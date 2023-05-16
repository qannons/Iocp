#include "pch.h"
#include "IocpCore.h"

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
}

void IocpCore::AddSession(SessionRef session)
{
	mSessions.push_back(session);
}
