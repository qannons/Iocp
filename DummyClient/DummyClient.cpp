#include "pch.h"
#include "IocpCore.h"

int main()
{
	this_thread::sleep_for(1s);
	WSADATA wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), OUT & wsaData) != 0)
		return -1;

	SocketUtils::Init();

	SessionRef s = make_shared<Session>();
	s->mSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	//IocpCore iocpCore;
	//iocpCore.Register(s);

	s->Connect();
	cout << "Connected!" << endl;
	char msg[1024];

	while (true)
	{
		cout << "Input: " << endl;
		cin.getline(msg, 1024);

		s->Send(msg);
		cout << "Send";
	}
	return 0;
}