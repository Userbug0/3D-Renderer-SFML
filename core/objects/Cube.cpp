#include "Cube.h"

#include "../Settings.h"


Cube::Cube()
	: Cube(1.f, 1.f, 1.f)
{

}


Cube::Cube(float width, float height, float length)
{
	// FRONT
	AddTriangle({ {0.f, 0.f, 0.f},		 {0.f, height, 0.f},     {width, height, 0.f } });
	AddTriangle({ {0.f, 0.f, 0.f},       {width, height, 0.f},   {width, 0.f, 0.f} });

	//RIGHT
	AddTriangle({ {width, 0.f, 0.f},     {width, height, 0.f},    {width, height, length } });
	AddTriangle({ {width, 0.f, 0.f},     {width, height, length}, {width, 0.f, length} });

	// BEHIND
	AddTriangle({ {width, 0.f, length},  {width, height, length}, {0.f, height, length } });
	AddTriangle({ {width, 0.f, length},  {0.f, height, length},	  {0.f, 0.f, length} });

	// LEFT
	AddTriangle({ {0.f, 0.f, length},    {0.f, height, length},   {0.f, height, 0.f } });
	AddTriangle({ {0.f, 0.f, length},	 {0.f, height, 0.f},	  {0.f, 0.f, 0.f} });

	// UP
	AddTriangle({ {0.f, height, 0.f },   {0.f, height, length},   {width, height, length} });
	AddTriangle({ {0.f, height, 0.f },	 {width, height, length}, {width, height, 0.f} });

	// DOWN
	AddTriangle({ {width, 0.f, length }, {0.f, 0.f, length},      {0.f, 0.f, 0.f} });
	AddTriangle({ {width, 0.f, length }, {0.f, 0.f, 0.f},		  {width, 0.f, 0.f} });
}

