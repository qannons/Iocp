#pragma once

class Listener
{
public:
	Listener();
	~Listener();
public:
	void Start();
	void End();

private:
	void fn();

private:
	SOCKET mSocket = INVALID_SOCKET;
	thread* mWorker;
	SOCKADDR_IN mAddr;
};

