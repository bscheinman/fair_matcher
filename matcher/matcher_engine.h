#ifndef MATCHER_ENGINE_H_
#define MATCHER_ENGINE_H_

#include "orderbook.h"
#include "order.h"
#include <string>
#include <unordered_map>
#include <boost/asio.hpp>

namespace trading {
namespace matcher {

#define DEFUALT_EXEC_INTERVAL 1000

class MatcherEngine {
public:

	MatcherEngine(boost::asio::io_service& io, unsigned long exec_interval)
		: exec_interval_(exec_interval),
		  exec_timer_(io) { }
	MatcherEngine(boost::asio::io_service& io)
		: MatcherEngine(io, DEFUALT_EXEC_INTERVAL) { }
	void process_order(std::shared_ptr<trading::data::Order> order);
	void start(void);

private:
	void match_orders_(void);
	void start_exec_timer_(void);

	std::unordered_map<std::string, Orderbook> orderbooks_;
	const unsigned long exec_interval_;
	boost::asio::deadline_timer exec_timer_;

};

}
}


#endif /* MATCHER_ENGINE_H_ */
