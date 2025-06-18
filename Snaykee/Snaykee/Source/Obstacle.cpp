#include "Obstacle.h"

Obstacle::Obstacle(sf::Vector2f size, sf::Vector2f position, float moveSpeed, sf::Texture* texture, sf::Color color)
	: GameObject_Rectangle_SFML(size, position, texture, color)
{
	this->_movementSpeed = moveSpeed;

	// TODO: Testing purposes only!!! Shows collider (outline) of object.
	//this->_body.setOutlineColor(sf::Color::Yellow);
	//this->_body.setOutlineThickness(3.0f);
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