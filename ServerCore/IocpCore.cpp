#include "pch.h"
#include "IocpCore.h"

void IocpCore::Register(IocpObjectRef iocpObject)
{
	if (::CreateIoCompletionPort(iocpObject->GetHandle(), mHandle, 0, 0) == NULL)
		SocketUtils::HandleError("Register");
}

void IocpCore::Dispatch()
{
	DWORD numOfBytes;
	ULONG_PTR key;

	IocpEvent* iocpEvent;
	if (::GetQueuedCompletionStatus(mHandle, &numOfBytes, &key, (LPOVERLAPPED*)&iocpEvent, INFINITE))
	{
		IocpObjectRef iocpObject = iocpEvent->owner;
		iocpObject->Dispatch(iocpEvent, numOfBytes);
	}

	else
	{
		SocketUtils::HandleError("dispatch");
	}
}
