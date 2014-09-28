#include "server_session.h"
#include "heartbeat.h"
#include <boost/date_time/posix_time/posix_time.hpp>

#include <iostream>

using namespace trading::data;
using namespace std;

namespace trading {
namespace matcher {

void ServerSession::start(void) {
	NetworkSession::start();
	send_heartbeat_(0);
}


void ServerSession::process_message_(MessageType type, const char* const message, size_t message_size) {
	switch (type) {
	case MT_HeartbeatAck: {
		HeartbeatAck ack;
		ack.read_from_buffer(message, message_size);
		process_heartbeat_ack_(ack);
		break;
	}
	case MT_Order: {
		shared_ptr<Order> order(new Order);
		order->read_from_buffer(message, message_size);
		process_order_(order);
		break;
	}
	default: break;
	}
}


void ServerSession::process_heartbeat_ack_(const HeartbeatAck& ack) {
	unsigned long sequence = ack.sequence();
	heartbeat_timer_.expires_from_now(boost::posix_time::seconds(HEARTBEAT_INTERVAL));
	heartbeat_timer_.async_wait([this, sequence](const boost::system::error_code& ec) {
		send_heartbeat_(sequence + 1);
	});
	cout << "Received ack for heartbeat #" << sequence << endl;
}


void ServerSession::process_order_(shared_ptr<Order> order) {
	context_.engine()->process_order(order);
}


void ServerSession::send_heartbeat_(unsigned int sequence) {
	Heartbeat hb(sequence);
	send_message(hb);
	cout << "Sent heartbeat #" << sequence << endl;
}

}
}
