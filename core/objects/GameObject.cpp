#include "GameObject.h"

#include <fstream>
#include <strstream>
#include "../Settings.h"


GameObject::GameObject()
	: m_isUpdatedTransform(true), m_NumOfTriangles(0)
{
	m_transform.scaling = { 1, 1, 1 };
}


GameObject::GameObject(const std::string& path)
	: m_isUpdatedTransform(true), m_NumOfTriangles(0)
{
	ReadFromObjectFile(path);
	m_transform.scaling = { 1, 1, 1 };
}


void GameObject::ApplyTransform()
{
	if (m_isUpdatedTransform == true)
	{

		Matrix4 toWorld = m_transform.GetTransformMatrix();

		m_triangles = m_originTriangles;

		for (auto& tri: m_triangles)
		{
			for (uint8_t j = 0; j < 3; ++j)
				Matrix4::ApplyMultiplication(tri[j], toWorld);
		}
		m_isUpdatedTransform = false;
	}
}


void GameObject::AddTriangle(const Triangle& tri)
{
	m_triangles.AddTriangle(tri); 
	m_originTriangles.AddTriangle(tri);
	++m_NumOfTriangles; 
}


void GameObject::SetTriangle(size_t i, const Triangle& other)
{
	m_triangles[i] = other;
	m_originTriangles[i] = other;
}


void GameObject::SetColor(const sf::Color& color)
{
	for (size_t i = 0; i < m_NumOfTriangles; ++i)
	{
		SetTriangleColor(i, color);
	}
}


void GameObject::SetTriangleColor(size_t i, const sf::Color& color)
{
	for (size_t j = 0; j < 3; ++j)
	{
		m_triangles[i].SetVertexColor(j, color);
		m_originTriangles[i].SetVertexColor(j, color);
	}
}


bool GameObject::ReadFromObjectFile(const std::string& path)
{
	m_triangles.clear();
	m_NumOfTriangles = 0;

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
			m_originTriangles.AddTriangle({ vertices[f[0] - 1], vertices[f[1] - 1], vertices[f[2] - 1] });
			++m_NumOfTriangles;
		}
	}

	return true;
}

