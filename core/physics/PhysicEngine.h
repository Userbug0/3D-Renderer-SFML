#pragma once

#include <SFML/System/Time.hpp>

#include "../objects/Cube.h"


class PhysicEngine
{
public:
	PhysicEngine() = default;
	~PhysicEngine() = default;

	void Update(const sf::Time& elapsedTime, Cube* cube);
	void Start();

private:

};