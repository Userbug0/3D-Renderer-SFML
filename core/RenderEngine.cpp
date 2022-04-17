#include "RenderEngine.h"
#include "Vector3.h"
#include "Settings.h"

#include <iostream>


RenderEngine::RenderEngine(const sf::Color& bgColor)
	: m_backgroundColor(bgColor), m_CameraPos(0, 0, 0)
{
	float AspectRatio = (float)WINDOW_HEIGHT / WINDOW_WIDTH;
	float FovRad = 1.f / tanf(FIELD_OF_VIEW * 0.5f);
	float zFar = 2000.f;
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

	cube->AddRotation({ 0.005f, -0.005f, 0.005f });
	Vector3 rotation = cube->getRotation();


	Vector3 light_direction = { 0, 0, -1 };
	light_direction.normalize();


	for (size_t i = 0; i < cube->NumOfTrinagles(); ++i)
	{
		Triangle tri = cube->getTriangle(i);

		rotateTriangle(tri, rotation);

		Vector3 normal = tri.GetNormal();
		float project = Vector3::DotProduct(normal, tri[0] - m_CameraPos);

		if (project < 0.f)
		{
			int shadow = Vector3::DotProduct(light_direction, normal) * 255;
			uint8_t ushadow = shadow;
			for (int i = 0; i < 3; ++i)
				tri.SetVertexColor(i, { ushadow, ushadow, ushadow });

			projectTriangle(tri);
			scaleTriangle(tri);

			tri.Draw(window);
		}

	}

	window->display();
}


void RenderEngine::projectTriangle(Triangle& tri)
{
	for (uint8_t i = 0; i < 3; ++i)
	{
		tri[i].ApplyMultiplication(m_projectionMatrix);
	}

}


void RenderEngine::scaleTriangle(Triangle& tri)
{
	for (uint8_t i = 0; i < 3; ++i)
	{
		tri[i].x += 1.f;
		tri[i].x *= 0.5f * (float)WINDOW_WIDTH;

		tri[i].y += 1.f;
		tri[i].y *= 0.5f * (float)WINDOW_HEIGHT;
	}

}


void RenderEngine::rotateTriangle(Triangle& tri, const Vector3& rotation)
{
	Vector3 relative = Vector3(-0.5f, -0.5f, 1) + Vector3(0.5f, 0.5f, 0.5f);

	float sinx = sinf(rotation.x);
	float siny = sinf(rotation.y);
	float sinz = sinf(rotation.z);

	float cosx = cosf(rotation.x);
	float cosy = cosf(rotation.y);
	float cosz = cosf(rotation.z);


	for (uint8_t i = 0; i < 3; ++i)
	{
		Vector3 original = tri[i] - relative;

		tri[i].x = original.x * (cosz * cosy) +
			original.y * (cosz * siny * sinx - sinz * cosx) +
			original.z * (cosz * siny * cosx + sinz * sinx);

		tri[i].y = original.x * (sinz * cosy) +
			original.y * (sinz * siny * sinx + cosz * cosx) +
			original.z * (sinz * siny * cosx - cosz * sinx);

		tri[i].z = original.x * (-siny) +
			original.y * (cosy * sinx) +
			original.z * (cosy * cosx);

		tri[i] += relative;
	}
}


void RenderEngine::Start()
{

}
