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

	vector<thread> v;
	v.push_back(thread([=]()
		{
			while(true)
				iocpCore->Dispatch();
		}));

	char msg[1024];
	while (true)
	{
		cout << "Input: " << endl;
		cin.getline(msg, 1024);

		iocpCore->fn(msg);
	}

	listener.End();

	return 0;
}