#include "Obstacle.h"

Obstacle::Obstacle(sf::Vector2f size, sf::Vector2f position, float moveSpeed, sf::Texture* texture, sf::Color color)
	: GameObject_Rectangle_SFML(size, position, texture, color)
{
	this->_movementSpeed = moveSpeed;
	this->_body.setFillColor(color);

	// TODO: Testing purposes only!!! Shows collider (outline) of object.
	//this->_body.setOutlineColor(sf::Color::Yellow);
	//this->_body.setOutlineThickness(3.0f);
}

Obstacle::~Obstacle() {}

void Obstacle::Update(float fDeltaTime, int row)
{
	// Apply movement velocity
	this->_velocity.y += (1.0f * this->_movementSpeed);
	this->_body.move(this->_velocity * fDeltaTime);
}

void Obstacle::Set_MovementSpeed(float newSpeed)
{
	this->_movementSpeed = newSpeed;
}

void Obstacle::Reset(sf::Vector2f size, sf::Vector2f position, float moveSpeed, sf::Texture* texture, sf::Color color)
{
	this->_body.setSize(size);
	this->_body.setPosition(position);
	this->_body.setOrigin(this->_body.getSize() / 2.0f);
	this->_body.setTexture(texture);
	this->_body.setFillColor(color);

	this->_velocity = { 0.0f, 0.0f };
	this->_movementSpeed = moveSpeed;
}