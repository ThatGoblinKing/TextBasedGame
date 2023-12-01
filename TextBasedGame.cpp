#include<iostream>
#include <vector>
#include "Room.cpp"
#include <map>
#include "Item.cpp"
#include "Events.cpp"
#include <fstream>
#include<windows.h>
#include<string>
#include<sstream>
//using std::string;
//using std::vector;
//using std::pair;
//using std::cout;

static Room parseRoom(string rawRoom);
static vector<string> getRawMap();

/*

BOAT_FRAME1:
								  |      |      |
								 )_)    )_)    )_)
							   )____) )____) )____)
							 )______)______)______)
						/\________|______|______|__________/\
					   |                                    |
---^^~-^---^~-^------~-^\    O     o      O     o     O    /----~----~~~~~---^^-^-^---~\n
	^~~^                 ^~^~^~^~                   ^^          ~~^~^^~\n
				^~~~^~~~~^^                       ^^^^^\n"




BOAT_FRAME2:
								  |      |      |
								 )_)    )_)    )_)
							   )____) )____) )____)
							 )______)______)______)
						/\________|______|______|________/\
--^--^----^^----^-~~----`     ~~               ^^^~~^      '----~--~~^^--^---^---^~-
	 ^^^^^^             ~^~^^^~                          ^^ ^    ~~~ ~^             ^^
										-----~^~^^~^~                   ^^^^


WELCOME:
 _ _ _     _                   __
| | | |___| |___ ___ _____ ___|  |
| | | | -_| |  _| . |     | -_|__|
|_____|___|_|___|___|_|_|_|___|__|


*/




int main()
{
	const string BOAT_FRAME1 = "				  |      |      |\n				 )_)    )_)    )_)\n			       )____) )____) )____)\n			     )______)______)______)\n			/\\________|______|______|________/\\\n		       |                                   |\n---^^~-^---^~-^------~-^\\ ~~ O    ^o      O     o     O ^^ /----~----~~~~~---^^-^-^---~\n		^~~^                 ^~^~^~^~                   ^^          ~~^~^^~\n					^~~~^~~~~^^                       ^^^^^\n\n";
	const string BOAT_FRAME2 = "\n				  |      |      |\n				 )_)    )_)    )_)\n			       )____) )____) )____)\n			     )______)______)______)\n			/\\________|______|______|________/\\\n--^--^----^^----^-~~----`     ~~               ^^^~~^      '----~--~~^^--^---^---^~-\n     ^^^^^^ 		~^~^^^~                          ^^ ^    ~~~ ~^             ^^\n	  				-----~^~^^~^~                   ^^^^\n\n";
	const string WELCOME = " _   _     _\t\t       __\n| | | |___| |___ ___ _____ ___|  |\n| | | | -_| |  _| . |     | -_|__|\n|_____|___|_|___|___|_|_|_|___|__|\n";
	//Shop testShop("Hello, this is a shop, buy something.", vector<Item>{Item(20, 1, 1, "Healing Potion", "Lets you heal, what did you expect?"), Item(200, 1, 1, "Boomerang", "Always comes back, unlike those 5 gold coins you lent to Brent all those years ago.")});
	Shop testShop("Hello, this is a shop, buy something.");
	vector<string> rawMap = getRawMap();
	const int MAP_SIZE = rawMap.size();
	pair<int, int> playerPos(0, 0);
	pair<pair<int, int>, Room> insertion;
	Room outOfBounds = Room();
	std::map<pair<int, int>, Room> rooms;
	for (int i = 0; i < MAP_SIZE; i++) {
		Room currentParsedRoom = parseRoom(rawMap.at(i));
		insertion.first = currentParsedRoom.getCoords();
		insertion.second = currentParsedRoom;
		rooms.insert(insertion);
	}
	pair<pair<int, int>, Room> testEventRoom;
	testEventRoom.first = { 0, -2 };
	//EventRoom *erm = new EventRoom("You're at the base of a staircase up to the deck", 0, -2, false, true, false, true, &testShop);
	Room roomIn;
	pair<int, int> adjacentCoords;
	string adjacentRoomDescriptions[4];

	for (int i = 0; i < 12; i++) {
		cout << WELCOME;
		switch (i % 2)
		{
		case 0:
			cout << BOAT_FRAME1 << std::flush;
			break;

		default:
			cout << BOAT_FRAME2 << std::flush;
			break;
		}
		Sleep(800);
	}

	//-----------------------------------------------------------------------------------------------------------------------------------+
	//Game Loop

	while (true)
	{
		roomIn = rooms[playerPos];
		roomIn.describe();
		cout << "You are at: (" << playerPos.first << ", " << playerPos.second << ")" << std::endl;
		for (int i = 0; i < 4; i++) {
			adjacentCoords = playerPos;
			switch (i) {
			case 0:
				adjacentCoords.second = playerPos.second + 1;
				break;
			case 1:
				adjacentCoords.first = playerPos.first + 1;
				break;
			case 2:
				adjacentCoords.second = playerPos.second - 1;
				break;
			case 3:
				adjacentCoords.first = playerPos.first - 1;
				break;
			}
			try {
				adjacentRoomDescriptions[i] = rooms[adjacentCoords].getShortDescription();
			}
			catch (std::exception)
			{
				adjacentRoomDescriptions[i] = "null";
			}
		}
		switch (roomIn.move(adjacentRoomDescriptions))
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


static Room parseRoom(string rawRoom) {
	string segment[7];
	string delimeter = "|";
	for (int i = 0; i < 4; i++) {
		segment[i] = rawRoom.substr(0, rawRoom.find(delimeter));
		rawRoom.erase(0, rawRoom.find(delimeter) + delimeter.length());
	}
	Room parsedRoom;
	try {
		parsedRoom = Room(segment[0], segment[1], (stoi(segment[2])), stoi(segment[3]));
	}
	catch (std::invalid_argument const&) {
	}
	return parsedRoom;
}

static vector<string> getRawMap() {
	std::fstream newFile;
	vector<string> rawMap;

	newFile.open("Map.txt", std::ios::in);
	if (newFile.is_open()) {
		std::string tp;
		while (getline(newFile, tp)) {
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