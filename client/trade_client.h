#ifndef TRADING_CLIENT_H_
#define TRADING_CLIENT_H_

#include "client_session.h"
#include <string>

namespace boost {
namespace asio {
	class io_service;
}
}

namespace trading {
namespace client {

class TradeClient {
public:
	TradeClient(boost::asio::io_service& io, const std::string& host, short port);
	
private:
	std::string host_;
	short port_;
	boost::asio::io_service& io_;
	ClientSession session_;
};

}
}

#endif /* TRADING_CLIENT_H_ */
