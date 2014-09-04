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
	Order(void) { }
	Order(const std::string& order_id, const std::string& user_id,
		const std::string& symbol, quantity_t quantity, price_t price,
		bool buy_or_sell);
	Order(const trading::data::proto::ProtoOrder& proto);

	virtual trading::data::proto::ProtoOrder to_proto(void) const override;
	virtual void copy_from_proto(const trading::data::proto::ProtoOrder& proto) override;

	const std::string& order_id(void) const { return order_id_; }
	Order& set_order_id(const std::string& order_id) { order_id_ = order_id; return *this; }

	const std::string& symbol(void) const { return symbol_.get(); }
	Order& set_symbol(const std::string& symbol) { symbol_ = symbol; return *this; }

	const std::string& user_id(void) const { return user_id_.get(); }
	Order& set_user_id(const std::string& user_id) { user_id_ = user_id; return *this; }

	quantity_t quantity(void) const { return quantity_; }
	Order& set_quantity(quantity_t quantity) { quantity_ = quantity; return *this; }

	quantity_t quantity_remaining(void) const { return quantity_remaining_; }
	Order& set_quantity_remaining(quantity_t quantity) { quantity_remaining_ = quantity; return *this; }

	price_t price(void) const { return price_; }
	Order& set_price(price_t price) { price_ = price; return *this; }

	bool buy_or_sell(void) const { return buy_or_sell_; }
	Order& set_buy_or_sell(bool buy_or_sell) { buy_or_sell_ = buy_or_sell; return *this; }

private:
	std::string order_id_;
	boost::flyweight<std::string> user_id_;
	boost::flyweight<std::string> symbol_;
	quantity_t quantity_;
	quantity_t quantity_remaining_;
	price_t price_;
	bool buy_or_sell_;
};

}
}


#endif /* ORDER_H_ */
