#include "Triangle.h"

#include <iostream>

Triangle::Triangle(const std::initializer_list<Vector3>& list)
	: m_toDraw(sf::LinesStrip, 4)
{
	uint8_t i = 0;
	for (auto& point : list)
	{
		m_points[i] = point;
		i++;
	}
}


void Triangle::Draw(sf::RenderWindow* window)
{
	m_toDraw[0] = m_toDraw[3] = sf::Vertex({ m_points[0].x, m_points[0].y });
	m_toDraw[1] = sf::Vertex({ m_points[1].x, m_points[1].y });
	m_toDraw[2] = sf::Vertex({ m_points[2].x, m_points[2].y });

	window->draw(m_toDraw);
}


Mesh::Mesh(const std::initializer_list<Triangle>& list)
	: m_size(list.size())
{
	for (auto& tri : list)
		m_array.push_back(tri);
}
