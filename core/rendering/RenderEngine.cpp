#include <algorithm>
#include <list>

#include "RenderEngine.h"
#include "../Vector3.h"
#include "../Settings.h"
#include "../physics/Intersection.h"

#include <iostream>


RenderEngine::RenderEngine(Camera* camera, const sf::Color& bgColor)
	: m_Camera(camera), m_backgroundColor(bgColor), m_currentIndex(0)
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
		renderObject(window, object);
		m_currentIndex = 0;
	}

	window->display();
}


void RenderEngine::renderObject(sf::RenderWindow* window, GameObject* object)
{
	Vector3 light_direction = { 0, 0, 1 };
	
	for (size_t i = 0; i < object->GetNumOfTriangles(); ++i)
	{
		object->ApplyTransform();

		Triangle tri = object->GetTriangle(i);

		if (isVisible(tri) == true)
		{
			if(object->UsingLight == true)
				applySimpleLight(tri, light_direction);

			worldToView(tri);

			uint8_t nClippedTriangles = 0;
			Triangle clipped[2];
			nClippedTriangles = clipTriangleAgainstPlane({ 0.0f, 0.0f, 0.1f }, { 0.0f, 0.0f, 1.0f }, tri, clipped[0], clipped[1]);

			for (uint8_t n = 0; n < nClippedTriangles; n++)
			{
				projectTriangle(clipped[n]);
				scaleTriangle(clipped[n]);

				if (m_currentIndex < m_allTriangles.size())
					m_allTriangles[m_currentIndex] = clipped[n];
				else
					m_allTriangles.push_back(clipped[n]);
				++m_currentIndex;
			}
		}
	}

	std::sort(m_allTriangles.begin(), m_allTriangles.begin() + m_currentIndex, [](const Triangle& t1, const Triangle& t2)
		{
			float z1 = (t1[0].z + t1[1].z + t1[2].z) / 3;
			float z2 = (t2[0].z + t2[1].z + t2[2].z) / 3;
			return z1 > z2;
		});


	for (size_t i = 0; i < m_currentIndex; ++i)
	{
		Triangle clipped[2];
		std::list<Triangle> listTriangles;

		listTriangles.push_back(m_allTriangles[i]);
		size_t nNewTriangles = 1;

		for (uint8_t p = 0; p < 4; ++p)
		{
			uint8_t nTrisToAdd = 0;
			while (nNewTriangles > 0)
			{
				Triangle test = listTriangles.front();
				listTriangles.pop_front();
				--nNewTriangles;
				switch (p)
				{
				case 0:	nTrisToAdd = clipTriangleAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, test, clipped[0], clipped[1]); break;
				case 1:	nTrisToAdd = clipTriangleAgainstPlane({ 0.0f, (float)WINDOW_HEIGHT - 1, 0.0f }, { 0.0f, -1.0f, 0.0f }, test, clipped[0], clipped[1]); break;
				case 2:	nTrisToAdd = clipTriangleAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, test, clipped[0], clipped[1]); break;
				case 3:	nTrisToAdd = clipTriangleAgainstPlane({ (float)WINDOW_WIDTH - 1, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, test, clipped[0], clipped[1]); break;
				}

				for (uint8_t w = 0; w < nTrisToAdd; ++w)
				{
					listTriangles.push_back(clipped[w]);
				}
			}
			nNewTriangles = listTriangles.size();
		}
	}
	for (size_t i = 0; i < m_currentIndex; ++i)
	{
		m_allTriangles[i].Draw(window);
		if(m_ShowClippedTriangles)
			m_allTriangles[i].DrawOutline(window);
	}

}


uint8_t RenderEngine::clipTriangleAgainstPlane(const Vector3& planePoint, const Vector3& planeNormal, const Triangle& inTri,
											Triangle& outTri1, Triangle& outTri2)
{
	uint8_t inside_points[3];
	uint8_t insidePointCount = 0;
	uint8_t outside_points[3];
	uint8_t outsidePointCount = 0;

	float d = -Vector3::DotProduct(planeNormal, planePoint);
	for (uint8_t i = 0; i < 3; ++i)
	{
		float signedDistance = planeNormal.x * inTri[i].x + planeNormal.y * inTri[i].y + planeNormal.z * inTri[i].z	+ d;
		if (signedDistance >= 0)
			inside_points[insidePointCount++] = i;
		else
			outside_points[outsidePointCount++] = i;
	}

	switch (insidePointCount)
	{
	case 0: return 0u;
	case 3: outTri1 = inTri; return 1u;
	case 1:
		for (uint8_t i = 0; i < 3; ++i)
		{
			if(m_ShowClippedTriangles)
				outTri1.SetVertexColor(i, {0, 0, 175});
			else
				outTri1.SetVertexColor(i, inTri.GetVertexColor(i));
		}

		outTri1[0] = inTri[inside_points[0]];
		outTri1[1] = Physics::LineIntersectsPlane(planePoint, planeNormal, outTri1[0], inTri[outside_points[0]]);
		outTri1[2] = Physics::LineIntersectsPlane(planePoint, planeNormal, outTri1[0], inTri[outside_points[1]]);
		return 1u;
	case 2:
		for (uint8_t i = 0; i < 3; ++i)
		{
			if (m_ShowClippedTriangles)
				outTri1.SetVertexColor(i, {175, 0, 0});
			else
				outTri1.SetVertexColor(i, inTri.GetVertexColor(i));
		}
		outTri1[0] = inTri[inside_points[0]];
		outTri1[1] = inTri[inside_points[1]];
		outTri1[2] = Physics::LineIntersectsPlane(planePoint, planeNormal, outTri1[0], inTri[outside_points[0]]);

		for (uint8_t i = 0; i < 3; ++i)
		{
			if (m_ShowClippedTriangles)
				outTri2.SetVertexColor(i, {0, 175, 0});
			else
				outTri2.SetVertexColor(i, inTri.GetVertexColor(i));
		}
		outTri2[0] = inTri[inside_points[1]];
		outTri2[1] = outTri1[2];
		outTri2[2] = Physics::LineIntersectsPlane(planePoint, planeNormal, outTri2[0], inTri[outside_points[0]]);
		return 2u;
	}
	return 0u;
}


void RenderEngine::worldToView(Triangle& tri)
{
	Matrix4 viewMat = m_Camera->GetViewMatrix();

	for (uint8_t i = 0; i < 3; ++i)
	{
		Matrix4::ApplyMultiplication(tri[i], viewMat);
	}
}


bool RenderEngine::isVisible(const Triangle& tri)
{
	Vector3 normal = tri.GetNormal();
	float project = Vector3::DotProduct(normal, tri[0] - m_Camera->GetPosition());
	return project <= 0.f;
}


void RenderEngine::applySimpleLight(Triangle& tri, const Vector3& light_dir)
{
	Vector3 normal = tri.GetNormal();
	float shadow = -Vector3::DotProduct(light_dir, normal);
	if (shadow >= 0 && shadow < 0.45)
	{
		shadow += 0.2;
	}
	if (shadow < 0)
	{
		shadow = 1 + shadow;
		shadow /= (3 - shadow);
	}

	for (uint8_t i = 0; i < 3; ++i)
	{
		sf::Color origin = tri.GetVertexColor(i);
		origin = { (uint8_t)(origin.r * shadow), (uint8_t)(origin.g * shadow), (uint8_t)(origin.b * shadow) };
		tri.SetVertexColor(i, origin);
	}

}


void RenderEngine::projectTriangle(Triangle& tri)
{
	for (uint8_t i = 0; i < 3; ++i)
	{
		Matrix4::ApplyMultiplication(tri[i], m_projectionMatrix);
	}
}


void RenderEngine::scaleTriangle(Triangle& tri)
{
	for (uint8_t i = 0; i < 3; ++i)
	{
		tri[i].x += 1.f;
		tri[i].x *= 0.5f * float(WINDOW_WIDTH);

		tri[i].y += 1.f;
		tri[i].y *= 0.5f * float(WINDOW_HEIGHT);
	}
}


void RenderEngine::HandleEvent(const sf::Event& event)
{

}


void RenderEngine::Start()
{

}
