#pragma once

#include "RegularPolygon.h"


class Pyramid: public GameObject 
{
public:
	Pyramid(float height, float radius, size_t numOfVertices);
	Pyramid(float height, RegularPolygon base);

	void SetBaseColor(const sf::Color& color);

private:
	float m_height;
	float m_baseRadius;
	size_t m_baseNumOfVertices;
};
