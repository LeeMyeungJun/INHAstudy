#pragma once
class RoomManager
{
private:
	int m_UserCount;
	char* m_RoomName;

public:
	RoomManager();
	~RoomManager();

	std::vector<SOCKET> m_RoomUseer;
	void setRoomName(char* RoomName);
	char* getRoomName();
	int AddUser(WPARAM wParam);
	int ExitUser(WPARAM wParam);
	int getUserCount();
};

        