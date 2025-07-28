#include "Obstacle.h"

namespace Snaykee
{
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

		// Apply rotation
		this->_body.rotate(this->_rotationAngle);
	}

	void Obstacle::Set_MovementSpeed(float newSpeed)
	{
		this->_movementSpeed = newSpeed;
	}

	void Obstacle::Reset(sf::Vector2f size, sf::Vector2f position, float moveSpeed, sf::Texture* texture, sf::Color color)
	{
		this->_body.setSize(size);
		this->_body.setOrigin(this->_body.getSize() / 2.0f);
		this->_body.setPosition(position);
		this->_body.setTexture(texture);
		this->_body.setFillColor(color);

		this->_velocity = { 0.0f, 0.0f };
		this->_movementSpeed = moveSpeed;

		// Determine rotation
		int rotDirection = MR_Math::RandomInt(2);
		float rotMultiplier = static_cast<float>(MR_Math::RandomInt(10));
		rotMultiplier *= 0.1f;

		switch (rotDirection)
		{
		case 0:
			this->_rotationAngle = sf::degrees(0.0f);
			break;
		case 1:
			this->_rotationAngle = sf::degrees(1.0f * rotMultiplier);
			break;
		case 2:
			this->_rotationAngle = sf::degrees(-1.0f * rotMultiplier);
			break;
		default:
			break;
		}
	}

	sf::Vector2f Obstacle::Get_Size() { return this->_body.getSize(); }
	sf::Vector2f Obstacle::Get_Position() { return this->_body.getPosition(); }
}
