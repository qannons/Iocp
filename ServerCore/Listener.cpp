#include "pch.h"
#include "Listener.h"
#include "IocpCore.h"

Listener::Listener(IocpCoreRef pCore) : mCore(pCore)
{
	mSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

	mAddr.sin_family = AF_INET;
	mAddr.sin_port = ::htons(7777);
	inet_pton(AF_INET, SERVER_ADDR, &mAddr.sin_addr);
}

Listener::~Listener()
{
	delete mWorker;
	SocketUtils::Close(mSocket);
}

void Listener::Start()
{
	int sizeAddr = sizeof(mAddr);
	SocketUtils::SetReuseAddress(mSocket, true);
	if (::bind(mSocket, (SOCKADDR*)&mAddr, sizeAddr) == SOCKET_ERROR)
		SocketUtils::HandleError("Bind");

	if (::listen(mSocket, SOMAXCONN) == SOCKET_ERROR)
		SocketUtils::HandleError("Listen");

	mWorker = new thread(&Listener::fn, this);
}

void Listener::End()
{
	mWorker->join();
}

void Listener::fn()
{
	while (true)
	{
		int sizeAddr = sizeof(mAddr);
		SOCKET socket = ::accept(mSocket, (SOCKADDR*)&mAddr, &sizeAddr);
		SocketUtils::SetReuseAddress(socket, true);

		if (socket == INVALID_SOCKET)
		{
			SocketUtils::HandleError("socket");
			continue;
		}

		cout << "Connected!\n";
		SessionRef session = make_shared<Session>();
		session->mSocket = socket;

		//mCore->Register(session);
		//mCore->AddSession(session);

		session->ProcessConnect();
	}
}
 

