#include "trade.h"

using namespace std;
namespace proto = trading::data::proto;

namespace trading {
namespace data {


Trade::Trade(const string& trade_id, const string& order_id, quantity_t quantity, price_t price, window_t window)
	: trade_id_(trade_id),
	  order_id_(order_id),
	  quantity_(quantity),
	  price_(price),
	  window_(window)
{ }


Trade::Trade(const proto::Trade& trade)
	: Trade(trade.trade_id(),
		trade.order_id(),
		trade.quantity(),
		trade.price(),
		trade.window())
{ }


void Trade::copy_from_proto(const proto::Trade& trade) {
	trade_id_ = trade.trade_id();
	order_id_ = trade.order_id();
	quantity_ = trade.quantity();
	price_ = trade.price();
	window_ = trade.window();
}


proto::Trade Trade::to_proto(void) const {
	proto::Trade trade;
	trade.set_trade_id(trade_id_);
	trade.set_order_id(order_id_);
	trade.set_quantity(quantity_);
	trade.set_price(price_);
	trade.set_window(window_);
	return move(trade);
}

}
}
