#include "RegularPolygon.h"
#include "../Settings.h"


RegularPolygon::RegularPolygon(float radius, size_t numOfVertices)
	: m_Radius(radius), m_NumOfVertices(numOfVertices)
{
	if (m_NumOfVertices < 3)
		throw std::invalid_argument("Regular Polygon must have at least 3 vertices");


    float prevPointx = m_Radius, prevPointy = 0, pointx, pointy;

    for (float angle = 360 / (float)m_NumOfVertices; angle <= 360; angle += 360 / m_NumOfVertices)
    {
        pointx = m_Radius * cosf(angle * (float)M_PI / 180);
        pointy = m_Radius * sinf(angle * (float)M_PI / 180);

        AddTriangle({ {0, 0, 0}, {pointx, pointy, 0}, {prevPointx, prevPointy, 0} });

        prevPointx = pointx;
        prevPointy = pointy;
    }
}
