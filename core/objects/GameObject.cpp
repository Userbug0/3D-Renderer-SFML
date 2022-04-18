#include "GameObject.h"

#include <fstream>
#include <strstream>
#include "../Settings.h"


GameObject::GameObject(const std::string& path)
{
	ReadFromObjectFile(path);
	SetOrigin({0, 0, 0});
	transform.scaling = { 0.5f * (float)WINDOW_WIDTH, 0.5f * (float)WINDOW_HEIGHT, 1 };
}


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


bool GameObject::ReadFromObjectFile(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open())
		return false;

	std::vector<Vector3> vertices;

	while (!file.eof())
	{
		char line[128];
		file.getline(line, 128);

		std::strstream s;
		s << line;

		char junk;

		if (line[0] == 'v')
		{
			Vector3 vertex;
			s >> junk >> vertex.x >> vertex.y >> vertex.z;
			vertices.push_back(vertex);
		}

		if (line[0] == 'f')
		{
			size_t f[3];
			s >> junk >> f[0] >> f[1] >> f[2];
			m_triangles.AddTriangle({vertices[f[0] - 1], vertices[f[1] - 1], vertices[f[2] - 1]});
			++m_NumOfTriangles;
		}
	}

	return true;
}

