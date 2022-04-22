#pragma once

#include "GameObject.h"


// Position: front left upper corner
class Cube: public GameObject
{
public:
	Cube();
	Cube(float width, float height, float length);
	~Cube() = default;

private:
	float m_width;
	float m_height;
	float m_length;
};
