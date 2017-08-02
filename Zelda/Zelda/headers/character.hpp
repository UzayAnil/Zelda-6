#pragma once

#include <vector>
#include <fstream>
#include "entity.hpp"

using std::vector;
using std::ifstream;

using sf::IntRect;
using sf::Vector2f;

class Character : public Entity
{
	enum class HorizontalDirection {LEFT, NEUTRAL, RIGHT};
	enum class VerticalDirection {UP, NEUTRAL, DOWN};

	struct Directions
	{
		HorizontalDirection horizontal;
		VerticalDirection vertical;
	};

public:
	Character(string _name);
	~Character();

	void setDirection(Directions directions);

private:
	bool load(string directory);
	vector<IntRect> frameRect; // contains the rectangles for every entity frame
	
	bool moving;
	float animationClock; // this will be the internal clock that handles animation
	Directions direction;
};