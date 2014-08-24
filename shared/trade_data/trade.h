#ifndef TRADE_H_
#define TRADE_H_

#include "proto_wrapper.h"
#include "trade.pb.h"
#include "data_types.h"
#include <string>

namespace trading {
namespace data {

class Trade : public ProtoWrapper<
		trading::data::proto::Trade,
		trading::data::MessageType::MT_Trade> {
public:

	Trade(void) { }

	Trade(const std::string& trade_id,
			const std::string& order_id,
			quantity_t quantity,
			price_t price)
		: trade_id_(trade_id),
		  order_id_(order_id),
		  quantity_(quantity),
		  price_(price) { }

	Trade(const trading::data::proto::Trade& trade)
		: Trade(trade.trade_id(),
			trade.order_id(),
			trade.quantity(),
			trade.price()) { }

	std::string& trade_id(void) { return trade_id_; }
	Trade& trade_id(const std::string& trade_id) { trade_id_ = trade_id; return *this; }

	std::string& order_id(void) { return order_id_; }
	Trade& order_id(const std::string& order_id) { order_id_ = order_id; return *this; }

	quantity_t quantity(void) { return quantity_; }
	Trade& quantity(const quantity_t quantity) { quantity_ = quantity; return *this; }

	price_t price(void) { return price_; }
	Trade& price(price_t price) { price_ = price; return *this; }

	virtual void copy_from_proto(const trading::data::proto::Trade& proto) override;
	virtual trading::data::proto::Trade to_proto(void) const override;
private:
	std::string trade_id_;
	std::string order_id_;
	quantity_t quantity_;
	price_t price_;
};

}
}

#endif /* TRADE_H_ */
