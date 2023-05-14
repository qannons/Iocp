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
<<<<<<< HEAD
	SOCKET mSocket = INVALID_SOCKET;
	SOCKADDR_IN mAddr;

private:
	thread* mWorker = nullptr;
=======

	vector<SessionRef> v;
>>>>>>> df37140cdd791fe3da6d1dadb6b961f4c89e2939
};


