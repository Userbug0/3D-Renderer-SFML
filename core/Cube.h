#pragma once

#include "Triangle.h"
#include "Vector3.h"


// Position: left upper corner
class Cube
{
public:
	Cube(const Vector3& position);
	~Cube() = default;

	void Draw();

private:
	Mesh m_triangles;

	Vector3 m_position;
};
