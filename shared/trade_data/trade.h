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
	Trade(const std::string& trade_id, const std::string& order_id,
		quantity_t quantity, price_t price);
	Trade(const trading::data::proto::Trade& trade);

	const std::string& trade_id(void) const { return trade_id_; }
	Trade& set_trade_id(const std::string& trade_id) { trade_id_ = trade_id; return *this; }

	const std::string& order_id(void) const { return order_id_; }
	Trade& set_order_id(const std::string& order_id) { order_id_ = order_id; return *this; }

	quantity_t quantity(void) const { return quantity_; }
	Trade& set_quantity(const quantity_t quantity) { quantity_ = quantity; return *this; }

	price_t price(void) const { return price_; }
	Trade& set_price(price_t price) { price_ = price; return *this; }

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
