#pragma once


#include "../rendering/Triangle.h"
#include "../Transform.h"


class GameObject
{
public:
	inline size_t GetNumOfTriangles()	   const { return m_NumOfTriangles; }
	inline Triangle& GetTriangle(size_t i)       { return m_triangles[i];   }
	inline Triangle GetTriangle(size_t i)  const { return m_triangles[i]; }

	inline void AddTriangle(const Triangle& tri) { m_triangles.AddTriangle(tri); ++m_NumOfTriangles; }

	inline Vector3 GetOrigin() 			   const { return m_origin; }
	inline void SetOrigin(const Vector3& point)  { m_origin = point; }

	Transform transform;

private:
	Mesh m_triangles;
	size_t m_NumOfTriangles;
	Vector3 m_origin;
};

