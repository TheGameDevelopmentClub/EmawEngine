// James Tyson
#pragma once
#pragma comment(lib, "Ws2_32.lib")

#include <WinSock2.h>
#include <Windows.h>
#include "NetworkData.h"
#include "Packets.h"

namespace EmawEngineServer {
	class NetworkServices
	{
	public:
		__declspec(dllexport) static int sendMessage(SOCKET curSocket, char* message, int messageSize);
		__declspec(dllexport) static int receiveMessage(SOCKET curSocket, char* buffer, int bufsize);
	};
}