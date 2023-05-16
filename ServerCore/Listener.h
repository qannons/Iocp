#pragma once

class Listener
{
public:
	Listener(IocpCoreRef pCore);
	~Listener();

public:
	void Start();
	void End();

private:
	void fn();

private:
	IocpCoreRef mCore = nullptr;
	SOCKET mSocket = INVALID_SOCKET;
	SOCKADDR_IN mAddr;

private:
	thread* mWorker = nullptr;
};


