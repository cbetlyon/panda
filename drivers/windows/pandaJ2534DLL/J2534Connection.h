#pragma once
#include "panda/panda.h"
#include "J2534_v0404.h"
#include "J2534MessageFilter.h"

class J2534Connection {
public:
	J2534Connection(
		panda::Panda* panda_dev,
		unsigned long ProtocolID,
		unsigned long Flags,
		unsigned long BaudRate
	);
	~J2534Connection();
	virtual long PassThruReadMsgs(PASSTHRU_MSG *pMsg, unsigned long *pNumMsgs, unsigned long Timeout);
	virtual long PassThruWriteMsgs(PASSTHRU_MSG *pMsg, unsigned long *pNumMsgs, unsigned long Timeout);
	virtual long PassThruStartPeriodicMsg(PASSTHRU_MSG *pMsg, unsigned long *pMsgID, unsigned long TimeInterval);
	virtual long PassThruStopPeriodicMsg(unsigned long MsgID);

	virtual long PassThruStartMsgFilter(unsigned long FilterType, PASSTHRU_MSG *pMaskMsg, PASSTHRU_MSG *pPatternMsg,
		PASSTHRU_MSG *pFlowControlMsg, unsigned long *pFilterID);

	virtual long PassThruStopMsgFilter(unsigned long FilterID);
	virtual long PassThruIoctl(unsigned long IoctlID, void *pInput, void *pOutput);

	long init5b(SBYTE_ARRAY* pInput, SBYTE_ARRAY* pOutput);
	long initFast(PASSTHRU_MSG* pInput, PASSTHRU_MSG* pOutput);
	long clearTXBuff();
	long clearRXBuff();
	long clearPeriodicMsgs();
	long clearMsgFilters();
	long clearFunctMsgLookupTable(PASSTHRU_MSG* pInput);
	long addtoFunctMsgLookupTable(PASSTHRU_MSG* pInput);
	long deleteFromFunctMsgLookupTable();

	long setBaud(unsigned long baud);
	unsigned long getBaud();

	unsigned long getProtocol();

	bool isProtoCan();

	unsigned long getPort();

	void processMessage(const PASSTHRU_MSG_INTERNAL& msg);

	bool loopback = FALSE;

protected:
	unsigned long ProtocolID;
	unsigned long Flags;
	unsigned long BaudRate;
	unsigned long port;

	//Should only be used while the panda device exists, so a pointer should be ok.
	panda::Panda* panda_dev;

	std::queue<PASSTHRU_MSG_INTERNAL> messages;

	std::array<std::unique_ptr<J2534MessageFilter>, 10> filters;

	CRITICAL_SECTION message_access_lock;
};