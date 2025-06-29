#include "StarEnergy.h"
#include "MTigerCore/MR_Math.h"

StarEnergy::StarEnergy(sf::Vector2f position, sf::Texture** texture1, sf::Texture** texture2, sf::Texture** texture3, sf::Color color)
	: _starEnergy_1_Texture(texture1), _starEnergy_2_Texture(texture2), _starEnergy_3_Texture(texture3)
{
	this->_body.setSize({ 35.0f, 35.0f });
	this->_body.setPosition(position);
	this->_body.setOrigin(this->_body.getSize() / 2.0f);
	this->_body.setFillColor(color);

	// Determine energy power
	this->DetermineEnergyPower();
}

StarEnergy::~StarEnergy() {}

void StarEnergy::Draw(sf::RenderWindow& window) { window.draw(this->_body); }

Collider_SFML StarEnergy::Get_Collider() { return Collider_SFML(this->_body); }

void StarEnergy::Update(float fDeltaTime, int row) {}

unsigned int StarEnergy::Get_EnergyPower() { return this->_energyPower; }

void StarEnergy::Reset(sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
	this->_body.setSize(size);
	this->_body.setPosition(position);
	this->_body.setOrigin(this->_body.getSize() / 2.0f);
	this->_body.setFillColor(color);

	this->DetermineEnergyPower();
}

void StarEnergy::DetermineEnergyPower()
{
	// TODO: May need to tweak star power values.(maybe 3, 7, and 10)
	int choice = MR_Math::RandomIntRange(1, 3);
	switch (choice)
	{
	case 1:
		this->_energyPower = 3;
		this->_body.setTexture(*this->_starEnergy_1_Texture);
		break;

	case 2:
		this->_energyPower = 6;
		this->_body.setTexture(*this->_starEnergy_2_Texture);
		break;

	case 3:
		this->_energyPower = 10;
		this->_body.setTexture(*this->_starEnergy_3_Texture);
		break;
	default:
		break;
	}
}