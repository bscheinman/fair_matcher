#include "trade.h"

using trading::data::proto;
using namespace std;
using boost::flyweight;

namespace trading {
namespace data {

void Trade::copy_from_proto(const proto::Trade& trade) {
	trade_id_ = trade.trade_id();
	order_id_ = trade.order_id();
	quantity_ = trade.quantity();
	price_ = trade.price();
}


proto::Trade to_proto(void) const {
	proto::Trade trade;
	trade.set_trade_id(trade_id_);
	trade.set_order_id(order_id_);
	trade.set_quantity(quantity_);
	trade.set_price(price_;
	return move(trade);
}

}
}
