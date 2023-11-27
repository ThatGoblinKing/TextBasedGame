#include <vector>
#include "Room.cpp"
#include <map>
#include "Item.cpp"
#include "Events.cpp"
#include <fstream>
using std::string;
using std::vector;
using std::pair;
using std::cout;

static Room parseRoom(string rawRoom);
static vector<string> getRawMap();

int main()
{
	string imGonnaScream = "Hello, this is a shop, buy something.";
	Shop testShop(imGonnaScream, vector<Item>{Item(20, 1, 1, "Healing Potion", "Lets you heal, what did you expect?"), Item(200, 1, 1, "Boomerang", "Always comes back, unlike those 5 gold coins you lent to Brent all those years ago.")});
	vector<string> rawMap = getRawMap();
	const int MAP_SIZE = rawMap.size();
	pair<int, int> playerPos (0, 0);
	pair<pair<int, int>, Room> insertion;
	Room outOfBounds = Room();
	std::map<pair<int,int>, Room> rooms;
	for(int i = 0; i < MAP_SIZE; i++) {
		Room currentParsedRoom = parseRoom(rawMap.at(i));
		insertion.first = currentParsedRoom.getCoords();
		insertion.second = currentParsedRoom;
		rooms.insert(insertion);
	}
	pair<pair<int, int>, Room> testEventRoom;
	testEventRoom.first = {0, -2};
	EventRoom::EventRoom("You're at the base of a staircase up to the deck", 0, -2, false, true, false, true, testShop);
	Room roomIn;
	while (true)
	{
		roomIn = rooms[playerPos];
		rooms[playerPos].describe();
		cout << "You are at: (" << playerPos.first << ", " << playerPos.second << ")" << std::endl;
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
static Room parseRoom(string rawRoom){
    string segment[7];
    string delimeter = "|";
    for (int i = 0; i < 7; i++){
        segment[i] = rawRoom.substr(0, rawRoom.find(delimeter));
	    rawRoom.erase(0, rawRoom.find(delimeter) + delimeter.length());
    }
	Room parsedRoom;
	try{
	parsedRoom = Room(segment[0], stoi(segment[1]), stoi(segment[2]), segment[3] != "false", segment[4] != "false", segment[5] != "false", segment[6] != "false");
	} catch(std::invalid_argument const&) {
	}
	return parsedRoom;
}

static vector<string> getRawMap(){
    std::fstream newFile;
    vector<string> rawMap;

    newFile.open("Map.txt", std::ios::in);
    if (newFile.is_open()){
        std::string tp;
        while(getline(newFile, tp)){
            rawMap.push_back(tp);
        }
    }

    return rawMap;
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
*/