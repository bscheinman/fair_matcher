#ifndef HEARTBEAT_ACK_H_
#define HEARTBEAT_ACK_H_

#include "proto_wrapper.h"
#include "heartbeat_ack.pb.h"

namespace trading {
namespace data {

class HeartbeatAck : public ProtoWrapper<
		trading::data::proto::ProtoHeartbeatAck,
		trading::data::MessageType::MT_HeartbeatAck> {
public:
	HeartbeatAck(void);
	HeartbeatAck(unsigned int sequence) : sequence_(sequence) { }
	HeartbeatAck(const trading::data::proto::ProtoHeartbeatAck& heartbeat);
	virtual void copy_from_proto(const trading::data::proto::ProtoHeartbeatAck& heartbeat) override;
	virtual trading::data::proto::ProtoHeartbeatAck to_proto(void) const override;

	unsigned int sequence(void) const { return sequence_; }
private:
	unsigned int sequence_;
};

}
}


#endif /* HEARTBEAT_ACK_H_ */
