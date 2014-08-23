#ifndef HEARTBEAT_H_
#define HEARTBEAT_H_

#include "proto_wrapper.h"
#include "heartbeat.pb.h"

namespace trading {
namespace data {

class Heartbeat : public ProtoWrapper<
		trading::data::proto::ProtoHeartbeat,
		trading::data::MessageType::MT_Heartbeat> {
public:
	Heartbeat(void) { }
	Heartbeat(unsigned int sequence) : sequence_(sequence) { }
	Heartbeat(const trading::data::proto::ProtoHeartbeat& heartbeat);
	virtual void copy_from_proto(const trading::data::proto::ProtoHeartbeat& heartbeat) override;
	virtual trading::data::proto::ProtoHeartbeat to_proto(void) const override;

	unsigned int sequence(void) const { return sequence_; }
	void sequence(unsigned int s) { sequence_ = s; }
private:
	unsigned int sequence_;
};

}
}

#endif /* HEARTBEAT_H_ */
