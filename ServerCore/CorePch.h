#pragma once
#pragma comment(lib, "ws2_32.lib")

using namespace std;

#include "Types.h"
#include "CoreMacro.h"
#include "CoreTLS.h"

//���� ���α׷��� ���̺귯��
#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>

#include <windows.h>
#include <iostream>
#include <thread>

#include <vector>
#include <string>

#include "Session.h"
#include "SocketUtils.h"