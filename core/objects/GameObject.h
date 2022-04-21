#pragma once


#include "../rendering/Triangle.h"
#include "../Transform.h"


class GameObject
{
public:
	GameObject();
	GameObject(const std::string& path);
	
	void ApplyTransform();
	inline Transform& GetTransform() { m_isUpdatedTransform = true; return m_transform; };

	inline size_t GetNumOfTriangles()	   const { return m_NumOfTriangles; }
	inline Triangle& GetTriangle(size_t i)       { return m_triangles[i];   }
	inline Triangle GetTriangle(size_t i)  const { return m_triangles[i]; }

	void AddTriangle(const Triangle& tri);
	void SetColor(const sf::Color& color);

	bool ReadFromObjectFile(const std::string& path);
	
private:
	bool m_isUpdatedTransform;
	Transform m_transform;

	Mesh m_triangles;
	Mesh m_originTriangles;
	size_t m_NumOfTriangles;
};

