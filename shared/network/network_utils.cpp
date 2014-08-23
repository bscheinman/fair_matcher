#include "network_utils.h"

using namespace trading::data;

namespace trading {
namespace network {

	size_t read_value(const char* const buffer, size_t bytes) {
		// assert(bytes <= sizeof(size_t));
		size_t result = 0;
		for (int i = bytes - 1 ; i >= 0 ; --i) {
			result = (result << 8) | buffer[i];
		}
		return result;
	}


	void write_value(char* const buffer, size_t value, size_t bytes) {
		// assert(bytes <= sizeof(size_t));
		for (int i = bytes - 1 ; i >= 0 ; --i) {
			buffer[i] = static_cast<char>(value & 0xFF);
			value >>= 8;
		}
	}


	void read_message_header(const char* const buffer, MessageHeader& header) {
		header.body_size = read_value(buffer, 4);
		header.message_type = static_cast<MessageType>(read_value(buffer, 2));
		header.header_version = read_value(buffer, 2);
	}


	// caller is responsible for ensuring that buffer has sufficient space
	void write_message_header(char* const buffer, const MessageHeader& header) {
		write_value(buffer, header.body_size, 4);
		write_value(buffer, header.message_type, 2);
		write_value(buffer, header.header_version, 2);
	}

}
}
