#ifndef MATCH_SERVER_H_
#define MATCH_SERVER_H_

#include "match_server_context.h"
#include "matcher_engine.h"
#include "network_host.h"
#include "server_session.h"

namespace trading {
namespace matcher {

class MarketDataHost;

class MatchServer : public trading::network::NetworkHost<ServerSession> {
public:
	MatchServer(boost::asio::io_service& io, const short port, MarketDataHost& md_host);
	virtual void start(void) override;

protected:
	virtual ServerSession* create_session_(void) override;

private:
	MatcherEngine engine_;
	MatchServerContext context_;
};

}
}

#endif /* MATCH_SERVER_H_ */
