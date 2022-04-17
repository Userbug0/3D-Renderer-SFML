#pragma once

#include "../rendering/Triangle.h"
#include "../Vector3.h"


// Position: front left upper corner
class Cube
{
public:
	Cube();
	~Cube() = default;

	size_t NumOfTrinagles() const { return m_NumOfTriangles; }
	Triangle& getTriangle(size_t index) { return m_triangles[index]; }

	void Translate(const Vector3& offset);
	Vector3 getRotation() { return m_rotation; }
	void AddRotation(const Vector3& vec) { m_rotation += vec; };

private:
	Vector3 m_rotation;

	Mesh m_triangles;
	const size_t m_NumOfTriangles = 12;
};
