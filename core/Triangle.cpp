#include "Triangle.h"

#include <iostream>

Triangle::Triangle(const std::initializer_list<Vector3>& list)
{
	uint8_t i = 0;
	for (auto& point : list)
	{
		m_points[i] = point;
		i++;
	}
	m_toDraw.setPointCount(3);
	m_toDraw.setOutlineThickness(1);
	m_toDraw.setFillColor(sf::Color::Transparent);
}


void Triangle::Draw(sf::RenderWindow* window)
{
	for (int i = 0; i < 3; ++i)
		m_toDraw.setPoint(i, { m_points[i].x, m_points[i].y });


	window->draw(m_toDraw);
}


Mesh::Mesh(const std::initializer_list<Triangle>& list)
	: m_size(list.size())
{
	for (auto& tri : list)
		m_array.push_back(tri);
}
