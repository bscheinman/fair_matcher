#ifndef ORDERBOOK_H_
#define ORDERBOOK_H_

#include "data_types.h"
#include "order.h"
#include "trade.h"
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <unordered_map>


namespace trading {
namespace matcher {

typedef std::function<void(const std::shared_ptr<trading::data::Trade>)> trade_callback;
typedef std::shared_ptr<trading::data::Order> order_ptr;

class WindowGroup {
public:
	WindowGroup(trading::data::window_t window)
		: total_quantity_(0),
		  window_(window) { }
	void add_order(order_ptr order);
	void execute_shares(trading::data::quantity_t shares, trade_callback callback);

	trading::data::quantity_t quantity(void) const { return total_quantity_; }
	trading::data::window_t window(void) const { return window_; }

private:
	std::unordered_map<std::string, order_ptr> orders_;
	trading::data::quantity_t total_quantity_;
	const trading::data::window_t window_;
};


class PriceGroup {
public:
	PriceGroup(trading::data::price_t price)
		: price_(price),
		  total_quantity_(0) { }

	void add_order(order_ptr order);
	void execute_shares(trading::data::quantity_t shares, trade_callback callback);

	trading::data::price_t price(void) const { return price_; }
	trading::data::quantity_t quantity(void) const { return total_quantity_; }

private:
	std::list<WindowGroup> windows_;
	trading::data::quantity_t total_quantity_;
	const trading::data::price_t price_;
};


class Orderbook {
public:
	void add_order(order_ptr order);
	void match_orders(trade_callback callback);

private:
	/* Use a linked list for this--
	 * even though insertions will be linear wrt the number of distinct prices,
	 * this number will rarely be significantly large, and in practice,
	 * most orders will end up very close to the head of the list.
	 * I suppose in theory a malicious user could submit orders with many different
	 * prices, but really any sort of flooding attack would have a similar effect
	 * anyway and that should be dealt with upstream.
	 */
	typedef std::list<PriceGroup> group_list;
	group_list buy_groups_;
	group_list sell_groups_;
	std::mutex mutex_;
};

}
}

#endif /* ORDERBOOK_H_ */
