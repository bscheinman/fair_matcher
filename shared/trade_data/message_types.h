#ifndef MESSAGE_TYPES_H_
#define MESSAGE_TYPES_H_

namespace trading {
namespace data {
	
	typedef enum MessageType {
		MT_Raw = 0,
		MT_Heartbeat = 1,
		MT_HeartbeatAck = 2,
		MT_Order = 3,
		MT_OrderAck = 4,
		MT_Trade = 5
	} MessageType;

}
}


#endif /* MESSAGE_TYPES_H_ */
