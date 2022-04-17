#pragma once

#include <SFML/Graphics.hpp>

#include "../objects/Cube.h"
#include "Triangle.h"
#include "../Matrix.h"


class RenderEngine
{
public:
	RenderEngine(const sf::Color& bgColor = sf::Color::Black);
	~RenderEngine() = default;

	void Start();
	void Render(sf::RenderWindow* window, Cube* cube);

private:
	Vector3 m_CameraPos;


	void projectTriangle(Triangle& tri);
	void scaleTriangle(Triangle& tri);
	void rotateTriangle(Triangle& tri, const Vector3& rotation);

	Matrix4x4 m_projectionMatrix;
	sf::Color m_backgroundColor;
};

