#include "PhysicEngine.h"


void PhysicEngine::Update(const sf::Time& elapsedTime, std::vector<GameObject*> objects)
{
	if (m_Pause == false)
	{
		for (size_t i = 1; i < objects.size(); ++i)
			objects[i]->GetTransform().rotation += m_speedRotation * elapsedTime.asSeconds() * Vector3(0.05f, -0.05f, 0.05f);
	}
}


void PhysicEngine::HandleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::Right)
			m_speedRotation += 4;
		if (event.key.code == sf::Keyboard::Left)
			m_speedRotation -= 4;

		if (event.key.code == sf::Keyboard::Space)
		{
			m_Pause = !m_Pause;
		}
	}
}


void PhysicEngine::Start()
{

}

