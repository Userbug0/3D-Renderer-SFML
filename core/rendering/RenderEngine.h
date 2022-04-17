#pragma once

#include <SFML/Graphics.hpp>

#include "../objects/GameObject.h"
#include "Triangle.h"
#include "../Matrix.h"


class RenderEngine
{
public:
	RenderEngine(const sf::Color& bgColor = sf::Color::Black);
	~RenderEngine() = default;

	void Start();
	void Render(sf::RenderWindow* window, const std::vector<GameObject*>& objects);

private:
	void renderObject(sf::RenderWindow* window, GameObject* object);

	bool isVisible(const Triangle& tri);
	void applySimpleLight(Triangle& tri, const Vector3& light_dir);
	void translateTriangle(Triangle& tri, const Vector3& position);
	void projectTriangle(Triangle& tri);
	void scaleTriangle(Triangle& tri, const Vector3& scale);
	void rotateTriangle(Triangle& tri, const Vector3& rotation, const Vector3& relative);

	Vector3 m_CameraPos;

	Matrix4x4 m_projectionMatrix;
	sf::Color m_backgroundColor;
};

