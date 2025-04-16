#include "StarEnergy.h"
#include "MTigerCore_Math/MR_Math.h"

StarEnergy::StarEnergy(sf::Vector2f position, sf::Texture* texture, sf::Color color)
{
	this->_body.setSize({ 20.0f, 20.0f });
	this->_body.setPosition(position);
	this->_body.setOrigin(this->_body.getSize() / 2.0f);
	this->_body.setFillColor(color);

	// Determine enery power
	int choice = MR_Math::RandomIntRange(1, 3);
	switch (choice)
	{
	case 1:
		this->_energyPower = 5;
		this->_body.setFillColor(sf::Color::Red);
		this->_body.setOutlineColor(sf::Color::White);
		this->_body.setOutlineThickness(2.0f);
		break;

	case 2:
		this->_energyPower = 10;
		this->_body.setFillColor(sf::Color::Yellow);
		this->_body.setOutlineColor(sf::Color::White);
		this->_body.setOutlineThickness(2.0f);
		break;

	case 3:
		this->_energyPower = 15;
		this->_body.setFillColor(sf::Color::Blue);
		this->_body.setOutlineColor(sf::Color::White);
		this->_body.setOutlineThickness(2.0f);
		break;
	default:
		break;
	}
}

StarEnergy::~StarEnergy() {}

void StarEnergy::Draw(sf::RenderWindow& window) { window.draw(this->_body); }

Collider_SFML StarEnergy::Get_Collider() { return Collider_SFML(this->_body); }

void StarEnergy::Update(float fDeltaTime, int row) {}

unsigned int StarEnergy::Get_EnergyPower() { return this->_energyPower; }