#include "server_session.h"
#include "heartbeat.h"
#include "heartbeat_ack.h"
#include <boost/date_time/posix_time/posix_time.hpp>

#include <iostream>

using namespace trading::data;
using namespace std;

namespace trading {
namespace matcher {

void ServerSession::start(void) {
	NetworkSession::start();
	send_heartbeat(0);
}


void ServerSession::process_message_(MessageType type, const char* const message, size_t message_size) {
	switch (type) {
	case MT_HeartbeatAck: {
		HeartbeatAck ack;
		ack.read_from_buffer(message, message_size);
		unsigned long sequence = ack.sequence();
		heartbeat_timer_.expires_from_now(boost::posix_time::seconds(HEARTBEAT_INTERVAL));
		heartbeat_timer_.async_wait([this, sequence](const boost::system::error_code& ec) {
			send_heartbeat(sequence + 1);
		});
		cout << "Received ack for heartbeat #" << sequence << endl;
		break;
	}
	default: break;
	}
}


void ServerSession::send_heartbeat(unsigned int sequence) {
	Heartbeat hb(sequence);
	send_message(hb);
	cout << "Sent heartbeat #" << sequence << endl;
}

}
}
