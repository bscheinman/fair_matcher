#include "matcher_engine.h"
#include "market_data_host.h"
#include <iostream>

using namespace trading::data;
using namespace std;

namespace trading {
namespace matcher {

void MatcherEngine::start(void) {
	//TODO: read symbols from input file or something similar
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

	order->set_window(window_);
	orderbook_it->second.add_order(order);
}


void MatcherEngine::match_orders_(void) {
	for (auto it = orderbooks_.begin() ; it != orderbooks_.end() ; ++it) {
		it->second.match_orders([this, &it](shared_ptr<Trade> trade) {
			cout << "executed " << trade->quantity() << " shares of " << it->first
				<< " at " << trade->price() << endl;
			trade->set_window(window_);
		    context_.md_host()->broadcast_trade(*trade);
		});
	}
}


void MatcherEngine::start_exec_timer_(void) {
	exec_timer_.expires_from_now(boost::posix_time::milliseconds(exec_interval_));
	exec_timer_.async_wait([this](const boost::system::error_code& ec) {
		start_exec_timer_();
		// this can be a problem if matching orders begins to take the better part
		// of a window interval
		match_orders_();
		++window_;
	});
}

}
}
