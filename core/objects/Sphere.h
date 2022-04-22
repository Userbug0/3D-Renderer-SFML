#pragma once

#include "GameObject.h"


class Sphere: public GameObject
{
public:
	Sphere(float radius);

	float GetRadius() const { return m_Radius; }

private:
	float m_Radius;
};
