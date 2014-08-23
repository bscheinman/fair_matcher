#ifndef NETWORK_SESSION_H_
#define NETWORK_SESSION_H_

#include "message_types.h"
#include "network_utils.h"
#include "proto_wrapper.h"
#include <mutex>
#include <string>
#include <boost/asio.hpp>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/io/coded_stream.h>

namespace trading {
namespace network {

	class NetworkSession {
	public:

		NetworkSession(boost::asio::io_service &io);

		boost::asio::ip::tcp::socket& socket(void) { return socket_; }
		virtual void start(void);
		void connect(const std::string& host, short port);

		template <typename T, trading::data::MessageType MType>
		void send_message(const trading::data::ProtoWrapper<T, MType>& message) {
			std::lock_guard<std::mutex> lock(write_mutex_);
			T proto = message.to_proto();

			trading::network::MessageHeader header;
			//header.message_type = message.message_type();
			header.message_type = MType;
			header.body_size = proto.ByteSize();

			// TODO: check against buffer overflows.  For now just assume it fits
			trading::network::write_message_header(write_buffer_, header);
			google::protobuf::io::ArrayOutputStream os(write_buffer_, header.body_size);
			google::protobuf::io::CodedOutputStream cos(&os);
			proto.SerializeToCodedStream(&cos);
			boost::asio::write(socket_, boost::asio::buffer(write_buffer_, header.body_size + HEADER_SIZE));
		}

	protected:
		virtual void process_message_(trading::data::MessageType type, const char* const message, size_t message_size) = 0;
		void send_message_(trading::data::MessageType type, const char * const message, size_t bytes);

	private:

		void await_header_(void);
		void handle_header_(void);
		void handle_body_(void);

		boost::asio::io_service& io_;
		boost::asio::ip::tcp::socket socket_;
		char read_buffer_[2 << 10];
		char write_buffer_[2 << 10];
		MessageHeader message_header_;
		std::mutex write_mutex_;
	};

}
}

#endif /* NETWORK_SESSION_H_ */
