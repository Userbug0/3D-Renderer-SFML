#include "Triangle.h"


Triangle::Triangle()
	: m_toDraw(sf::Triangles, 3), m_toDrawOutline(sf::LineStrip, 4)
{
	for (uint8_t i = 0; i < 3; ++i)
	{
		m_toDraw[i] = sf::Vertex({ 0, 0 }, sf::Color::White);
		m_toDrawOutline[i].color = sf::Color::Black;
	}

	m_toDrawOutline[3].color = sf::Color::Black;
}


Triangle::Triangle(const std::initializer_list<Vector3>& list)
	: m_toDraw(sf::Triangles, 3), m_toDrawOutline(sf::LineStrip, 4)
{
	uint8_t i = 0;
	for (auto& point : list)
	{
		m_points[i] = point;
		m_toDraw[i] = sf::Vertex({ m_points[i].x, m_points[i].y }, sf::Color::White);

		m_toDrawOutline[i].color = sf::Color::Black;
		i++;
	}

	m_toDrawOutline[3].color = sf::Color::Black;
}


void Triangle::Draw(sf::RenderWindow* window)
{
	m_toDraw[0].position = { m_points[0].x, m_points[0].y };
	m_toDraw[1].position = { m_points[1].x, m_points[1].y };
	m_toDraw[2].position = { m_points[2].x, m_points[2].y };

	window->draw(m_toDraw);

	if (m_DrawOutline)
	{
		m_toDrawOutline[0].position = { m_points[0].x, m_points[0].y };
		m_toDrawOutline[1].position = { m_points[1].x, m_points[1].y };
		m_toDrawOutline[2].position = { m_points[2].x, m_points[2].y };
		m_toDrawOutline[0].position = { m_points[0].x, m_points[0].y };

		window->draw(m_toDrawOutline);
	}

}


Vector3 Triangle::GetNormal() const
{
	Vector3 res = Vector3::CrossProduct(m_points[1] - m_points[0], m_points[2] - m_points[0]);
	return res.Normalize();
}


void Triangle::SetVertexColor(size_t i, const sf::Color& color)
{
	m_toDraw[i].color = color;

}


sf::Color Triangle::GetVertexColor(size_t i) const
{
	return m_toDraw[i].color;
}


Mesh::Mesh(const std::initializer_list<Triangle>& list)
	: m_size(list.size())
{
	for (auto& tri : list)
		m_array.push_back(tri);
}
