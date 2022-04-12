#pragma once

#include "Triangle.h"
#include "Vector3.h"


// Position: left upper corner
class Cube
{
public:
	Cube();
	~Cube() = default;

	size_t NumOfTrinagles() const { return m_NumOfTriangles; }
	Triangle& getTriangle(size_t index) { return m_triangles[index]; }

	void Translate(const Vector3& offset);

private:
	Mesh m_triangles;
	const size_t m_NumOfTriangles = 12;
};
