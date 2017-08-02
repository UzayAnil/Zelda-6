#pragma once

#include "entity.hpp"


class Layer : public Entity
{
public:
	Layer(string _name);

private:
	bool load(string directory);


};