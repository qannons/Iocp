#pragma once
#include "IocpEvent.h"
#include "IocpCore.h"
#include "SocketUtils.h"

class Session : public IocpObject
{
	friend class Listener;

public:
	Session() 
	{
		//mSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		SocketUtils::SetReuseAddress(mSocket, true);
	}

public:
	virtual HANDLE GetHandle(void) override { return (HANDLE)mSocket; };
	virtual void Dispatch(class IocpEvent* iocpEvent, int numOfBytes) override;

public:
	void Connect();

	void Send(const char* str);

	void Recv();

private:
	void RegisterRecv();
	void ProcessRecv(int numofBytes);

public:
	SOCKET mSocket = INVALID_SOCKET;

private:
	char mSendBuf[1024];
	char mRecvBuf[1024];

	SOCKADDR_IN mAddr;

private:
	SendEvent mSendEvent;
	RecvEvent mRecvEvent;
	ConnectEvent mConnectEvent;
};

