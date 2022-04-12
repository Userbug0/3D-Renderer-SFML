#include "Cube.h"


Cube::Cube(const Vector3& position)
	: m_position(position)
{
	m_triangles =
	{
		// FRONT
		{ {0.f, -1.f, 0.f},  {0.f, 0.f, 0.f},   {1.f, 0.f, 0.f } },
		{ {0.f, -1.f, 0.f},  {1.f, 0.f, 0.f},   {1.f, -1.f, 0.f} },

		//RIGHT
		{ {1.f, -1.f, 0.f},  {1.f, 0.f, 0.f},   {1.f, 0.f, 1.f } },
		{ {1.f, -1.f, 0.f},  {1.f, 0.f, 1.f},   {1.f, -1.f, 1.f} },

		// BEHIND
		{ {0.f, -1.f, 1.f},  {0.f, 0.f, 1.f},   {1.f, 0.f, 1.f } },
		{ {0.f, -1.f, 1.f},  {1.f, 0.f, 1.f},   {1.f, -1.f, 1.f} },

		// LEFT
		{ {0.f, -1.f, 0.f},  {0.f, 0.f, 0.f},   {0.f, 0.f, 1.f } },
		{ {0.f, -1.f, 0.f},  {0.f, 0.f, 1.f},   {0.f, -1.f, 1.f} },

		// UP
		{ {0.f, 0.f, 0.f },   {0.f, 0.f, 1.f},  {1.f, 0.f, 1.f} },
		{ {0.f, 0.f, 0.f },   {1.f, 0.f, 1.f},  {1.f, 0.f, 0.f} },

		// DOWN
		{ {0.f, -1.f, 0.f},  {0.f, -1.f, 1.f},  {1.f, -1.f, 1.f} },
		{ {0.f, -1.f, 0.f},  {1.f, -1.f, 1.f},  {1.f, -1.f, 0.f} },
	};
}
