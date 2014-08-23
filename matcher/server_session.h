#ifndef SERVER_SESSION_H_
#define SERVER_SESSION_H_

#include "../shared/network/network_session.h"
#include "../shared/trade_data/message_types.h"
#include <boost/asio.hpp>

#define HEARTBEAT_INTERVAL 10

namespace trading {
namespace matcher {

class ServerSession : public trading::network::NetworkSession {
public:
	ServerSession(boost::asio::io_service& io)
	  : trading::network::NetworkSession(io),
	    heartbeat_timer_(io) { }
	virtual void start(void) override;

protected:
	virtual void process_message_(trading::data::MessageType message_type,
		const char* const message, size_t message_size) override;
	void send_heartbeat(unsigned int sequence);

private:
	boost::asio::deadline_timer heartbeat_timer_;
};

}
}


#endif /* SERVER_SESSION_H_ */
