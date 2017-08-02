#include "../headers/character.hpp"

Character::Character(string _name) : Entity(_name)
{
	if (!load("./data/characters/")) cout << "couldn't load map" << endl;;
	moving = false;
	movingHoriz = false;
	movingVert = false;
	direction = { HorizontalDirection::NEUTRAL, VerticalDirection::NEUTRAL };
	animationClock.restart();
}

Character::~Character()
{

}

//overloaded from the pure virtual in Entity
bool Character::load(string directory)
{
	//first, load the texture sheet for the character
	if(!entityTexture.loadFromFile(directory + name + ".png")) return false;
	
	//then, load the map
	string mapPath = "./data/maps/" + name + ".dat";
	string buffer;
	ifstream load(mapPath);
	IntRect tempRect;
	char comma; //for filtering out the commas in the dat file

	if (!load.good()) return false;

	while (!load.eof())
	{
		//clear the beginning out of the way
		getline(load, buffer, ',');

		for (int i = 1; i < 5; i++)
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

	setFrame(0);
	load.close();

	return true;
}

void Character::setDirection(Directions directions)
{
	direction.horizontal = directions.horizontal;
	direction.vertical = directions.vertical;
}

void Character::setFrame(int frame)
{
	entityDrawable.setTextureRect(frameRect[frame]);
	frameNumber = frame;
}

int Character::getFrameNumber() const
{
	return frameNumber;
}
