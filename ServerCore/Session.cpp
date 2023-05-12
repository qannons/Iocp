#include "pch.h"
#include "Session.h"
#include <cstring>

void Session::Dispatch(IocpEvent* iocpEvent, int numOfBytes)
{
	switch (iocpEvent->eventType)
	{
	case eEventType::SEND:
		Send("dispatch");
		break;
	case eEventType::RECV:
		//Recv();
		tmpRecv();
		break;
	default:
		cout << "Default";
		break;
	}
}

void Session::Connect()
{
	mAddr.sin_family = AF_INET;
	mAddr.sin_port = ::htons(7777);
	inet_pton(AF_INET, "127.0.0.1", &mAddr.sin_addr);

	auto a = shared_from_this();

	mConnectEvent.owner = shared_from_this();

	DWORD numOfBytes = 0;
	if (false == SocketUtils::ConnectEx(mSocket, reinterpret_cast<SOCKADDR*>(&mAddr), sizeof(mAddr), nullptr, 0, &numOfBytes, &mConnectEvent))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			mConnectEvent.owner = nullptr; // RELEASE_REF
		}
	}
}

void Session::Send(const char* str)
{
	if (mSocket == INVALID_SOCKET)
	{
		// 소켓이 유효하지 않음
		cout << "Tlqkf";
	}
	
	
	mSendEvent.owner = shared_from_this();

	strcpy_s(mSendBuf, str);
	WSABUF wsaBuf;
	wsaBuf.buf = mSendBuf;
	wsaBuf.len = sizeof(mSendBuf);

	DWORD bytes;
	if (::WSASend(mSocket, &wsaBuf, 1, &bytes, 0, &mSendEvent, 0) == SOCKET_ERROR)
	{
		SocketUtils::HandleError("Send error code: ");
		//ASSERT_CRASH(false);
	}
}

void Session::Recv()
{
	mRecvEvent.owner = shared_from_this();

	WSABUF wsaBuf;
	wsaBuf.buf = mRecvBuf;
	wsaBuf.len = sizeof(mRecvBuf);

	DWORD numOfBytes;
	DWORD flag = 0;
	if (::WSARecv(mSocket, &wsaBuf, 1, &numOfBytes, &flag, &mRecvEvent, nullptr) == SOCKET_ERROR)
		SocketUtils::HandleError("Recv");

	cout << "WSARecv called" << endl;
}