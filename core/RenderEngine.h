#pragma once

#include <SFML/Graphics.hpp>

#include "Matrix.h"
#include "Vector3.h"
#include "Settings.h"


class RenderEngine
{
public:
	RenderEngine(const sf::Color& bgColor = sf::Color::Black);
	~RenderEngine() = default;

	void Start();
	void Render(sf::RenderWindow* window);

private:

	static constexpr float FieldOfView = (float)M_PI / 2;

	sf::Color m_backgroundColor;
};

