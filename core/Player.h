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

	Camera* m_Camera;
	static constexpr float m_MoveSpeed = 3.f;
	static constexpr float m_Sensivity = 3.f;
};
