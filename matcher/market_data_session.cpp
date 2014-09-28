#include "market_data_session.h"
#include "messages.h"

using namespace trading::data;
using namespace std;

namespace trading {
namespace matcher {

	void MarketDataSession::process_message_(MessageType type, const char *const message, size_t message_size) {
		switch(type) {
			case MT_MarketDataSubscribe:
				MarketDataSubscribe subscribe;
				subscribe.read_from_buffer(message, message_size);
		        process_subscription_(subscribe);
				break;
		}

	}


	void MarketDataSession::process_subscription_(const MarketDataSubscribe& subscription) {
		// TODO: allow bulk wildcard subscriptions
		// subscriptions_.emplace(subscription.symbol());
	}

}
}