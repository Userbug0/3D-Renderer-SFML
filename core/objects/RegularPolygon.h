#pragma once

#include "GameObject.h"


class RegularPolygon: public GameObject
{
public:
	RegularPolygon(float radius, size_t numOfVertices);

private:
	float m_Radius;
	size_t m_NumOfVertices;
};

