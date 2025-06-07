#include "Border.h"

Border::Border(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, sf::Color color)
{
	this->_body.setSize(size);
	this->_body.setPosition(position);
	this->_body.setOrigin(this->_body.getSize() / 2.0f);
	this->_body.setFillColor(color);

	if (texture != nullptr)
		this->_body.setTexture(texture);
}

Border::~Border() {}

void Border::Draw(sf::RenderWindow& window) { window.draw(this->_body); }

Collider_SFML Border::Get_Collider() { return Collider_SFML(this->_body); }

void Border::SetColor(sf::Color newColor) { this->_body.setFillColor(newColor); }

