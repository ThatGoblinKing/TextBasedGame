#include "Rooms.cpp"

int main()
{
	int playerPos[2] = {0, 0};
	Room testRoom[50];
	Room roomIn;
	while (1)
	{
		for (Room currentRoom : testRoom)
		{
			if (currentRoom.inRoom(playerPos[0], playerPos[1]))
			{
				roomIn = currentRoom;
				break;
			}
		}
		roomIn.describe();
		switch (roomIn.move())
		{
		case 0:
			playerPos[1]++;
			break;
		case 1:
			playerPos[0]++;
			break;
		case 2:
			playerPos[1]--;
			break;
		case 3:
			playerPos[0]--;
			break;
		}
	}
}