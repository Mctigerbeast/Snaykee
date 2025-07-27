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

	void ShipProjectile::Draw(sf::RenderWindow& window)
	{
		window.draw(this->_body, this->shader);
	}

	void ShipProjectile::SetupShader(sf::Shader& newShader, sf::Color innerColor, sf::Color outerColor)
	{
		this->shader = &newShader;
		float innerX = (innerColor.r * 1.0f) / 255.0f;
		float innerY = (innerColor.g * 1.0f) / 255.0f;
		float innerZ = (innerColor.b * 1.0f) / 255.0f;
		float innerW = (innerColor.a * 1.0f) / 255.0f;

		float outerX = (outerColor.r * 1.0f) / 255.0f;
		float outerY = (outerColor.g * 1.0f) / 255.0f;
		float outerZ = (outerColor.b * 1.0f) / 255.0f;
		float outerW = (outerColor.a * 1.0f) / 255.0f;

		// Shader setup
		this->shader->setUniform("innerColor", sf::Glsl::Vec4(innerX, innerY, innerZ, innerW));
		this->shader->setUniform("glowColor", sf::Glsl::Vec4(outerX, outerY, outerZ, outerW));
		this->shader->setUniform("glowStrength", 10.0f);
		this->shader->setUniform("glowRadius", 7.0f);
		//this->shader->setUniform("texelSize", sf::Vector2f(1.0f / this->_body.getTexture()->getSize().x, 1.0f / this->_body.getTexture()->getSize().y));
		this->shader->setUniform("texelSize", sf::Vector2f(1.0f / this->_body.getSize().x, 1.0f / this->_body.getSize().y));
	}
}
