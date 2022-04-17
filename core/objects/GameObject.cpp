#include "GameObject.h"


void GameObject::AddTriangle(const Triangle& tri)
{
	m_triangles.AddTriangle(tri); 
	++m_NumOfTriangles; 
}


void GameObject::SetColor(const sf::Color& color)
{
	for (auto& tri : m_triangles)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			tri.SetVertexColor(i, color);
		}
	}
}

