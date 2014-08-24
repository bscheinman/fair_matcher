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
	orders_.push_back(order);
	total_quantity_ += order->quantity();
}


/* TODO: There is going to be some very funky floating point
 * stuff going on here; we should probably decide on some
 * minimum fractional share to use, or (probably better),
 * get rid of partial shares altogether and award remaining 
 * shares to the biggest orders instead of having fractional executions
 */

void PriceGroup::execute_shares(quantity_t shares, trade_callback callback) {
	Trade trade;
	if (shares == quantity()) {
		for (auto it = orders_.begin() ; it != orders_.end() ; ++it) {
			trade.set_quantity((*it)->quantity()).set_order_id((*it)->order_id());
			// TODO: assign trade IDs
			// Orderbook will assign price
			callback(trade);
		}
	}

}


int buy_compare(const Order& x, const PriceGroup& y) {
	return y.price() - x.price();
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

	vector<Trade> trades;
	auto add_trade = [&trades](const Trade& trade) { trades.push_back(trade); };
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
		it->set_price(mean_price);
		callback(*it);
	}
}


}
}
