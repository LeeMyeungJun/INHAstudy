#include "stdafx.h"
#include <stdlib.h>
#include <string>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#define Buf_Size 1024

struct UserInfo
{
	char chName[10];
	char chMessage[Buf_Size];
};




void Error(char* msg);
void Log(char * msg);

char strServerIP[] = "165.246.192.72";
char strClientIP[] = "127.0.0.1";
char strPort[] = "12345";

void Server_code();
int main()
{
	Server_code();

	return 0;
}
void Error(char* msg)
{
	Log(msg);
	exit(1);
}
void Log(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
}
void Server_code()
{
	WSADATA wsaData;
	SOCKET serverSocket, clientSocket;
	char msg[Buf_Size];
	int strLength, i;

	SOCKADDR_IN serverAddr, clientAddr;
	int clientAddrSize;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //버전정보 2, 2버전?
		Error("WSAStartup error");

	serverSocket = socket(PF_INET, SOCK_STREAM, 0); //소켓정보 PF_INET는 주소체계 TCP는 보내고 받아줘야함  UDP 보내고나서 신경안씀
	if (serverSocket == INVALID_SOCKET)
		Error("socket() error");

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(atoi(strPort));

	if (bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr))
		== SOCKET_ERROR)
		Error("bind() error");
	Log("bind() ok");

	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
		Error("listen() error");
	Log("listen() ok");

	clientAddrSize = sizeof(clientAddr);
	memset(msg, 0, sizeof(msg));
	for (int i = 0; i < SOMAXCONN; i++)
	{
		clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientAddrSize);
		Log("Accept()...");
		if (clientSocket == SOCKET_ERROR)
			Error("Accept() error");
		else
			printf("Connected client %d \n", i + 1);
		while ((strLength = recv(clientSocket, msg, Buf_Size, 0)) != 0)
		{
			printf("%d client : %s", i + 1, msg);
			send(clientSocket, msg, strLength, 0); //클라이언트 
			memset(msg, 0, sizeof(msg));
		}
		closesocket(clientSocket);
	}
	closesocket(serverSocket);
	WSACleanup();
	Log("Finish ... ");
}