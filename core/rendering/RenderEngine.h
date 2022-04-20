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
	void Render(sf::RenderWindow* window, const std::vector<GameObject*>& objects);

private:
	void renderObject(sf::RenderWindow* window, GameObject* object);

	void worldToView(Triangle& tri);

	bool isVisible(const Triangle& tri);
	void applySimpleLight(Triangle& tri, const Vector3& light_dir);
	void translateTriangle(Triangle& tri, const Vector3& position);
	void projectTriangle(Triangle& tri);
	void scaleTriangle(Triangle& tri, const Vector3& scale);
	void rotateTriangle(Triangle& tri, const Vector3& rotation, const Vector3& relative);

	Camera* m_Camera;

	Matrix4 m_projectionMatrix;
	sf::Color m_backgroundColor;
};

