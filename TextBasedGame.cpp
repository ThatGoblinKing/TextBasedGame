#include "Room.cpp"
#include "MapInitalizer.cpp"

static void parseRoom(string rawRoom);
Room parsedRoom;

int main()
{
	vector<string> rawMap = getRawMap();
	const int MAP_SIZE = rawMap.size();
	int playerPos[2] = {0, 0};
	Room outOfBounds = Room();
	Room map[MAP_SIZE];
	for(int i = 0; i < MAP_SIZE; i++){
		parseRoom(rawMap[i]);
		map[i] = parsedRoom;
	}
	Room roomIn;
	while (1)
	{
		for (Room currentRoom : map)
		{
			if (currentRoom.inRoom(playerPos[0], playerPos[1]))
			{
				roomIn = currentRoom;
				break;
			} else {
				roomIn = outOfBounds;
			}
				
		}
		roomIn.describe();
		cout << "You are at: (" << playerPos[0] << ", " << playerPos[1] << ")" << endl;
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

static void parseRoom(string rawRoom){
    string segment[7];
    string delimeter = "|";
    for (int i = 0; i < 7; i++){
        segment[i] = rawRoom.substr(0, rawRoom.find(delimeter));
	    rawRoom.erase(0, rawRoom.find(delimeter) + delimeter.length());
    }
	parsedRoom = Room(segment[0], stoi(segment[1]), stoi(segment[2]), segment[3] != "false", segment[4] != "false", segment[5] != "false", segment[6] != "false");
}

/* 
To do:
add more actions:
	check GPS

add events:
	Shops
	Fights
	Misc Encounters
	NPCs

Plan the story...
Add rooms in

event could be an object, with inheritence. 
"EventRoom" could be a subclass of Room.

*/