#include "Triangle.h"



Triangle::Triangle(const std::initializer_list<Vector3>& list)
	: m_toDraw(sf::Triangles, 3)
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
	m_toDraw[0] = sf::Vertex({ m_points[0].x, m_points[0].y }, sf::Color::White);
	m_toDraw[1] = sf::Vertex({ m_points[1].x, m_points[1].y }, sf::Color::White);
	m_toDraw[2] = sf::Vertex({ m_points[2].x, m_points[2].y }, sf::Color::White);

	window->draw(m_toDraw);
}


Vector3 Triangle::GetNormal()
{
	Vector3 res = Vector3::CrossProduct(m_points[1] - m_points[0], m_points[2] - m_points[0]);
	return res.normalize();
}


Mesh::Mesh(const std::initializer_list<Triangle>& list)
	: m_size(list.size())
{
	for (auto& tri : list)
		m_array.push_back(tri);
}
