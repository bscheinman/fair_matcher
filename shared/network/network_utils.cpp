#include "network_utils.h"

using namespace trading::data;

namespace trading {
namespace network {

	namespace {
		unsigned long read_value_track(const char* const buffer, size_t bytes, size_t* const bytes_read) {
			size_t offset = bytes_read ? *bytes_read : 0;
			unsigned long result = read_value(buffer + offset, bytes);
			if (bytes_read) {
				*bytes_read += bytes;
			}
			return result;
		}


		void write_value_track(char* const buffer, unsigned long value, size_t bytes, size_t* const bytes_written) {
			size_t offset = bytes_written ? *bytes_written : 0;
			write_value(buffer + offset, value, bytes);
			if (bytes_written) {
				*bytes_written += bytes;
			}
		}

	}


	unsigned long read_value(const char* const buffer, size_t bytes) {
		// assert(bytes <= sizeof(size_t));
		unsigned long result = 0;
		for (size_t i = 0 ; i < bytes ; ++i) {
			result |= static_cast<unsigned long>(buffer[i]) << i;
		}
		return result;
	}


	void write_value(char* const buffer, unsigned long value, size_t bytes) {
		// assert(bytes <= sizeof(size_t));
		for (size_t i = 0 ; i < bytes ; ++i) {
			buffer[i] = static_cast<char>(value & 0xFF);
			value >>= 8;
		}
	}


	void read_message_header(const char* const buffer, MessageHeader& header) {
		size_t bytes_read = 0;
		header.body_size = read_value_track(buffer, 4, &bytes_read);
		header.message_type = static_cast<MessageType>(read_value_track(buffer, 2, &bytes_read));
		header.header_version = read_value_track(buffer, 2, &bytes_read);
	}


	// caller is responsible for ensuring that buffer has sufficient space
	void write_message_header(char* const buffer, const MessageHeader& header) {
		size_t bytes_written = 0;
		write_value_track(buffer, header.body_size, 4, &bytes_written);
		write_value_track(buffer, header.message_type, 2, &bytes_written);
		write_value_track(buffer, header.header_version, 2, &bytes_written);
	}

}
}
