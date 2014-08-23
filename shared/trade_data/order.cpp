#include "order.h"
#include <memory>
#include <utility>

using namespace std;
using namespace trading::data::proto;

namespace trading {
namespace data {

Order::Order(ProtoOrder& proto) :
	order_id_(proto.order_id()),
	user_id_(proto.user_id()),
	symbol_(proto.symbol()),
	quantity_(proto.quantity()),
	price_(proto.price()),
	buy_or_sell_(proto.buy_or_sell() == ProtoOrder::BUY)
{ }


ProtoOrder Order::to_proto(void) const {
	ProtoOrder proto;
	proto.set_order_id(get_order_id());
	proto.set_user_id(get_user_id());
	proto.set_symbol(get_symbol());
	proto.set_quantity(get_quantity());
	proto.set_price(get_price());
	proto.set_buy_or_sell(buy_or_sell() ? ProtoOrder::BUY : ProtoOrder::SELL);
	return move(proto);
}


void Order::copy_from_proto(const ProtoOrder& proto) {
	order_id_ = proto.order_id();
	user_id_ = proto.user_id();
	symbol_ = proto.symbol();
	quantity_ = proto.quantity();
	price_ = proto.price();
	buy_or_sell_ = proto.buy_or_sell() == ProtoOrder::BUY;
}

}
}
