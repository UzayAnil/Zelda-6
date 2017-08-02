#include "../headers/layer.hpp"

Layer::Layer(string _name) : Entity(_name)
{
	load("./data/layers/");
}

bool Layer::load(string directory)
{
	if(!entityTexture.loadFromFile(directory + name + ".png")) return false;
	entityDrawable.setTexture(entityTexture);

	return true;
}