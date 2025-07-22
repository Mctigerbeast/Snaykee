#include "ShipProjectile.h"

namespace Snaykee
{
	ShipProjectile::ShipProjectile(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, sf::Color color)
		: GameObject_Rectangle_SFML(size, position, texture, color)
	{
		this->_body.setFillColor(color);

		// TODO: Testing purposes only!!! Shows collider (outline) of object.
		//this->_body.setOutlineColor(sf::Color::Yellow);
		//this->_body.setOutlineThickness(3.0f);
	}

	ShipProjectile::~ShipProjectile() {}

	void ShipProjectile::Update(float fDeltaTime, int row)
	{
		sf::Vector2f movement = { 0.0f, 0.0f };
		movement.y -= 1.0f * this->_movementSpeed * fDeltaTime;
		this->_body.move(movement);
	}

	void ShipProjectile::Set_MovementSpeed(float newSpeed)
	{
		this->_movementSpeed = newSpeed;
	}

	void ShipProjectile::Reset(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, sf::Color color)
	{
		this->_body.setSize(size);
		this->_body.setPosition(position);
		this->_body.setOrigin(this->_body.getSize() / 2.0f);
		this->_body.setTexture(texture);
		this->_body.setFillColor(color);

		this->_velocity = { 0.0f, 0.0f };
	}
}
