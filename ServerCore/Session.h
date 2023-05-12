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
		//mSocket = socket(AF_INET, SOCK_STREAM, 0);
	}

public:
	virtual HANDLE GetHandle(void) override { return (HANDLE)mSocket; };
	virtual void Dispatch(IocpEvent* iocpEvent, int numOfBytes) override;

public:
	void Connect();
	void Send(const char* str);
	void Recv();

public:
	void tmpRecv()
	{
		WSABUF wsaBuf;
		wsaBuf.buf = mRecvBuf;
		wsaBuf.len = sizeof(mRecvBuf);

		DWORD numOfBytes;
		DWORD flag = 0;
		if (::recv(mSocket, mRecvBuf, sizeof(mRecvBuf), 0) == SOCKET_ERROR)
			SocketUtils::HandleError("tmpRecv");

		cout << mRecvBuf << endl;
	}

//private:
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

