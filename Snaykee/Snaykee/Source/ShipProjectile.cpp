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

		// Shader setup
		/*this->shader->setUniform("glowColor", sf::Glsl::Vec4(0.0f, 1.0f, 0.8f, 1.0f));
		this->shader->setUniform("innerTintColor", sf::Glsl::Vec4(0.0f, 0.6f, 1.0f, 1.0f));
		this->shader->setUniform("glowStrength", 8.0f);
		this->shader->setUniform("glowRadius", 20.0f);
		//this->shader->setUniform("texelSize", sf::Vector2f(1.0f / this->_body.getTexture()->getSize().x, 1.0f / this->_body.getTexture()->getSize().y));
		this->shader->setUniform("texelSize", sf::Vector2f(1.0f / this->_body.getSize().x, 1.0f / this->_body.getSize().y));*/
	}

	void ShipProjectile::Draw(sf::RenderWindow& window)
	{
		window.draw(this->_body, this->shader);
	}

	void ShipProjectile::SetupShader(sf::Shader& newShader, sf::Color color)
	{
		this->shader = &newShader;
		float x = (color.r * 1.0f);
		float y = (color.g * 1.0f);
		float z = (color.b * 1.0f);
		float w = (color.a * 1.0f);

		x /= 255.0f;
		y /= 255.0f;
		z /= 255.0f;
		w /= 255.0f;

		// Shader setup
		this->shader->setUniform("glowColor", sf::Glsl::Vec4(x, y, z, 1.0f));
		this->shader->setUniform("innerTintColor", sf::Glsl::Vec4(x, y, z, 1.0f));
		this->shader->setUniform("glowStrength", 10.0f);
		this->shader->setUniform("glowRadius", 5.0f);
		//this->shader->setUniform("texelSize", sf::Vector2f(1.0f / this->_body.getTexture()->getSize().x, 1.0f / this->_body.getTexture()->getSize().y));
		this->shader->setUniform("texelSize", sf::Vector2f(1.0f / this->_body.getSize().x, 1.0f / this->_body.getSize().y));
	}
}
