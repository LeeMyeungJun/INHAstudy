#include "stdafx.h"



RoomManager::RoomManager()
{
	m_UserCount = 0;
}


RoomManager::~RoomManager()
{
}

void RoomManager::setRoomName(char * RoomName)
{
	memset(this->m_RoomName, 0, _msize(RoomName));
	memcpy(this->m_RoomName, RoomName, _msize(RoomName));
}

char * RoomManager::getRoomName()
{
	return this->m_RoomName;
}

int RoomManager::AddUser(WPARAM wParam)
{
	if (m_UserCount >= 3)
		return -1; //추가실패

	m_RoomUseer.push_back(wParam);
	m_UserCount++;

	return m_UserCount;//추가성공
}

int RoomManager::ExitUser(WPARAM wParam)
{
	for (int i = 0; i < m_RoomUseer.size(); i++)
	{
		if (m_RoomUseer[i] == wParam)
		{
			m_RoomUseer.erase(m_RoomUseer.begin() + i);
			m_UserCount--;
			return m_UserCount;
		}
	}

	return -1;
}

int RoomManager::getUserCount()
{
	return m_UserCount;
}
