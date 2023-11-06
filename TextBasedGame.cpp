#include "Room.cpp"
#include "MapInitalizer.cpp"
#include <map>

static void parseRoom(string rawRoom);
static int coordsToNum(int x, int y);
Room parsedRoom;

int main()
{
	vector<string> rawMap = getRawMap();
	const int MAP_SIZE = rawMap.size();
	std::pair<int, int> playerPos (0, 0);
	std::pair<std::pair<int, int>, Room> insertion;
	Room outOfBounds = Room();
	std::map<std::pair<int,int>, Room> rooms;
	for(int i = 0; i < MAP_SIZE; i++) {
		parseRoom(rawMap.at(i));
		insertion.first = parsedRoom.getCoords();
		insertion.second = parsedRoom;
		rooms.insert(insertion);
	}
	Room roomIn;
	while (true)
	{
		roomIn = rooms[playerPos];
		rooms[playerPos].describe();
		//cout << "You are at: (" << playerPos.first << ", " << playerPos.second << ")" << endl;
		switch (roomIn.move())
		{
		case 0:
			playerPos.second++;
			break;
		case 1:
			playerPos.first++;
			break;
		case 2:
			playerPos.second--;
			break;
		case 3:
			playerPos.first--;
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
	try{
	parsedRoom = Room(segment[0], stoi(segment[1]), stoi(segment[2]), segment[3] != "false", segment[4] != "false", segment[5] != "false", segment[6] != "false");
	} catch(exception e) {
	}
}

static int coordsToNum(int x, int y){
	return x >= y ? x * x + x + y : x + y * y;
}


/* 
To do:
add more actions:
	check GPS (display coords)
	check inventory:
		Item object w/ inheritence for certain types (weapons, armor, etc.)
			Wouldn't need many functions, just variables.
				name
				damage
				durability
				quantity
				price
	better directional descriptions



add events: 
	Shops
	Fights
	Misc Encounters
	NPCs

Plan the story...
Add rooms in

event could be an object, with inheritence. 
"EventRoom" could be a subclass of Room.

Maybe rooms could be accessed via their coordinates by using a hash?

*/