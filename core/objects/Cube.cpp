#include "Cube.h"

#include "../Settings.h"


Cube::Cube()
{
	// FRONT
	AddTriangle({ {0.f, 0.f, 0.f},  {0.f, 1.f, 0.f},   {1.f, 1.f, 0.f } });
	AddTriangle({ {0.f, 0.f, 0.f},  {1.f, 1.f, 0.f},   {1.f, 0.f, 0.f} });

	//RIGHT
	AddTriangle({ {1.f, 0.f, 0.f},  {1.f, 1.f, 0.f},   {1.f, 1.f, 1.f } });
	AddTriangle({ {1.f, 0.f, 0.f},  {1.f, 1.f, 1.f},   {1.f, 0.f, 1.f} });

	// BEHIND
	AddTriangle({ {1.f, 0.f, 1.f},  {1.f, 1.f, 1.f},   {0.f, 1.f, 1.f } });
	AddTriangle({ {1.f, 0.f, 1.f},  {0.f, 1.f, 1.f},   {0.f, 0.f, 1.f} });

	// LEFT
	AddTriangle({ {0.f, 0.f, 1.f},  {0.f, 1.f, 1.f},   {0.f, 1.f, 0.f } });
	AddTriangle({ {0.f, 0.f, 1.f},  {0.f, 1.f, 0.f},   {0.f, 0.f, 0.f} });

	// UP
	AddTriangle({ {0.f, 1.f, 0.f },   {0.f, 1.f, 1.f},  {1.f, 1.f, 1.f} });
	AddTriangle({ {0.f, 1.f, 0.f },   {1.f, 1.f, 1.f},  {1.f, 1.f, 0.f} });

	// DOWN
	AddTriangle({ {1.f, 0.f, 1.f },   {0.f, 0.f, 1.f},  {0.f, 0.f, 0.f} });
	AddTriangle({ {1.f, 0.f, 1.f },   {0.f, 0.f, 0.f},  {1.f, 0.f, 0.f} });


	SetOrigin({ 0.5f, 0.5f, 0.5f });
	transform.scaling = {0.5f * (float)WINDOW_WIDTH, 0.5f * (float)WINDOW_HEIGHT, 1};
}

