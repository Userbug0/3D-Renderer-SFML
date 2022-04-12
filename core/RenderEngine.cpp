#include "RenderEngine.h"
#include "Vector3.h"
#include "Settings.h"

#include <iostream>


RenderEngine::RenderEngine(const sf::Color& bgColor)
	: m_backgroundColor(bgColor)
{
	float AspectRatio = (float)WINDOW_HEIGHT / WINDOW_WIDTH;
	float FovRad = 1 / tanf(FIELD_OF_VIEW * 0.5f);
	float zFar = 1000;
	float zNear = 0.1f;

	m_projectionMatrix[0][0] = AspectRatio * FovRad;
	m_projectionMatrix[1][1] = FovRad;
	m_projectionMatrix[2][2] = zFar / (zFar - zNear);
	m_projectionMatrix[3][2] = -zNear * zFar / (zFar - zNear);
	m_projectionMatrix[2][3] = 1;
}


void RenderEngine::Render(sf::RenderWindow* window, Cube* cube)
{
	window->clear(m_backgroundColor);

	for (size_t i = 0; i < cube->NumOfTrinagles(); ++i)
	{
		Triangle tri = cube->getTriangle(i);

		projectTriangle(tri);
		scaleTriangle(tri);

		tri.Draw(window);
	}

	window->display();
}


void RenderEngine::projectTriangle(Triangle& tri)
{
	for (int i = 0; i < 3; ++i)
		tri[i].ApplyMultiplication(m_projectionMatrix);
}


void RenderEngine::scaleTriangle(Triangle& tri)
{
	for (int i = 0; i < 3; ++i)
	{
		tri[i].x += 1.f;
		tri[i].x *= 0.5f * (float)WINDOW_WIDTH;

		tri[i].y += 1.f;
		tri[i].y *= 0.5f * (float)WINDOW_HEIGHT;
	}

}


void RenderEngine::Start()
{

}
