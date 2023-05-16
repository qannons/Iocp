#pragma once

class IocpObject : public enable_shared_from_this<IocpObject>
{
public:
	virtual HANDLE GetHandle() abstract;
	virtual void Dispatch(class IocpEvent* iocpEvent, int numOfBytes) abstract;
};

class IocpCore
{
public:
	IocpCore() 
	{
		mHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
		ASSERT_CRASH(mHandle == INVALID_HANDLE_VALUE);
	}

public:
	HANDLE GetHandle() { return mHandle; }
	int GetSessionCount(void) { return mSessions.size(); }

public:
	void Register(IocpObjectRef iocpObject);
	void Dispatch();

	void AddSession(SessionRef session);

	void fn(const char* str);
//private:
public:
	HANDLE mHandle;
	vector<SessionRef> mSessions;
};

