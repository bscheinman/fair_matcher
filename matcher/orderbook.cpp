#include "orderbook.h"
#include <algorithm>
#include <vector>

using namespace trading::data;
using namespace std;


namespace trading {
namespace matcher {

/* These PriceGroup methods are not thread-safe but the containing
 * Orderbook has to lock on its insert methods anyway (for now)
 * so we can rely on that for thread safety.  If we modify the
 * Orderbook to allow concurrent insertions, then PriceGroup
 * methods will need to lock.
 */

void PriceGroup::add_order(const order_ptr& order) {
	orders_.insert(make_pair(order->order_id(), order));
	total_quantity_ += order->quantity();
}


/*
 * TODO: Should probably give priority to orders from earlier windows
 * (i.e. only be time-agnostic within each execution window)
 */
void PriceGroup::execute_shares(quantity_t shares, trade_callback callback) {
	// TODO: assert(shares <= quantity())
	quantity_t exec_quantity;
	quantity_t shares_remaining = shares;
	vector<shared_ptr<Trade> > trades;

	for (auto it = orders_.begin() ; it != orders_.end() ; ++it) {
		order_ptr order = it->second;
		Trade *p_trade(new Trade);
		// initially, execute proportional shares (rounded down) for each order
		exec_quantity = (order->quantity_remaining() * shares) / total_quantity_;
		p_trade->set_quantity(exec_quantity).set_order_id(order->order_id());
		order->set_quantity_remaining(order->quantity_remaining() - exec_quantity);
		shares_remaining -= exec_quantity;
		// TODO: assign trade IDs
		// Orderbook will assign price
		trades.emplace_back(p_trade);
	}

	/*
	 * TODO: For now, award extra shares in basically arbitrary order (according
	 * to hash map iterator).  This should change to be something more
	 * deterministic (and less game-able).  I am thinking of possibly
	 * ordering by remaining quantity (descending).
	 */
	for (auto it = trades.begin() ; it != trades.end() ; ++it) {
		order_ptr& order = orders_[(*it)->order_id()];
		if (shares_remaining > 0 && order->quantity_remaining() > 0) {
			(*it)->set_quantity((*it)->quantity() + 1);
			order->set_quantity_remaining(order->quantity_remaining() - 1);
			--shares_remaining;
		}
		callback(*it);
	}

	total_quantity_ -= shares;
}


int buy_compare(const Order& x, const PriceGroup& y) {
	price_t diff = y.price() - x.price();
	if (diff < 0) {
		return -1;
	} else {
		return diff > 0;
	}
}


int sell_compare(const Order& x, const PriceGroup& y) {
	return -1 * buy_compare(x, y);
}


typedef function<int(const Order&, const PriceGroup&)> order_comparer;
order_comparer buy_comparer(&buy_compare);
order_comparer sell_comparer(&sell_compare);


void Orderbook::add_order(const order_ptr& order) {
	lock_guard<mutex> lock(mutex_);

	group_list& groups = order->buy_or_sell() ? buy_groups_ : sell_groups_;
	order_comparer& comparer = order->buy_or_sell() ? buy_comparer : sell_comparer;
	group_list::iterator it = groups.begin();
	while (it != groups.end() && comparer(*order, *it) > 0) {
		++it;
	}
	 
	// if there is already a group with this price, then add
	// the order to that group
	if (it != groups.end() && comparer(*order, *it) == 0) { 
		it->add_order(order);
	} else { // otherwise create a new group for it
		PriceGroup group(order->buy_or_sell(), order->price());
		group.add_order(order);
		groups.insert(it, move(group));
	}
}


void Orderbook::match_orders(trade_callback callback) {
	lock_guard<mutex> lock(mutex_);
	group_list::iterator it_buy = buy_groups_.begin();
	group_list::iterator it_sell = sell_groups_.begin();

	vector<shared_ptr<Trade> > trades;
	auto add_trade = [&trades](shared_ptr<Trade> trade) { trades.push_back(trade); };
	price_t mean_price;

	while (it_buy != buy_groups_.end() &&
	       it_sell != sell_groups_.end() &&
	       it_buy->price() >= it_sell->price()) {

		quantity_t exec_quantity = min(it_buy->quantity(), it_sell->quantity());
		mean_price = (it_buy->price() + it_sell->price()) / 2;
		it_buy->execute_shares(exec_quantity, add_trade);
		it_sell->execute_shares(exec_quantity, add_trade);
	
		if (it_buy->quantity() == 0) {
			it_buy = buy_groups_.erase(it_buy);
		}

		if (it_sell->quantity() == 0) {
			it_sell = sell_groups_.erase(it_sell);
		}
			
	}

	for (auto it = trades.begin() ; it != trades.end() ; ++it) {
		(*it)->set_price(mean_price);
		callback(*it);
	}
}


}
}
