#include "pch.h"

int main()
{
	this_thread::sleep_for(1s);

	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	Session s;
	s.Connect();
	cout << "Connected!" << endl;

	char msg[1024];

	while (true)
	{
		cout << "Input: " << endl;
		cin.getline(msg, 1024);

		s.NBSend(msg);
		cout << "Send";
	}
	return 0;
}