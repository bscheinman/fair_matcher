#ifndef SERVER_SESSION_H_
#define SERVER_SESSION_H_

#include "../shared/network/network_session.h"
#include "../shared/trade_data/message_types.h"
#include <boost/asio.hpp>

namespace trading {
namespace matcher {

    class ServerSession : public trading::network::NetworkSession {
    public:
        ServerSession(boost::asio::io_service& io) : trading::network::NetworkSession(io) { }
    	virtual void start(void) override;
    protected:
        virtual void process_message_(trading::data::MessageType message_type,
		const char* const message, size_t message_size) override;
    };

}
}


#endif /* SERVER_SESSION_H_ */
