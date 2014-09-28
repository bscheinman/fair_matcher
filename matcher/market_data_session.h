#ifndef MARKET_DATA_SESSION_H_
#define MARKET_DATA_SESSION_H_

#include "data_types.h"
#include "message_types.h"
#include "market_data_subscribe.h"
#include "network_session.h"
#include <unordered_set>
#include <boost/asio.hpp>

namespace trading {
namespace matcher {

class MarketDataSession : public trading::network::NetworkSession {
public:
	MarketDataSession(boost::asio::io_service& io)
		: NetworkSession(io) { };

protected:
	virtual void process_message_(trading::data::MessageType type, const char* const message, size_t message_size) override;

private:
	void process_subscription_(const trading::data::MarketDataSubscribe& subscription);

	// TODO: it makes more sense to keep track of subscriptions in the market data host as
	// opposed to having each session keep track of their own, but this is simpler for now
	//std::unordered_set<trading::data::symbol_t> subscriptions_;
};

}
}

#endif /* MARKET_DATA_SESSION_H_ */
