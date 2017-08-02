#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

using sf::Texture;
using sf::Sprite;
using sf::RenderWindow;
using sf::Vector2f;

using std::string;

class Entity 
{
public:
	Entity(string _name);
	~Entity();

	Sprite getSprite() const;
	void setVelocity(Vector2f newVelocity);
	void move(Vector2f distance);
	void setPosition(Vector2f position);
	void setSize(Vector2f scale);
	void draw(RenderWindow *window) const;
	float getX();
	float getY();

protected:
	virtual bool load(string directory) = 0;

	Texture entityTexture;
	Sprite entityDrawable;
	string name;
	Vector2f velocity;
};