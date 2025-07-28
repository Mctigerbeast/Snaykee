#include "GameObject_Rectangle_SFML.h"

namespace MR_SFML
{
	GameObject_Rectangle_SFML::GameObject_Rectangle_SFML(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, sf::Color color)
	{
		this->_body.setSize(size);
		this->_body.setOrigin(this->_body.getSize() / 2.0f);
		this->_body.setPosition(position);
		this->_body.setFillColor(color);

		if (texture != nullptr)
			this->_body.setTexture(texture);
	}

	GameObject_Rectangle_SFML::~GameObject_Rectangle_SFML() {}

	void GameObject_Rectangle_SFML::Draw(sf::RenderWindow& window) { window.draw(this->_body); }

	Collider_SFML GameObject_Rectangle_SFML::Get_Collider() { return Collider_SFML(this->_body); }

	void GameObject_Rectangle_SFML::SetColor(sf::Color newColor) { this->_body.setFillColor(newColor); }

	void GameObject_Rectangle_SFML::Update(float fDeltaTime, int row) {}
}
