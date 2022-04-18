#include <algorithm>

#include "RenderEngine.h"
#include "../Vector3.h"
#include "../Settings.h"


RenderEngine::RenderEngine(const sf::Color& bgColor)
	: m_backgroundColor(bgColor), m_CameraPos(0, 0, 0)
{
	float AspectRatio = (float)WINDOW_HEIGHT / WINDOW_WIDTH;
	float FovRad = 1 / tanf((float)FIELD_OF_VIEW * 0.5f);
	float zFar = 2000.f;
	float zNear = 0.1f;

	m_projectionMatrix[0][0] = AspectRatio * FovRad;
	m_projectionMatrix[1][1] = FovRad;
	m_projectionMatrix[2][2] = zFar / (zFar - zNear);
	m_projectionMatrix[3][2] = -zNear * zFar / (zFar - zNear);
	m_projectionMatrix[2][3] = 1;
}


void RenderEngine::Render(sf::RenderWindow* window, const std::vector<GameObject*>& objects)
{
	window->clear(m_backgroundColor);

	for (auto& object : objects)
	{
		object->transform.rotation += { 0.005f, -0.005f, 0.005f };
		renderObject(window, object);
	}

	window->display();
}


void RenderEngine::renderObject(sf::RenderWindow* window, GameObject* object)
{
	Vector3 rotation = object->transform.rotation;
	Vector3 light_direction = { 0, 0, -1 };
	
	std::vector<Triangle> allTriangles;

	for (size_t i = 0; i < object->GetNumOfTriangles(); ++i)
	{
		Triangle tri = object->GetTriangle(i);

		translateTriangle(tri, object->transform.position);

		if(rotation.GetLength() != 0)
			rotateTriangle(tri, rotation, object->transform.position + object->GetOrigin());

		if (isVisible(tri) == true)
		{
			applySimpleLight(tri, light_direction);

			projectTriangle(tri);
			scaleTriangle(tri, object->transform.scaling);

			allTriangles.push_back(tri);
			tri.Draw(window);
		}
	}

	std::sort(allTriangles.begin(), allTriangles.end(), [](const Triangle& t1, const Triangle& t2)
		{
			float z1 = (t1[0].z + t1[1].z + t1[2].z) / 3;
			float z2 = (t2[0].z + t2[1].z + t2[2].z) / 3;
			return z1 > z2;
		});

	for(auto& tri: allTriangles)
		tri.Draw(window);

}


bool RenderEngine::isVisible(const Triangle& tri)
{
	Vector3 normal = tri.GetNormal();
	float project = Vector3::DotProduct(normal, tri[0] - m_CameraPos);
	return project <= 0.f;
}


void RenderEngine::applySimpleLight(Triangle& tri, const Vector3& light_dir)
{
	Vector3 normal = tri.GetNormal();
	float shadow = Vector3::DotProduct(light_dir, normal);
	for (uint8_t i = 0; i < 3; ++i)
	{
		sf::Color origin = tri.GetVertexColor(i);
		tri.SetVertexColor(i, { (uint8_t)(origin.r * shadow), (uint8_t)(origin.g * shadow), (uint8_t)(origin.b * shadow) });
	}

}


void RenderEngine::translateTriangle(Triangle& tri, const Vector3& position)
{
	for (uint8_t i = 0; i < 3; ++i)
	{
		tri[i] += position;
	}
}


void RenderEngine::projectTriangle(Triangle& tri)
{
	for (uint8_t i = 0; i < 3; ++i)
	{
		tri[i].ApplyMultiplication(m_projectionMatrix);
	}
}


void RenderEngine::scaleTriangle(Triangle& tri, const Vector3& scale)
{
	for (uint8_t i = 0; i < 3; ++i)
	{
		tri[i].x += 1.f;
		tri[i].x *= scale.x;

		tri[i].y += 1.f;
		tri[i].y *= scale.y;

		tri[i].z += 1.f;
		tri[i].z *= scale.z;
	}

}


void RenderEngine::rotateTriangle(Triangle& tri, const Vector3& rotation, const Vector3& relative)
{
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
