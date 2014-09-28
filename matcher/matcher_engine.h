#ifndef MATCHER_ENGINE_H_
#define MATCHER_ENGINE_H_

#include "match_server_context.h"
#include "orderbook.h"
#include "order.h"
#include <string>
#include <unordered_map>
#include <boost/asio.hpp>

namespace trading {
namespace matcher {

#define DEFAULT_EXEC_INTERVAL 1000

class MatcherEngine {
public:

	MatcherEngine(boost::asio::io_service& io, MatchServerContext& context, unsigned long exec_interval)
		: exec_interval_(exec_interval),
		  context_(context),
		  exec_timer_(io) { }

	MatcherEngine(boost::asio::io_service& io, MatchServerContext& context)
		: MatcherEngine(io, context, DEFAULT_EXEC_INTERVAL) { }

	void process_order(std::shared_ptr<trading::data::Order> order);
	void start(void);

private:
	void match_orders_(void);
	void start_exec_timer_(void);

	std::unordered_map<std::string, Orderbook> orderbooks_;
	const unsigned long exec_interval_;
	boost::asio::deadline_timer exec_timer_;
	MatchServerContext& context_;

};

}
}


#endif /* MATCHER_ENGINE_H_ */
