#include "pch.h"
#include "Listener.h"

int main()
{
	WSADATA wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), OUT & wsaData) != 0)
		return -1;

	IocpCoreRef iocpCore = make_shared<IocpCore>();

	Listener listener(iocpCore);
	listener.Start();
	
	SocketUtils::Init();
	

	vector<thread> v;
	v.push_back(thread([=]()
		{
			while(true)
				iocpCore->Dispatch();
		}
	));


	cout << "Here";

	for (thread& t : v)
	{
		if (t.joinable())
			t.join();
	}
	listener.End();

	return 0;
}