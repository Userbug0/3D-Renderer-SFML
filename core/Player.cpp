#include <SFML\Window\Event.hpp>

#include "Player.h"
#include "Settings.h"


Player::Player(Camera* camera)
	: m_Camera(camera)
{

}


void Player::Update(const sf::Time& elapsedTime)
{
	moveHandle(elapsedTime.asSeconds());
}


void Player::moveHandle(float felapsedTime)
{

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_Camera->Move(m_Camera->GetDirection() * m_MoveSpeed * felapsedTime);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_Camera->Move(-m_Camera->GetDirection() * m_MoveSpeed * felapsedTime);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_Camera->LookAt(m_Sensivity * felapsedTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_Camera->LookAt(-m_Sensivity * felapsedTime);
}
