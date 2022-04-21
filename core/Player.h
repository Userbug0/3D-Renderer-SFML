#pragma once

#include <SFML\System\Time.hpp>

#include "rendering\Camera.h"


class Player
{
public:
	Player(Camera* camera);

	void Update(const sf::Time& elapsedTime);

private:
	void moveHandle(float felapsedTime);

	static constexpr float m_MoveSpeed = 3.f;
	static constexpr float m_Sensivity = 3.f;

	sf::Vector2i m_MousePos;
	Camera* m_Camera;
};
