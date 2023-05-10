#include "pch.h"
#include "CoreGlobal.h"
#include "SessionManager.h"

SessionManager* GSessionManager = nullptr;

class CoreGlobal
{
public:
	CoreGlobal()
	{
		GSessionManager = new SessionManager();
	}

	~CoreGlobal()
	{
		delete GSessionManager;
	}
} GCoreGlobal;