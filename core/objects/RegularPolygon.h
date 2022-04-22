#pragma once

#include "GameObject.h"


class RegularPolygon: public GameObject
{
public:
	RegularPolygon(float radius, size_t numOfVertices);

	size_t GetNumOfVertices() const { return m_NumOfVertices; }
	float GetRadius() const { return m_Radius; }

private:
	float m_Radius;
	size_t m_NumOfVertices;
};

