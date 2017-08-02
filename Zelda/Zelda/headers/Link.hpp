#pragma once

#include "character.hpp"
#include <SFML/System.hpp>

using sf::Keyboard;

class Link : public Character
{
public:
	Link();
	~Link();

	void update(float deltaTime);

private:

};