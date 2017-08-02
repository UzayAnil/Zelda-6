#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include "entity.hpp"

using std::vector;
using std::ifstream;
using std::cout;
using std::endl;

using sf::IntRect;
using sf::Vector2f;

class Character : public Entity
{

public:

	enum class HorizontalDirection { LEFT, NEUTRAL, RIGHT };
	enum class VerticalDirection { UP, NEUTRAL, DOWN };

	struct Directions
	{
		HorizontalDirection horizontal;
		VerticalDirection vertical;
	};

	Character(string _name);
	~Character();

	void setDirection(Directions directions);
	void setFrame(int frame);
	int getFrameNumber() const;

protected:

	bool load(string directory);
	vector<IntRect> frameRect; // contains the rectangles for every entity frame
	int frameNumber;

	
	bool moving;
	bool movingHoriz;
	bool movingVert;
	Clock animationClock;
	Directions direction;
};