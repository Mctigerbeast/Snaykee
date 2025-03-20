#include "Obstacle.h"

Obstacle::Obstacle(sf::Vector2f size, sf::Vector2f position, float moveSpeed, sf::Texture* texture, sf::Color color)
	: GameObject_Rectangle(size, position, texture, color)
{
	this->_movementSpeed = moveSpeed;
}

Obstacle::~Obstacle() {}

void Obstacle::Update(float fDeltaTime, int row)
{
	// Apply gravity
	this->_velocity.y += (1.0f * this->_movementSpeed);

	this->_body.move(this->_velocity * fDeltaTime);
}

void Obstacle::Set_MovementSpeed(float newSpeed)
{
	this->_movementSpeed = newSpeed;
}