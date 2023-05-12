#include "pch.h"
#include "CoreGlobal.h"

class CoreGlobal
{
public:
	void Start() { cout << "start"; }
public:
	CoreGlobal()
	{
		SocketUtils::Init();
	}

	~CoreGlobal()
	{
		SocketUtils::Clear();
	}
} GCoreGlobal;