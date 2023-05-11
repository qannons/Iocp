#pragma once
#include "IocpEvent.h"
#include "IocpCore.h"

class Session : public IocpObject
{
	friend class Listener;

public:
	Session() 
	{
		mSocket = socket(AF_INET, SOCK_STREAM, 0);
	}

public:
	virtual HANDLE GetHandle(void) override { return (HANDLE)mSocket; };
	virtual void Dispatch(IocpEvent* iocpEvent, int numOfBytes) override;
public:
	void Connect();
	void NBSend(const char* str);
	void NBRecv();
	void Recv();

private:

private:
	SOCKET mSocket = INVALID_SOCKET;

private:
	char mSendBuf[1024];
	char mRecvBuf[1024];

	SOCKADDR_IN mAddr;

private:
	SendEvent mSendEvent;
	RecvEvent mRecvEvent;
};

