#include "../headers/character.hpp"

Character::Character(string _name) : Entity(_name)
{
	load("./data/characters/");
	moving = false;
	direction = { HorizontalDirection::NEUTRAL, VerticalDirection::NEUTRAL };
	animationTime = 0.0f;
}

Character::~Character()
{

}

//overloaded from the pure virtual in Entity
bool Character::load(string directory)
{
	//first, load the texture sheet for the character
	entityTexture.loadFromFile(directory + name + ".png");
	
	//then, load the map
	string mapPath = "./data/maps" + name + ".dat";
	string buffer;
	ifstream load(mapPath);
	IntRect tempRect;
	char comma; //for filtering out the commas in the dat file

	if (!load.good()) return false;

	while (!load.eof())
	{
		//clear the beginning out of the way
		getline(load, buffer, ',');

		for (int i = 0; i < 4; i++)
		{
			switch (i)
			{
			case 1: load >> tempRect.left >> comma;
				break;
			case 2: load >> tempRect.top >> comma;
				break;
			case 3: load >> tempRect.width >> comma;
				break;
			case 4: load >> tempRect.height >> comma; // the last instance of comma actually clears the newline
				break;
			}
		}

		frameRect.push_back(tempRect);
	}

	return true;
}

void Character::setDirection(Directions directions)
{
	direction.horizontal = directions.horizontal;
	direction.vertical = directions.vertical;
}
