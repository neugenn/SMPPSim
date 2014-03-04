#ifndef PDU_TYPE_H_
#define PDU_TYPE_H_

namespace SMPP
{
	enum PduType
	{
		BindReceiver = 0x00000001,
		BindReceiverResp = 0x80000001,
		BindTransmitter = 0x00000002,
		BindTransmitterResp = 0x80000002,
		QyerySm = 0x0000003,
		QyerySmResp = 0x8000003,
		SubmitSm = 0x00000004,
		SubmitSmResp = 0x80000004,
		DeliverSm = 0x00000005,
		DeliverSmResp = 0x80000005
	};
}

#endif // PDU_TYPE_H_
