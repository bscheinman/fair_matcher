#ifndef PROTO_WRAPPER_H_
#define PROTO_WRAPPER_H_

#include "message_types.h"
#include <iostream>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/io/coded_stream.h>

namespace trading {
namespace data {

template<typename ProtoClass, MessageType MType>
class ProtoWrapper {
public:
	// not sure how to enforce something like this, but all
	// subclasses should implement a copy constructor
	// for the proto class
	//virtual ProtoWrapper(const ProtoClass& proto) = 0;

	virtual void copy_from_proto(const ProtoClass& proto) = 0;
	ProtoWrapper& operator=(const ProtoClass& proto) {
		copy_from_proto(proto);
		return *this;
	}
	virtual ProtoClass to_proto(void) const = 0;

	void write_to_buffer(char* const buffer) const {
		ProtoClass proto = to_proto();
		google::protobuf::uint32 message_size = proto.ByteSize();
		// TODO: check buffer size to prevent overflows
		google::protobuf::io::ArrayOutputStream os(buffer, message_size);
		google::protobuf::io::CodedOutputStream cos(&os);
		proto.SerializeToCodedStream(&cos);
	}

	void read_from_buffer(const char* const buffer, size_t buffer_size) {
		google::protobuf::io::ArrayInputStream is(buffer, buffer_size);
		google::protobuf::io::CodedInputStream cis(&is);
		ProtoClass proto;
		proto.ParseFromCodedStream(&cis);
		copy_from_proto(proto);
	}
	MessageType message_type(void) const { return message_type_; }

private:
	const MessageType message_type_ = MType;
};

}
}

#endif /* PROTO_WRAPPER_H_ */
