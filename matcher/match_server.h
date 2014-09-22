#ifndef MATCH_SERVER_H_
#define MATCH_SERVER_H_

#include "server_session.h"
#include "matcher_engine.h"
#include "network_host.h"
#include <boost/asio.hpp>

namespace trading {
namespace matcher {

class MatchServer : public trading::network::NetworkHost<ServerSession> {
public:
	MatchServer(boost::asio::io_service& io, const short port);
	virtual void start(void) override;

protected:
	virtual ServerSession* create_session_(void) override;

private:
	MatcherEngine engine_;
};

}
}

#endif /* MATCH_SERVER_H_ */
