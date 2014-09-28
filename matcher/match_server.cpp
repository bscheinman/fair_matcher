#include "match_server.h"
#include "market_data_host.h"

using namespace std;
using namespace boost::asio;

namespace trading {
namespace matcher {

MatchServer::MatchServer(io_service& io, const short port, MarketDataHost& md_host)
    : NetworkHost(io, port),
      engine_(io, context_) {
	context_.set_md_host(&md_host);
	context_.set_engine(&engine_);
}


void MatchServer::start(void) {
	engine_.start();
	NetworkHost::start();
}


ServerSession* MatchServer::create_session_(void) {
	return new ServerSession(io_, context_);
}

}
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
	io_service io;
	trading::matcher::MarketDataHost md_host(io, 2469);
	trading::matcher::MatchServer server(io, 2468, md_host);
	server.start();
	io.run();
	return 0;
}



