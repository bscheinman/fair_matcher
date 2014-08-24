#ifndef ORDER_H_
#define ORDER_H_

#include "proto_wrapper.h"
#include "order.pb.h"
#include "data_types.h"
#include <string>
#include <boost/flyweight.hpp>

namespace trading {
namespace data {

class Order : public ProtoWrapper<
		trading::data::proto::ProtoOrder,
		trading::data::MessageType::MT_Order> {
public:
	Order(trading::data::proto::ProtoOrder &message);
	virtual trading::data::proto::ProtoOrder to_proto(void) const override;
	virtual void copy_from_proto(const trading::data::proto::ProtoOrder& proto) override;

	const std::string& order_id(void) const { return order_id_; }
	const std::string& symbol(void) const { return symbol_.get(); }
	const std::string& user_id(void) const { return user_id_.get(); }
	quantity_t quantity(void) const { return quantity_; }
	price_t price(void) const { return price_; }
	bool buy_or_sell(void) const { return buy_or_sell_; }
private:
	std::string order_id_;
	boost::flyweight<std::string> user_id_;
	boost::flyweight<std::string> symbol_;
	quantity_t quantity_;
	price_t price_;
	bool buy_or_sell_;
};

}
}


#endif /* ORDER_H_ */
