#ifndef ORDER_H_
#define ORDER_H_

#include "proto_wrapper.h"
#include "order.pb.h"
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

	const std::string& get_order_id(void) const { return order_id_.get(); }
	const std::string& get_symbol(void) const { return symbol_.get(); }
	const std::string& get_user_id(void) const { return user_id_.get(); }
	const unsigned int get_quantity(void) const { return quantity_; }
	const float get_price(void) const { return price_; }
	const bool buy_or_sell(void) const { return buy_or_sell_; }
private:
	boost::flyweight<std::string> order_id_;
	boost::flyweight<std::string> user_id_;
	boost::flyweight<std::string> symbol_;
	unsigned int quantity_;
	float price_;
	bool buy_or_sell_;
};

}
}


#endif /* ORDER_H_ */
