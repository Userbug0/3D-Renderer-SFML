#include "Triangle.h"


Triangle::Triangle(const std::initializer_list<Vector3>& list)
{
	uint8_t i = 0;
	for (auto& point : list)
	{
		m_points[i] = point;
		i++;
	}
}


Mesh::Mesh(const std::initializer_list<Triangle>& list)
{
	size_t i = 0;
	for (auto& tri : list)
	{
		m_array[i] = tri;
		++i;
	}
	m_size = i;
}
