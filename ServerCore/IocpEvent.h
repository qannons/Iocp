#pragma once

enum class eEventType
{
	SEND,
	RECV,
	CONNECT,
	DISCONNECT,
	ACCEPT
};

class IocpEvent : public OVERLAPPED
{
public:
	IocpEvent(eEventType pEventType) : eventType(pEventType) 
	{
		Init();
	};

	void			Init();

public:
	eEventType eventType;
<<<<<<< HEAD
	IocpObjectRef owner = nullptr;
=======
	IocpObjectRef owner;
>>>>>>> df37140cdd791fe3da6d1dadb6b961f4c89e2939
};

class SendEvent : public IocpEvent
{
public:
	SendEvent() : IocpEvent(eEventType::SEND) {}
};

class RecvEvent : public IocpEvent
{
public:
	RecvEvent() : IocpEvent(eEventType::RECV) {}
};

class ConnectEvent : public IocpEvent
{
public:
	ConnectEvent() : IocpEvent(eEventType::CONNECT) {}
};
