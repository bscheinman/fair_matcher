#ifndef NETWORK_HOST_H_
#define NETWORK_HOST_H_

#include <memory>
#include <boost/asio.hpp>

namespace trading {
namespace network {

template <typename SessionType>
class NetworkHost {
public:
	NetworkHost(boost::asio::io_service& io, const short port)
			: io_(io),
	          port_(port),
	          acceptor_(io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) { }
	virtual void start(void) {
		accept_connection_();
	}

protected:
	virtual SessionType* create_session_(void) = 0;
	typedef std::vector<std::shared_ptr<SessionType>> session_list;
	const session_list& get_sessions_(void) {
		return sessions_;
	}

	boost::asio::io_service& io_;

private:
	void accept_connection_(void) {
		std::shared_ptr<SessionType> session(create_session_());
		sessions_.push_back(session);
		acceptor_.async_accept(session->socket(),
			[=](const boost::system::error_code& ec) {
				(void)ec;
				session->start();
				accept_connection_();
			});
	}

	const short port_;
	boost::asio::ip::tcp::acceptor acceptor_;
	session_list sessions_;
};

}
}

#endif /* NETWORK_HOST_H_ */