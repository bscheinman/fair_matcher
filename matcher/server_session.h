#ifndef SERVER_SESSION_H_
#define SERVER_SESSION_H_

#include "heartbeat_ack.h"
#include "matcher_engine.h"
#include "match_server_context.h"
#include "order.h"
#include "../shared/network/network_session.h"
#include "../shared/trade_data/message_types.h"
#include <memory>
#include <boost/asio.hpp>

#define HEARTBEAT_INTERVAL 10

namespace trading {
namespace matcher {

class ServerSession : public trading::network::NetworkSession {
public:
	ServerSession(boost::asio::io_service& io, MatchServerContext& context)
	  : trading::network::NetworkSession(io),
	    context_(context),
	    heartbeat_timer_(io) { }
	virtual void start(void) override;

protected:
	virtual void process_message_(trading::data::MessageType message_type,
		const char* const message, size_t message_size) override;

private:
	void process_heartbeat_ack_(const trading::data::HeartbeatAck& ack);
	void process_order_(std::shared_ptr<trading::data::Order> order);
	void send_heartbeat_(unsigned int sequence);

	boost::asio::deadline_timer heartbeat_timer_;
	MatchServerContext& context_;
};

}
}


#endif /* SERVER_SESSION_H_ */
