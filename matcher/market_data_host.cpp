#include "market_data_host.h"

using namespace std;
using namespace trading::data;


namespace trading {
namespace matcher {

	void MarketDataHost::broadcast_trade(const Trade& trade) {
		// TODO: actually keep track of subscriptions; for now just send to all
		for (auto session : get_sessions_()) {
			session->send_message(trade);
		}
	}


	MarketDataSession* MarketDataHost::create_session_(void) {
		return new MarketDataSession(io_);
	}

}
}