#pragma once

class Listener
{
public:
	Listener(IocpCoreRef iocpCore);
	~Listener();
public:
	void Start();
	void End();

private:
	void fn();

private:
	SOCKET mSocket = INVALID_SOCKET;
	thread* mWorker = nullptr;
	SOCKADDR_IN mAddr;
	IocpCoreRef mCore = nullptr;
};


