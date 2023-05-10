#pragma once

class SessionManager
{
public:

public:
	void Register(SessionRef s);
	void Recv();

private:
	vector<SessionRef> mSessions;
	HANDLE mHandle;
};

