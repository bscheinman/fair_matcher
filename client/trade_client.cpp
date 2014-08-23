#include "trade_client.h"
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;


namespace trading {
namespace client {

TradeClient::TradeClient(io_service& io, const string& host, short port)
	: io_(io),
	  session_(io) {
	session_.connect(host, port);
}


}
}


int main(int argc, char** argv) {
	(void)argc;
	(void)argv;
	io_service io;
	trading::client::TradeClient client(io, "localhost", 2468);
	io.run();
	return 0;
}
