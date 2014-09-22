#include "match_server.h"

using namespace std;
using namespace boost::asio;

namespace trading {
namespace matcher {

MatchServer::MatchServer(io_service& io, const short port)
    : NetworkHost(io, port),
      engine_(io) { }


void MatchServer::start(void) {
	engine_.start();
	NetworkHost::start();
}


ServerSession* MatchServer::create_session_(void) {
	return new ServerSession(io_, engine_);
}

}
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
	io_service io;
	trading::matcher::MatchServer server(io, 2468);
	server.start();
	io.run();
	return 0;
}



