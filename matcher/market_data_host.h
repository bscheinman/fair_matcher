#include "network_host.h"
#include "market_data_session.h"
#include "messages.h"

namespace trading {
namespace matcher {

class MarketDataHost : public trading::network::NetworkHost<MarketDataSession> {
public:
	MarketDataHost(boost::asio::io_service& io, short port)
			: NetworkHost(io, port) { }

	void broadcast_trade(const trading::data::Trade& trade);

protected:
	virtual MarketDataSession *create_session_(void) override;

};

}
}