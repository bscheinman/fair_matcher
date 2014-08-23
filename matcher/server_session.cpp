#include "server_session.h"
#include "heartbeat.h"

using namespace trading::data;

namespace trading {
namespace matcher {

void ServerSession::start(void) {
	NetworkSession::start();
	Heartbeat hb(0);
	send_message(hb);
}


void ServerSession::process_message_(MessageType type, const char* const message, size_t message_size) {
	switch (type) {
	default: break;
	}
}

}
}
