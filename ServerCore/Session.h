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
<<<<<<< HEAD
		//mSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		SocketUtils::SetReuseAddress(mSocket, true);
=======
		//mSocket = socket(AF_INET, SOCK_STREAM, 0);
>>>>>>> df37140cdd791fe3da6d1dadb6b961f4c89e2939
	}

public:
	virtual HANDLE GetHandle(void) override { return (HANDLE)mSocket; };
<<<<<<< HEAD
	virtual void Dispatch(class IocpEvent* iocpEvent, int numOfBytes) override;

public:
	void Connect();

=======
	virtual void Dispatch(IocpEvent* iocpEvent, int numOfBytes) override;

public:
	void Connect();
>>>>>>> df37140cdd791fe3da6d1dadb6b961f4c89e2939
	void Send(const char* str);

	void Recv();

<<<<<<< HEAD
private:
	void RegisterRecv();
	void ProcessRecv(int numofBytes);

=======
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
>>>>>>> df37140cdd791fe3da6d1dadb6b961f4c89e2939
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

