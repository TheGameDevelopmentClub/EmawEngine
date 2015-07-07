// James Tyson
#include "stdafx.h"
#include "ClientNetwork.h"

// Default Constructor
ClientNetwork::ClientNetwork() {

	// create WSADATA object
	WSADATA wsaData;

	// socket
	ConnectSocket = INVALID_SOCKET;

	// holds address info for socket to connect to
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		// fatal error
	}



	// set address info
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;  //TCP connection!!!

	//resolve server address and port 
	iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);

	if (iResult != 0)
	{
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		// fatal error
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);

		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			//fatal error
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

		if (iResult == SOCKET_ERROR)
		{
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			printf("The server is down... did not connect");
		}
	}

	// no longer need address info for server
	freeaddrinfo(result);



	// if connection failed
	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Unable to connect to server!\n");
		WSACleanup();
		// fatal error
	}

	// Set the mode of the socket to be nonblocking
	u_long iMode = 1;

	iResult = ioctlsocket(ConnectSocket, FIONBIO, &iMode);
	if (iResult == SOCKET_ERROR)
	{
		printf("ioctlsocket failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		//fatal error
	}

	//disable nagle - optional
	char value = 1;
	setsockopt(ConnectSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));

}

// Closes the connection to the server.
void ClientNetwork::close() {
	closesocket(ConnectSocket);
	WSACleanup();
}

// Default destructor.
ClientNetwork::~ClientNetwork() {
	close();
}

// Receive packets from the server.
int ClientNetwork::receivePackets(char * recvbuf)
{
	iResult = NetworkServices::receiveMessage(ConnectSocket, recvbuf, MAX_PACKET_SIZE);

	if (iResult == 0)
	{
		printf("Connection closed\n");
		closesocket(ConnectSocket);
		WSACleanup();
		//fatal error
	}

	return iResult;
}