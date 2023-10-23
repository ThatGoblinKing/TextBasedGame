#include <iostream>

class Room
{
	std::string description;
	int coordinates[2];
	bool exits[4];

public:
	Room()
	{
		this->description = "As you enter this area, the world around you seems to melt into a pale white void. Your body feels weightless.";
		this->coordinates[0] = 2000;
		this-> coordinates[1] = 2000;
	}
	Room(std::string description, int x, int y, bool northExit, bool eastExit, bool southExit, bool westExit)
	{
		this->description = description;
		this->coordinates[0] = x;
		this->coordinates[1] = y;
		this->exits[0] = northExit;
		this->exits[1] = eastExit;
		this->exits[2] = southExit;
		this->exits[3] = westExit;
	}
	void describe() { std::cout << this-> description << std::endl; }
	int move()
	{
		std::string moveOptions = "You can go:";
		if (this->exits[0])
		{
			moveOptions += " N";
		}
		if (this->exits[1])
		{
			moveOptions += " E";
		}
		if (this->exits[2])
		{
			moveOptions += " S";
		}
		if (this->exits[3])
		{
			moveOptions += " W";
		}
		std::cout << moveOptions << std::endl;
		std::string input;
		std::cin >> input;
		char moveDir = toupper(input.at(0));
		switch (moveDir)
		{
		case 'N':
			if (this->exits[0])
				return 0;
			else
				return move();
			break;
		case 'E':
			if (this->exits[1])
				return 1;
			else
				return move();
			break;
		case 'S':
			if (this->exits[2])
				return 2;
			else
				return move();
			break;
		case 'W':
			if (this->exits[3])
				return 3;
			else
				return move();
			break;
		default:
			return move();
		}
	}
	bool inRoom(int playerX, int playerY)
	{
		return (playerX == this->coordinates[0] && playerY == this->coordinates[1]);
	}
};