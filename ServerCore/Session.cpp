#include "pch.h"
#include "Session.h"
#include <cstring>

void Session::Dispatch(IocpEvent* iocpEvent, int numOfBytes)
{
	switch (iocpEvent->eventType)
	{
	case eEventType::SEND:
		NBSend("dispatch");
		break;
	case eEventType::RECV:
		NBRecv();
		break;
	default:

	}
}

void Session::Connect()
{
	mAddr.sin_family = AF_INET;
	mAddr.sin_port = ::htons(7777);
	inet_pton(AF_INET, "127.0.0.1", &mAddr.sin_addr);

	if (::connect(mSocket, (SOCKADDR*)&mAddr, sizeof(mAddr)) == SOCKET_ERROR)
		SocketUtils::HandleError("Connect");
}

void Session::NBSend(const char* str)
{
	strcpy_s(mSendBuf, str);
	WSABUF wsaBuf;
	wsaBuf.buf = mSendBuf;
	wsaBuf.len = sizeof(mSendBuf);

	DWORD bytes;
	::WSASend(mSocket, &wsaBuf, 1, &bytes, 0, &mSendEvent, 0);
}

void Session::NBRecv()
{
	WSABUF wsaBuf;
	wsaBuf.buf = mRecvBuf;
	wsaBuf.len = sizeof(mRecvBuf);

	DWORD numOfBytes;
	DWORD flag = 0;
	::WSARecv(mSocket, &wsaBuf, 1, &numOfBytes, &flag, &mRecvEvent, nullptr);

	cout << mRecvBuf << endl;
}

void Session::Recv()
{
	if (::recv(mSocket, mRecvBuf, sizeof(mRecvBuf), 0) <= 0)
		SocketUtils::HandleError("Recv");

	cout << mRecvBuf << endl;
}

