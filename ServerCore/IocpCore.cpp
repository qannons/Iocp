#include "pch.h"
#include "IocpCore.h"

void IocpCore::Register(IocpObjectRef iocpObject)
{
	if (::CreateIoCompletionPort(iocpObject->GetHandle(), mHandle, 0, 0) == NULL)
		SocketUtils::HandleError("Register");
}

void IocpCore::Dispatch()
{
<<<<<<< HEAD
	DWORD numOfBytes = 0;
	ULONG_PTR key = 0;
	IocpEvent* iocpEvent = nullptr;
	if (::GetQueuedCompletionStatus(mHandle, OUT & numOfBytes, OUT & key, OUT reinterpret_cast<LPOVERLAPPED*>(&iocpEvent), INFINITE))
=======
	DWORD numOfBytes;
	ULONG_PTR key;

	IocpEvent* iocpEvent;
	if (::GetQueuedCompletionStatus(mHandle, &numOfBytes, &key, (LPOVERLAPPED*)&iocpEvent, INFINITE))
>>>>>>> df37140cdd791fe3da6d1dadb6b961f4c89e2939
	{
		IocpObjectRef iocpObject = iocpEvent->owner;
		iocpObject->Dispatch(iocpEvent, numOfBytes);
	}
<<<<<<< HEAD
}

void IocpCore::AddSession(SessionRef session)
{
	mSessions.push_back(session);
=======

	else
	{
		SocketUtils::HandleError("dispatch");
	}
>>>>>>> df37140cdd791fe3da6d1dadb6b961f4c89e2939
}
