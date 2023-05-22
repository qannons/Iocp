#include "pch.h"
#include "IocpCore.h"
#include "Session.h"

void IocpCore::Register(IocpObjectRef iocpObject)
{
	if (::CreateIoCompletionPort(iocpObject->GetHandle(), mHandle, 0, 0) == NULL)
		SocketUtils::HandleError("Register");
}

void IocpCore::Dispatch()
{
	DWORD numOfBytes = 0;
	ULONG_PTR key = 0;
	IocpEvent* iocpEvent = nullptr;
	if (::GetQueuedCompletionStatus(mHandle, OUT & numOfBytes, OUT & key, OUT reinterpret_cast<LPOVERLAPPED*>(&iocpEvent), INFINITE))
	{
		IocpObjectRef iocpObject = iocpEvent->owner;
		iocpObject->Dispatch(iocpEvent, numOfBytes);
	}
	else
	{
		IocpObjectRef iocpObject = iocpEvent->owner;
		iocpObject->Dispatch(iocpEvent, numOfBytes);
	}
}

void IocpCore::AddSession(SessionRef session)
{
	mSessions.insert(session);
}

void IocpCore::EraseSession(SessionRef session)
{
	mSessions.erase(session);
}

void IocpCore::fn(const char* str)
{
	for (auto i : mSessions)
	{
		i->Send(str);
	}
}
