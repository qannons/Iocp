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
	
	IocpCoreRef iocpCore = make_shared<IocpCore>();

	Listener listener(iocpCore);
	listener.Start();
	
	vector<thread> v;
	v.push_back(thread([=]()
		{
			while(true)
				iocpCore->Dispatch();
		}
	));

	listener.End();

	//for (thread& t : v)
	//{
	//	if (t.joinable())
	//		t.join();
	//}

	return 0;
}