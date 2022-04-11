#pragma once

#include <SFML/Graphics.hpp>


class RenderEngine
{
public:
	RenderEngine(const sf::Color& bgColor = sf::Color::Black);
	~RenderEngine() = default;

	void Start();
	void Render(sf::RenderWindow* window);

private:
	sf::Color backgroundColor_;
};

