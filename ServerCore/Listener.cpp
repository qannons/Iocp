#include "pch.h"
#include "Listener.h"
#include "SessionManager.h"
#include "IocpCore.h"

Listener::Listener(IocpCoreRef iocpCore) : mCore(iocpCore)
{
	mSocket = socket(AF_INET, SOCK_STREAM, 0);

	mAddr.sin_family = AF_INET;
	mAddr.sin_port = ::htons(7777);
	inet_pton(AF_INET, "127.0.0.1", &mAddr.sin_addr);
}

Listener::~Listener()
{
	delete mWorker;
}

void Listener::Start()
{
	int sizeAddr = sizeof(mAddr);
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

		if (socket == INVALID_SOCKET)
			SocketUtils::HandleError("socket");

		SessionRef session = make_shared<Session>();
		session->mSocket = socket;

		mCore->Register(session);
		GSessionManager->Register(session);
	}
}
 

