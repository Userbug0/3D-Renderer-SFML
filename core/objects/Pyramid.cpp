#include "Pyramid.h"
#include "../Settings.h"


Pyramid::Pyramid(float height, float radius, size_t numOfVertices)
	: m_height(height), m_baseRadius(radius), m_baseNumOfVertices(numOfVertices)
{
    if (m_baseNumOfVertices < 3)
        throw std::invalid_argument("Regular Polygon must have at least 3 vertices");

    Vector3 top = { 0, 0, m_height };
    float prevPointx = m_baseRadius, prevPointy = 0, pointx, pointy;

    for (float angle = 360 / m_baseNumOfVertices; angle <= 360; angle += 360 / m_baseNumOfVertices)
    {
        pointx = m_baseRadius * cosf(angle * (float)M_PI / 180);
        pointy = m_baseRadius * sinf(angle * (float)M_PI / 180);

        AddTriangle({ {prevPointx, prevPointy, 0}, {pointx, pointy, 0}, top });

        AddTriangle({ {0, 0, 0}, {pointx, pointy, 0}, { prevPointx, prevPointy, 0 } });

        prevPointx = pointx;
        prevPointy = pointy;
    }

}


Pyramid::Pyramid(float height, RegularPolygon base)
	: m_height(height), m_baseRadius(base.GetRadius()), m_baseNumOfVertices(base.GetNumOfVertices())
{

}


void Pyramid::SetBaseColor(const sf::Color& color)
{
    for (size_t i = 1; i < m_baseNumOfVertices * 2; i+= 2)
    {
        SetTriangleColor(i, color);
    }
}

