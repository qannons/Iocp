#include "pch.h"
#include "SessionManager.h"

void SessionManager::Register(SessionRef s)
{
	mSessions.push_back(s);
}

void SessionManager::Recv()
{
	for (auto session : mSessions)
	{
		session->Recv();
	}
}
