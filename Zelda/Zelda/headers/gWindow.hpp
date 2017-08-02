#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>

using sf::RenderWindow;
using sf::View;
using sf::Event;

using std::vector;
using std::cout;
using std::endl;

enum
{
	FULLSCREEN, WINDOWED
};

/* This is basically a RenderWindow with a few added features specific for the program.
ADDED FEATURES
- automatically resizes upon shift + tab between fullscreen and windowed
- letterboxes the game to appropriate view depending on preferred aspect ratios
*/
class Entity;

class gWindow : public RenderWindow
{
public:
	gWindow(int _resX = 640, int _resY = 480);
	~gWindow();

	void update(const vector<Entity *> entities);

	void setKeyReleased(bool value);
	bool isKeyReleased() const;

	void switchStyle();

	void resized(int windowWidth, int windowHeight);

	void updateView();

private:
	int style; //FULLSCREEN or WINDOWED
	bool keyReleased; // to check for shift + tab style change key release
	int resX; // default windowed width
	int resY; // defualt windowed height

			  //all displayed objects will be placed inside the view.
			  //Text and other HUD information will be placed in vertical letterbox space
	View letterbox;
	int vResX; // default windowed resolution for View
	int vResY; // default windowed resolution for View
};
