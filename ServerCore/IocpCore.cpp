#include "pch.h"
#include "IocpCore.h"

void IocpCore::Register(IocpObjectRef iocpObject)
{
	if (::CreateIoCompletionPort(iocpObject->GetHandle(), mHandle, 0, 0) == NULL)
		SocketUtils::HandleError("Register");
}

void IocpCore::Dispatch()
{
	DWORD bytes;
	ULONG_PTR key;

	IocpEvent* iocpEvent;
	::GetQueuedCompletionStatus(mHandle, &bytes, &key, (LPOVERLAPPED*)&iocpEvent, INFINITE)
}
