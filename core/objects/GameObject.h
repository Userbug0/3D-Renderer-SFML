#pragma once


#include "../rendering/Triangle.h"
#include "../Transform.h"


class GameObject
{
public:
	GameObject() = default;
	GameObject(const std::string& path);
		
	inline size_t GetNumOfTriangles()	   const { return m_NumOfTriangles; }
	inline Triangle& GetTriangle(size_t i)       { return m_triangles[i];   }
	inline Triangle GetTriangle(size_t i)  const { return m_triangles[i]; }

	inline Vector3 GetOrigin() 			   const { return m_origin; }
	inline void SetOrigin(const Vector3& point)  { m_origin = point; }

	void AddTriangle(const Triangle& tri);
	void SetColor(const sf::Color& color);

	bool ReadFromObjectFile(const std::string& path);
	
	Transform transform;

private:
	Mesh m_triangles;
	size_t m_NumOfTriangles;
	Vector3 m_origin;
};

