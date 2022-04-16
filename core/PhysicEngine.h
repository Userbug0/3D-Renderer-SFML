#pragma once

#include <SFML/System/Time.hpp>

#include "Cube.h"


class PhysicEngine
{
public:
	PhysicEngine() = default;
	~PhysicEngine() = default;

	void Update(const sf::Time& elapsedTime, Cube* cube);

private:
	void RotatePoint(Vector3& point, const Vector3& rotation);
};