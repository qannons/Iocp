#pragma once

class Session
{
public:
	Session() 
	{
		mSocket = socket(AF_INET, SOCK_STREAM, 0);
	}

public:
	void Connect();
	void Send(const char* str);
	void Recv();

private:
	SOCKET mSocket = INVALID_SOCKET;

private:
	char mSendBuf[1024];
	SOCKADDR_IN mAddr;
};

