#include "heartbeat.h"
#include <utility>

namespace trading {
namespace data {
	
Heartbeat::Heartbeat(const trading::data::proto::ProtoHeartbeat& proto) :
	sequence_(proto.sequence()) { }


void Heartbeat::copy_from_proto(const trading::data::proto::ProtoHeartbeat& proto) {
	sequence_ = proto.sequence();
}


trading::data::proto::ProtoHeartbeat Heartbeat::to_proto(void) const {
	proto::ProtoHeartbeat hb;
	hb.set_sequence(sequence_);
	return std::move(hb); // protobuf doesn't actually support move semantics yet :(
}

}
}
