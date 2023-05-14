#include "pch.h"
#include "Listener.h"

int main()
{
	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return 1;
	}
	
	IocpCoreRef iocpCore = make_shared<IocpCore>();
	Listener listener(iocpCore);

	listener.Start();

	while (true)
	{
		iocpCore->Dispatch();
	}
	listener.End();

	return 0;
}