#include "pch.h"
#include "Listener.h"
#include "SessionManager.h"

int main()
{
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return 1;
	}
	
	Listener listener;

	listener.Start();
	while (true)
	{
		GSessionManager->Recv();

	}

	listener.End();

	return 0;
}