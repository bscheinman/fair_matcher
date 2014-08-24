#include "match_server.h"
#include <iostream>
#include <memory>
#include <boost/system/error_code.hpp>

using namespace std;
using namespace boost::asio;
using boost::asio::ip::tcp;

namespace trading {
namespace matcher {

MatchServer::MatchServer(io_service& io, const short port)
	: io_(io),
	  port_(port),
	  acceptor_(io, tcp::endpoint(tcp::v4(), port)),
	  engine_(io) {
	accept_connection_();
}


void MatchServer::accept_connection_(void) {
	shared_ptr<ServerSession> session(new ServerSession(io_, engine_));
	sessions_.push_back(session);
	acceptor_.async_accept(session->socket(),
		[=](const boost::system::error_code& ec) {
			(void)ec;
			session->start();
			accept_connection_();
		});
}

}
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
	io_service io;
	trading::matcher::MatchServer server(io, 2468);
	io.run();
	return 0;
}



