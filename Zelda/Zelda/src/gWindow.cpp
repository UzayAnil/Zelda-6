#include "../headers/gWindow.hpp"
#include "../headers/entity.hpp"

gWindow::gWindow(int _resX, int _resY) : RenderWindow(sf::VideoMode::getDesktopMode(), "ANOMIE", sf::Style::None)
{
	style = FULLSCREEN;
	keyReleased = true;
	resX = _resX;
	resY = _resY;

	//set the view
	letterbox.setSize(resX, resY);
	letterbox.setCenter(resX / 2, resY / 2);
	resized(resX, resY);
	setFramerateLimit(60);
}

void gWindow::resized(int windowWidth, int windowHeight)
{
	//modified from https://github.com/SFML/SFML/wiki/Source:-Letterbox-effect-using-a-view

	// Compares the aspect ratio of the window to the aspect ratio of the view,
	// and sets the view's viewport accordingly in order to archieve a letterbox effect.

	float windowRatio = windowWidth / (float)windowHeight;
	float viewRatio = letterbox.getSize().x / letterbox.getSize().y;
	float sizeX = 1;
	float sizeY = 1;
	float posX = 0;
	float posY = 0;

	bool horizontalSpacing = true;

	//If the view is wider than the window
	if (windowRatio < viewRatio)
		horizontalSpacing = false;

	if (horizontalSpacing)
	{
		sizeX = viewRatio / windowRatio;
		posX = (1 - sizeX) / 2.f;
	}

	else
	{
		sizeY = windowRatio / viewRatio;
		posY = (1 - sizeY) / 2.f;
	}

	letterbox.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
}

void gWindow::switchStyle()
{
	if (keyReleased)
	{
		std::cout << "keyreleased now false" << std::endl;
		keyReleased = false;

		if (style == FULLSCREEN)
		{
			//create windowed mode at default specified resolution
			this->create(sf::VideoMode(resX, resY, 32), "ANOMIE", sf::Style::Default);
			style = WINDOWED;
			resized(resX, resY);
		}

		else
		{
			//create fullscreen windowed mode using getDesktopMode()
			this->create(sf::VideoMode::getDesktopMode(), "ANOMIE", sf::Style::None);
			style = FULLSCREEN;
			resized(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
		}
	}
}

void gWindow::setKeyReleased(bool value)
{
	keyReleased = value;
}

void gWindow::updateView()
{
	setView(letterbox);
}

gWindow::~gWindow()
{

}

bool gWindow::isKeyReleased() const
{
	return keyReleased;
}

/*********************************************************************************
void gWindow::update(vector<Entity> const &entities)

INPUT PARAMETERS: a const reference to a vector of entities. NOTE: The function
will iterate through and draw the entities in order, so make sure that the
entities are inserted in the correct order in regards to foreground/background
precedence.

This function uses polymorphism. Make sure that all entities are declared as a
pointer to an entity on the heap. Don't call entities on the stack memory.

This function also checks for closing the window, and for whether or not the
window is maximized/minimized. Put this function in the main game loop.
*********************************************************************************/
void gWindow::update(vector<Entity *> entities)
{
	static Event event;

	//for checking if player wants to minimize/maximize the window
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::Tab) && keyReleased == true)
	{
		switchStyle();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) close();


	while (pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::Tab) setKeyReleased(true);
			break;
		case sf::Event::Closed:
			close();
			break;
		}
	}

	clear();
	updateView();

	for (int i = 0; i < (int)(entities.size()); i++)
	{
		entities[i]->draw(this);
	}

	display();
}