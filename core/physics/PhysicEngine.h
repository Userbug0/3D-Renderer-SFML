#pragma once

#include <SFML/System/Time.hpp>

#include "../objects/GameObject.h"


class PhysicEngine
{
public:
	PhysicEngine() = default;
	~PhysicEngine() = default;

	void Update(const sf::Time& elapsedTime, std::vector<GameObject*> objects);
	void HandleEvent(const sf::Event& event);
	void Start();

private:
	bool m_Pause = true;
	float m_speedRotation = 1.f;
};
