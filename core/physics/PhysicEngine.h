#pragma once

#include <SFML/System/Time.hpp>

#include "../objects/GameObject.h"


class PhysicEngine
{
public:
	PhysicEngine() = default;
	~PhysicEngine() = default;

	void Update(const sf::Time& elapsedTime, std::vector<GameObject*> objects);
	void Start();

private:

};