#include "matcher_engine.h"
#include <iostream>

using namespace trading::data;
using namespace std;

namespace trading {
namespace matcher {

void MatcherEngine::start(void) {
	//orderbooks_.emplace("GOOG");
	orderbooks_.emplace(
		std::piecewise_construct,
		std::forward_as_tuple("GOOG"),
		std::forward_as_tuple());

	start_exec_timer_();
}


void MatcherEngine::process_order(shared_ptr<Order> order) {
	auto orderbook_it = orderbooks_.find(order->symbol());
	if (orderbook_it == orderbooks_.end()) {
		//throw exception(string("invalid symbol"));
		return;
	}

	orderbook_it->second.add_order(order);
}


void MatcherEngine::match_orders_(void) {
	for (auto it = orderbooks_.begin() ; it != orderbooks_.end() ; ++it) {
		it->second.match_orders([&it](shared_ptr<Trade> trade) {
			cout << "executed " << trade->quantity() << " shares of " << it->first
				<< " at " << trade->price() << endl;
		});
	}
}


void MatcherEngine::start_exec_timer_(void) {
	exec_timer_.expires_from_now(boost::posix_time::milliseconds(exec_interval_));
	exec_timer_.async_wait([this](const boost::system::error_code& ec) {
		start_exec_timer_();
		match_orders_();
	});
}

}
}
