#include "client_session.h"
#include "heartbeat.h"
#include "heartbeat_ack.h"
#include "order.h"
#include <sstream>
#include <string>
#include <boost/asio.hpp>

#include <iostream>

using namespace trading::data;
using namespace trading::network;
using namespace std;
using boost::asio::ip::tcp;
namespace asio = boost::asio;

namespace trading {
namespace client {


void ClientSession::process_message_(MessageType message_type, const char* const message, size_t message_size) {
	switch(message_type) {
	case MT_Heartbeat: {
		Heartbeat hb;
		hb.read_from_buffer(message, message_size);
		HeartbeatAck ack(hb.sequence());
		send_message(ack);
		cout << "Responded to heartbeat #" << hb.sequence() << endl;

		if (hb.sequence() % 2 == 0) {
			Order o(string("order1"), string("user1"), string("GOOG"), 100, 500.00, true, 0);
			send_message(o);
		} else {
			Order o(string("order2"), string("user2"), string("GOOG"), 75, 500.00, false, 0);
			send_message(o);
		}

		break;
	}
	default: break;
	}
}

}
}
