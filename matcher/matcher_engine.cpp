#include "matcher_engine.h"

using namespace trading::data;
using namespace std;

namespace trading {
namespace matcher {

void MatcherEngine::start(void) {
	start_exec_timer_();
}


void MatcherEngine::process_order(shared_ptr<Order> order) {
	auto orderbook_it = orderbooks_.find(order->symbol().get());
	if (orderbook_it == orderbooks_.end()) {
		throw exception("invalid symbol");
	}

	orderbook_it->add_order(order);
}


void MatcherEngine::match_orders_(void) {
	for (auto it = orderbooks_.begin() ; it != orderbooks_.end() ; ++it) {
		it->second.match_orders([](const Trade& trade) {
			cout << "executed " << trade.quantity() << " shares of " << it->first
				<< " at " << trade.price() << endl;
		});
	}
}


void MatcherEngine::start_exec_timer_(void) {
	exec_timer_.expires_from_now(boost::posix_time::milliseconds(EXEC_INTERVAL));
	exec_timer_.async_wait([this](const boost::system::error_code& ec) {
		start_exec_timer_();
		match_orders_();
	});
}

}
}
