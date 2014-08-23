#ifndef NETWORK_UTILS_H_
#define NETWORK_UTILS_H_

#include <cstdlib>
#include "message_types.h"

#define HEADER_SIZE 8
#define TRADING_VERSION 1


namespace trading {
namespace network {

	typedef struct MessageHeader {
		size_t body_size;
		trading::data::MessageType message_type;
		unsigned int header_version;
		MessageHeader(void) : header_version(TRADING_VERSION) {}
	} MessageHeader;

	size_t read_value(const char* const buffer, size_t bytes);
	void write_value(char* const buffer, size_t value, size_t bytes);
	void read_message_header(const char* const buffer, MessageHeader& header);

	// caller is responsible for ensuring that buffer has sufficient space
	void write_message_header(char* const buffer, const MessageHeader& header);

}
}

#endif /* NETWORK_UTILS_H_ */
