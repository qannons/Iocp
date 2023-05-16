#include "pch.h"
#include "Session.h"
#include <cstring>

void Session::Dispatch(IocpEvent* iocpEvent, int numOfBytes)
{
	switch (iocpEvent->eventType)
	{
	case eEventType::RECV:
		ProcessRecv(numOfBytes);
	default:
		break;
	}
}

void Session::Connect()
{
	::memset(&mAddr, 0, sizeof(mAddr));
	mAddr.sin_family = AF_INET;
	::inet_pton(AF_INET, SERVER_ADDR, &mAddr.sin_addr);
	mAddr.sin_port = ::htons(7777);


	while (true)
	{
		if (::connect(mSocket, (SOCKADDR*)&mAddr, sizeof(mAddr)) == SOCKET_ERROR)
		{
			// 원래 블록했어야 했는데... 너가 논블로킹으로 하라며?
			if (::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			// 이미 연결된 상태라면 break
			if (::WSAGetLastError() == WSAEISCONN)
				break;
			// Error
			SocketUtils::HandleError("Connect");
			break;
		}
		RegisterRecv();
	}

	cout << "Connected to Server!" << endl;
}

void Session::Send(const char* str)
{
	mSendEvent.Init();
	mSendEvent.owner = shared_from_this();

	strcpy_s(mSendBuf, str);
	WSABUF wsaBuf;
	wsaBuf.buf = mSendBuf;
	wsaBuf.len = sizeof(mSendBuf);

	DWORD bytes;
	if (::WSASend(mSocket, &wsaBuf, 1, &bytes, 0, &mSendEvent, 0) == SOCKET_ERROR)
	{
		int errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			SocketUtils::HandleError("NBSend");
			mSendEvent.owner = nullptr; // RELEASE_REF
		}
	}
}

void Session::Recv()
{
	RegisterRecv();
}

void Session::RegisterRecv()
{
	mRecvEvent.Init();
	mRecvEvent.owner = shared_from_this();

	WSABUF wsaBuf;
	wsaBuf.buf = mRecvBuf;
	wsaBuf.len = sizeof(mRecvBuf);

	DWORD numOfBytes = 0;
	DWORD flags = 0;
	if (::WSARecv(mSocket, &wsaBuf, 1, &numOfBytes, &flags, &mRecvEvent, nullptr) == SOCKET_ERROR)
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			SocketUtils::HandleError("RegisterRecv");
			mRecvEvent.owner = nullptr; // RELEASE_REF
		}
	}
}

void Session::ProcessRecv(int numofBytes)
{
	if (numofBytes == 0)
		cout << "Disconnected!";

	cout << mRecvBuf << endl;

	RegisterRecv();
}

