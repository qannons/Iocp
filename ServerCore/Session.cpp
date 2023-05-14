#include "pch.h"
#include "Session.h"
#include <cstring>

void Session::Dispatch(IocpEvent* iocpEvent, int numOfBytes)
<<<<<<< HEAD
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
	::inet_pton(AF_INET, "127.0.0.1", &mAddr.sin_addr);
	mAddr.sin_port = ::htons(7777);


	while (true)
	{
		if (::connect(mSocket, (SOCKADDR*)&mAddr, sizeof(mAddr)) == SOCKET_ERROR)
		{
			// ���� ����߾�� �ߴµ�... �ʰ� ����ŷ���� �϶��?
			if (::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			// �̹� ����� ���¶�� break
			if (::WSAGetLastError() == WSAEISCONN)
				break;
			// Error
			SocketUtils::HandleError("Connect");
			break;
		}
	}

	cout << "Connected to Server!" << endl;
}

void Session::Send(const char* str)
{
	mSendEvent.Init();
=======
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
		// ������ ��ȿ���� ����
		cout << "Tlqkf";
	}
	
	
>>>>>>> df37140cdd791fe3da6d1dadb6b961f4c89e2939
	mSendEvent.owner = shared_from_this();

	strcpy_s(mSendBuf, str);
	WSABUF wsaBuf;
	wsaBuf.buf = mSendBuf;
	wsaBuf.len = sizeof(mSendBuf);

	DWORD bytes;
	if (::WSASend(mSocket, &wsaBuf, 1, &bytes, 0, &mSendEvent, 0) == SOCKET_ERROR)
	{
<<<<<<< HEAD
		int errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			SocketUtils::HandleError("NBSend");
			mSendEvent.owner = nullptr; // RELEASE_REF
		}
=======
		SocketUtils::HandleError("Send error code: ");
		//ASSERT_CRASH(false);
>>>>>>> df37140cdd791fe3da6d1dadb6b961f4c89e2939
	}
}

void Session::Recv()
{
<<<<<<< HEAD
	RegisterRecv();
}

void Session::RegisterRecv()
{
	mRecvEvent.Init();
=======
>>>>>>> df37140cdd791fe3da6d1dadb6b961f4c89e2939
	mRecvEvent.owner = shared_from_this();

	WSABUF wsaBuf;
	wsaBuf.buf = mRecvBuf;
	wsaBuf.len = sizeof(mRecvBuf);

<<<<<<< HEAD
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

=======
	DWORD numOfBytes;
	DWORD flag = 0;
	if (::WSARecv(mSocket, &wsaBuf, 1, &numOfBytes, &flag, &mRecvEvent, nullptr) == SOCKET_ERROR)
		SocketUtils::HandleError("Recv");

	cout << "WSARecv called" << endl;
}
>>>>>>> df37140cdd791fe3da6d1dadb6b961f4c89e2939
