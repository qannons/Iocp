#pragma once

class IocpObject : public enable_shared_from_this<IocpObject>
{
public:
	virtual HANDLE GetHandle() abstract;
	virtual void Dispatch(IocpEvent* iocpEvent, int numOfBytes) abstract;
};

class IocpCore
{
public:
	IocpCore() { mHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0); }

public:
	HANDLE GetHandle() { return mHandle; }

public:
	void Register(IocpObjectRef iocpObject);
	void Dispatch();

private:
	HANDLE mHandle;
};

