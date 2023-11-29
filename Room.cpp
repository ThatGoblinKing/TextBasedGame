#include <iostream>

class Room
{
	protected:
		std::string shortDescription;
		std::string description;
		int coordinates[2];
		bool exits[4];

	public:
	Room()
	{
		this->shortDescription = "null";
		this->description = "As you enter this area, the world around you seems to melt into a pale white void. Your body feels weightless.";
		this->coordinates[0] = 2000;
		this->coordinates[1] = 2000;
	}
	Room(std::string shortDescription, std::string description, int x, int y)
	{
		this->shortDescription = shortDescription;
		this->description = description;
		this->coordinates[0] = x;
		this->coordinates[1] = y;
	}
	void describe() { std::cout << this->description << std::endl;}
	std::string getShortDescription() {return this->shortDescription;}
	int move(std::string adjacentRoomDescriptions[4])
	{
		bool exits[4];

		for(int i = 0; i < 4; i++){
			exits[i] = (adjacentRoomDescriptions[i] != "null");
		}

		std::string moveOptions = "To your";
		if (exits[0])
		{
			moveOptions += ("\nNorth: " + adjacentRoomDescriptions[0]);
		}
		if (exits[1])
		{
			moveOptions += ("\nEast: " + adjacentRoomDescriptions[1]);
		}
		if (exits[2])
		{
			moveOptions += ("\nSouth: " + adjacentRoomDescriptions[2]);
		}
		if (exits[3])
		{
			moveOptions += ("\nWest: " + adjacentRoomDescriptions[3]);
		}
		std::cout << moveOptions << std::endl;
		std::string input;
		std::cin >> input;
		char moveDir = toupper(input.at(0));
		std::cout << std::endl;
		switch (moveDir)
		{
		case 'N':
			if (exits[0])
				return 0;
			else
				return move(adjacentRoomDescriptions);
			break;
		case 'E':
			if (exits[1])
				return 1;
			else
				return move(adjacentRoomDescriptions);
			break;
		case 'S':
			if (exits[2])
				return 2;
			else
				return move(adjacentRoomDescriptions);
			break;
		case 'W':
			if (exits[3])
				return 3;
			else
				return move(adjacentRoomDescriptions);
			break;
		default:
			return move(adjacentRoomDescriptions);
		}
	}
	bool inRoom(int playerX, int playerY)
	{
		return (playerX == this->coordinates[0] && playerY == this->coordinates[1]);
	}

	std::pair<int, int> getCoords()
	{
		return std::pair<int, int>(coordinates[0], coordinates[1]);
	}
};

class EventRoom : public Room
{
	#include"Events.cpp"
	Event* event;
	public:
	EventRoom(std::string description, int x, int y, bool northExit, bool eastExit, bool southExit, bool westExit, Event* roomEvent)
	{
		this->description = description;
		this->coordinates[0] = x;
		this->coordinates[1] = y;
		this->exits[0] = northExit;
		this->exits[1] = eastExit;
		this->exits[2] = southExit;
		this->exits[3] = westExit;
		this->event = roomEvent;
	}
	int move()
	{
		this->event->doEvent();
		return move();
	}
};