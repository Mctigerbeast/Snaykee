#include "StarEnergy.h"


StarEnergy::StarEnergy(unsigned int energyPwr, sf::Vector2f position, sf::Texture* texture, sf::Color color)
	: _energyPower(energyPwr)
{
	this->_body.setSize({ 100.0f, 100.0f });
	this->_body.setPosition(position);
	this->_body.setOrigin(this->_body.getSize() / 2.0f);
	this->_body.setFillColor(color);
}

StarEnergy::~StarEnergy() {}

void StarEnergy::Update(float fDeltaTime, int row) {}