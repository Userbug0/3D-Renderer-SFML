#pragma once

#include <SFML/Graphics.hpp>

#include "../objects/GameObject.h"
#include "Triangle.h"
#include "../Matrix4.h"
#include "Camera.h"


class RenderEngine
{
public:
	RenderEngine(Camera* camera, const sf::Color& bgColor = sf::Color::Black);
	~RenderEngine() = default;

	void Start();
	void HandleEvent(const sf::Event& event);
	void Render(sf::RenderWindow* window, const std::vector<GameObject*>& objects);

private:
	void renderObject(sf::RenderWindow* window, GameObject* object);

	bool isVisible(const Triangle& tri);
	void applySimpleLight(Triangle& tri, const Vector3& light_dir);

	void worldToView(Triangle& tri);
	void projectTriangle(Triangle& tri);
	void scaleTriangle(Triangle& tri);

	/// <summary>
	/// inTri can generate two others or one triangles(outTri1, ouTri2) or not generate
	/// </summary>
	/// <param name="planeNormal">Must be normalized!</param>
	/// <returns>Shows how many triangles generated.
	/// If 0 - triangle not in the screen, if 1 - valid triangle will be in outTri1</returns>
	uint8_t clipTriangleAgainstPlane(const Vector3& planePoint, const Vector3& planeNormal, const Triangle& inTri,
								 Triangle& outTri1, Triangle& outTri2);

	static const bool m_ShowClippedTriangles = false;

	size_t m_currentIndex;
	std::vector<Triangle> m_allTriangles;

	Camera* m_Camera;

	Matrix4 m_projectionMatrix;
	sf::Color m_backgroundColor;
};

