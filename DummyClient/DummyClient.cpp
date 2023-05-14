#include "pch.h"

int main()
{
	this_thread::sleep_for(1s);

	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET Socket = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	SessionRef s = make_shared<Session>();
	s->mSocket = Socket;

	IocpCoreRef iocpCore = make_shared<IocpCore>();
	iocpCore->Register(s);

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