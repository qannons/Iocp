#pragma once
#pragma comment(lib, "ws2_32.lib")

using namespace std;

#include "Types.h"
#include "CoreMacro.h"
#include "CoreTLS.h"
#include "CoreGlobal.h"

//소켓 프로그래밍 라이브러리
#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>

#include <windows.h>
#include <iostream>
#include <thread>

#include <vector>
#include <string>
#include <set>

#include "Session.h"
#include "SocketUtils.h"