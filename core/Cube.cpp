#include "Cube.h"


Cube::Cube()
{
	m_triangles =
	{
		// FRONT
		{ {0.f, 0.f, 0.f},  {0.f, 1.f, 0.f},   {1.f, 1.f, 0.f } },
		{ {0.f, 0.f, 0.f},  {1.f, 1.f, 0.f},   {1.f, 0.f, 0.f} },

		//RIGHT
		{ {1.f, 0.f, 0.f},  {1.f, 1.f, 0.f},   {1.f, 1.f, 1.f } },
		{ {1.f, 0.f, 0.f},  {1.f, 1.f, 1.f},   {1.f, 0.f, 1.f} },

		// BEHIND
		{ {1.f, 0.f, 1.f},  {1.f, 1.f, 1.f},   {0.f, 1.f, 1.f } },
		{ {1.f, 0.f, 1.f},  {0.f, 1.f, 1.f},   {0.f, 0.f, 1.f} },

		// LEFT
		{ {0.f, 0.f, 1.f},  {0.f, 1.f, 1.f},   {0.f, 1.f, 0.f } },
		{ {0.f, 0.f, 1.f},  {0.f, 1.f, 0.f},   {0.f, 0.f, 0.f} },

		// UP
		{ {0.f, 1.f, 0.f },   {0.f, 1.f, 1.f},  {1.f, 1.f, 1.f} },
		{ {0.f, 1.f, 0.f },   {1.f, 1.f, 1.f},  {1.f, 1.f, 0.f} },

		// DOWN
		{ {1.f, 0.f, 1.f },   {0.f, 0.f, 1.f},  {0.f, 0.f, 0.f} },
		{ {1.f, 0.f, 1.f },   {0.f, 0.f, 0.f},  {1.f, 0.f, 0.f} },
	};
}


void Cube::Translate(const Vector3& offset)
{
	for (auto& tri : m_triangles)
	{
		tri[0] += offset;
		tri[1] += offset;
		tri[2] += offset;
	}
}
