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
	IocpEvent(eEventType pEventType) : eventType(pEventType) {};

public:
	eEventType eventType;
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
