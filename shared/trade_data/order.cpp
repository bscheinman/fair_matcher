#include "order.h"
#include <memory>
#include <utility>

using namespace std;
using namespace trading::data::proto;

namespace trading {
namespace data {


Order::Order(const std::string& order_id, const std::string& user_id,
		const std::string& symbol, quantity_t quantity, price_t price,
		bool buy_or_sell, window_t window)
	: order_id_(order_id),
	  user_id_(user_id),
	  symbol_(symbol),
	  quantity_(quantity),
	  quantity_remaining_(quantity),
	  price_(price),
	  buy_or_sell_(buy_or_sell),
	  window_(window)
{ }


// orders are only sent over the wire to indicate new orders,
// so proto messages do not need to support remaining quantity
// or window
Order::Order(const ProtoOrder& message) : Order(
	message.order_id(),
	message.user_id(),
	message.symbol(),
	message.quantity(),
	message.price(),
	message.buy_or_sell() == ProtoOrder::BUY,
	0)
{ }


ProtoOrder Order::to_proto(void) const {
	ProtoOrder proto;
	proto.set_order_id(order_id());
	proto.set_user_id(user_id());
	proto.set_symbol(symbol());
	proto.set_quantity(quantity());
	proto.set_price(price());
	proto.set_buy_or_sell(buy_or_sell() ? ProtoOrder::BUY : ProtoOrder::SELL);
	return move(proto);
}


void Order::copy_from_proto(const ProtoOrder& proto) {
	order_id_ = proto.order_id();
	user_id_ = proto.user_id();
	symbol_ = proto.symbol();
	quantity_ = proto.quantity();
	quantity_remaining_ = proto.quantity();
	price_ = proto.price();
	buy_or_sell_ = proto.buy_or_sell() == ProtoOrder::BUY;
}

}
}
