#include "GameObject_Rectangle.h"

GameObject_Rectangle::GameObject_Rectangle(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, sf::Color color)
{
	this->_body.setSize(size);
	this->_body.setPosition(position);
	this->_body.setOrigin(this->_body.getSize() / 2.0f);
	this->_body.setFillColor(color);

	if (texture != nullptr)
		this->_body.setTexture(texture);
}

GameObject_Rectangle::~GameObject_Rectangle() {}

void GameObject_Rectangle::Draw(sf::RenderWindow& window) { window.draw(this->_body); }

Collider_SFML GameObject_Rectangle::Get_Collider() { return Collider_SFML(this->_body); }

void GameObject_Rectangle::SetColor(sf::Color newColor) { this->_body.setFillColor(newColor); }

void GameObject_Rectangle::Update(float fDeltaTime, int row) {}