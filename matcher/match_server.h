#ifndef MATCH_SERVER_H_
#define MATCH_SERVER_H_

#include "server_session.h"
#include <boost/asio.hpp>

namespace trading {
namespace matcher {

    class MatchServer {
    public:
        MatchServer(boost::asio::io_service& io, const short port);
        void start(void);

    private:
        void accept_connection_(void);

        boost::asio::io_service& io_;
        const short port_;
        boost::asio::ip::tcp::acceptor acceptor_;
        std::vector<std::shared_ptr<trading::matcher::ServerSession>> sessions_;
    };

}
}

#endif /* MATCH_SERVER_H_ */
