#pragma once
class RoomManager
{
private:
	std::vector<SOCKET> m_RoomUseer;
	int m_UserCount;
	char* m_RoomName;

public:
	RoomManager();
	~RoomManager();
	void setRoomName(char* RoomName);
	char* getRoomName();
	int AddUser(WPARAM wParam);
	int ExitUser(WPARAM wParam);
	int getUserCount();
};

        