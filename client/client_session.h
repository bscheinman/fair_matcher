#ifndef CLIENT_SESSION_H_
#define CLIENT_SESSION_H_

#include "network_session.h"

namespace trading {
namespace client {

class ClientSession : public trading::network::NetworkSession {
public:
	ClientSession(boost::asio::io_service& io) : trading::network::NetworkSession(io) { }
protected:
	virtual void process_message_(trading::data::MessageType message_type,
			const char* const message, size_t message_size) override;
};

}
}

#endif /* CLIENT_SESSION_H_ */
