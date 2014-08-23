#include "network_session.h"
#include <iomanip>
#include <iostream>
#include <utility>

using namespace trading::data;
using namespace std;
namespace asio = boost::asio;
using boost::asio::ip::tcp;

namespace trading {
namespace network {

NetworkSession::NetworkSession(asio::io_service& io) :
	io_(io),
	socket_(io),
	write_mutex_() {

}


void NetworkSession::connect(const string& host, short port) {
	tcp::resolver resolver(io_);
	ostringstream oss;
	oss << port;
	tcp::resolver::query query(host, oss.str());
	tcp::resolver::iterator it = resolver.resolve(query);
	tcp::endpoint endpoint = *it;

	socket_.async_connect(endpoint, [=](const boost::system::error_code& ec) {
		start();
	});
}


void NetworkSession::start(void) {
	await_header_();
}


void NetworkSession::await_header_(void) {
	asio::async_read(socket_, asio::buffer(read_buffer_, HEADER_SIZE),
		[this](const boost::system::error_code& ec, size_t bytes) {
			(void)ec;
			if (bytes == HEADER_SIZE) {
				handle_header_();
			} else {
				// TODO: dispose of everything after closed connection
				cout << "connection closed" << endl;
			}
		});
}


void NetworkSession::handle_header_(void) {
	read_message_header(read_buffer_, message_header_);

	// TODO: check message size and either confirm that it does not exceed
	// allocated buffer size, or (probably) add logic for reading messages in chunks.
	// for now, just assume that message fits in buffer (!!!)
	asio::async_read(socket_, asio::buffer(read_buffer_, message_header_.body_size),
		[=](const boost::system::error_code& ec, size_t bytes) {
			(void) ec;
			(void) bytes;
			handle_body_();
		});
}


void NetworkSession::handle_body_(void) {

#if DEBUG
	ostringstream oss;
	oss << hex << setfill('0');
	for (unsigned int i = 0 ; i < message_header_.body_size ; ++i) {
		oss << setw(2) << static_cast<unsigned>(read_buffer_[i]) << " ";
	}
	cout << "Received message data:" << endl;
	cout << oss.str() << endl;
#endif /* DEBUG */

	// process_message_ is responsible for marshaling calls onto a
	// separate thread if desired
	process_message_(message_header_.message_type, read_buffer_, message_header_.body_size);
	await_header_();
}


// this blocks until the write is complete
void NetworkSession::send_message_(MessageType message_type, const char * const message, size_t bytes) {
	lock_guard<mutex> lock(write_mutex_);

	MessageHeader header;
	header.message_type = message_type;
	header.body_size = bytes;

	// TODO: check against buffer overflows.  For now just assume it fits
	write_message_header(write_buffer_, header);
	memcpy(write_buffer_ + HEADER_SIZE, message, bytes);
	asio::write(socket_, asio::buffer(write_buffer_, bytes + HEADER_SIZE));
}

}
}
