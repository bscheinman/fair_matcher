#ifndef MARKET_DATA_SUBSCRIBE_H_
#define MARKET_DATA_SUBSCRIBE_H_

#include "proto_wrapper.h"
#include "market_data_subscribe.pb.h"
#include "data_types.h"

namespace trading {
namespace data {
class MarketDataSubscribe : public ProtoWrapper<
		proto::ProtoMarketDataSubscribe,
		MessageType::MT_MarketDataSubscribe> {
public:
	MarketDataSubscribe(void) { };
	MarketDataSubscribe(const symbol_t symbol) : symbol_(symbol) { }

	symbol_t symbol(void) const { return symbol_; }

	virtual proto::ProtoMarketDataSubscribe to_proto(void) const override {
		proto::ProtoMarketDataSubscribe proto;
		proto.set_symbol(symbol_.get());
		return proto;
	}
	virtual void copy_from_proto(const proto::ProtoMarketDataSubscribe& proto) override {
		symbol_ = proto.symbol();
	}

private:
	symbol_t symbol_;
};
}
}


#endif /* MARKET_DATA_SUBSCRIBE_H_ */