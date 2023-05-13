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
	mAddr.sin_family = AF_INET;
	mAddr.sin_port = ::htons(9898);
	inet_pton(AF_INET, "127.0.0.1", &mAddr.sin_addr);
	if (::bind(mSocket, (SOCKADDR*)&mAddr, sizeof(mAddr)) == SOCKET_ERROR)
	{
		SocketUtils::HandleError("Connect Bind");
	}

	if (::connect(mSocket, (SOCKADDR*)&mAddr, sizeof(mAddr)) == SOCKET_ERROR)
		SocketUtils::HandleError("Connect");
}

void Session::NBSend(const char* str)
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

void Session::BSend(const char* str)
{
	strcpy_s(mSendBuf, str);
	if (::send(mSocket, mSendBuf, sizeof(mSendBuf), 0) <= 0)
		SocketUtils::HandleError("Send");
}

void Session::NBRecv()
{
	RegisterRecv();
}

void Session::BRecv()
{
	if (::recv(mSocket, mRecvBuf, sizeof(mRecvBuf), 0) <= 0)
		SocketUtils::HandleError("Recv");

	cout << mRecvBuf << endl;
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

