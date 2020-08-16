#include "stdafx.h"


extern char g_player;
extern char g_turn;
extern char boardState[19][19];
ServerManager::ServerManager()
{
	BWturn = true;
}


ServerManager::~ServerManager()
{
}

void ServerManager::Read_Fd()
{
	int position[3];
	memset(buffer, 0, sizeof(buffer));
	msgLen = recv(server, buffer, 100, 0); //받아오는곳 
	buffer[msgLen] = NULL;
	size_t stlength = strlen(buffer);
	TCHAR tchturn[10] = { 0 };
	TCHAR * newMsg = new TCHAR[stlength + 1];
	sprintf(newMsg, TEXT("%s"), buffer);
	if (newMsg[0] == '_')
	{
		g_player = newMsg[1];
		g_turn = newMsg[2];
	}
	else if (newMsg[0] == '(' &&newMsg[1] == 't')
	{
		g_turn = 't';
	}
	else
	{
		if (newMsg[4] == ':')
		{
			chatLog.push_back(newMsg);
		}
		else
		{
			position[0] = atoi(newMsg);
			position[1] = position[0] % 1000;
			position[2] = (position[0] - position[1]) / 1000;

			if (boardState[position[1]][position[2]] == 'b' || boardState[position[1]][position[2]] == 'w')
			{
				strcpy(tchturn, "(t");
				strcpy_s(buffer, tchturn);
				send(server, (LPSTR)buffer, strlen(buffer), 0);
				g_turn = '\0';
			}
			else
			{
				if (g_player == 'b')
				{
					boardState[position[1]][position[2]] = 'w';
				}
				else if (g_player == 'w')
				{
					boardState[position[1]][position[2]] = 'b';
				}
				else if(g_player =='o')
				{
					if (BWturn)
					{
						boardState[position[1]][position[2]] = 'w';
						BWturn = !BWturn;
					}
					else
					{
						boardState[position[1]][position[2]] = 'b';
						BWturn = !BWturn;

					}
				}
				g_turn = 't';
			}
		}
	}

	InvalidateRect(hWnd, NULL, TRUE);
}

void ServerManager::Init()
{
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	server = socket(AF_INET, SOCK_STREAM, 0);
	if (server == INVALID_SOCKET)
	{
		MessageBox(NULL, _T("socket faield"), _T("Error"), MB_OK);
		return;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = 20;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (connect(server, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		MessageBox(NULL, _T("connect failed"), _T("Error"), MB_OK);
		return;
	}
	WSAAsyncSelect(server, hWnd, WM_ASYNC, FD_READ);
}
