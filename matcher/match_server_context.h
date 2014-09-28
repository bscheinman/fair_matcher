#ifndef MATCH_SERVER_CONTEXT_H_
#define MATCH_SERVER_CONTEXT_H_

namespace boost {
	namespace asio {
		class io_service;
	}
}

namespace trading {
namespace matcher {

	class MatcherEngine;
	class MarketDataHost;

	class MatchServerContext {
	public:

		MatchServerContext(void) {
			engine_ = 0;
			md_host_ = 0;
		}

		// TODO: make setters only accessible by MatchServer via friend classes

		MatcherEngine* engine(void) { return engine_; }
		const MatcherEngine* engine(void) const { return engine_; }
		void set_engine(MatcherEngine* engine) { engine_ = engine; }

		MarketDataHost* md_host(void) { return md_host_; }
		const MarketDataHost* md_host(void) const { return md_host_; }
		void set_md_host(MarketDataHost* md_host) { md_host_ = md_host; }

	private:
		MatcherEngine *engine_;
		MarketDataHost *md_host_;

	};

}
}

#endif /* MATCH_SERVER_CONTEXT_H_ */