#include "heartbeat_ack.h"
#include <utility>

namespace trading {
namespace data {
	
HeartbeatAck::HeartbeatAck(const trading::data::proto::ProtoHeartbeatAck& proto) :
	sequence_(proto.sequence()) { }


void HeartbeatAck::copy_from_proto(const trading::data::proto::ProtoHeartbeatAck& proto) {
	sequence_ = proto.sequence();
}


trading::data::proto::ProtoHeartbeatAck HeartbeatAck::to_proto(void) const {
	proto::ProtoHeartbeatAck hb;
	hb.set_sequence(sequence_);
	return std::move(hb); // protobuf doesn't actually support move semantics yet :(
}

}
}
