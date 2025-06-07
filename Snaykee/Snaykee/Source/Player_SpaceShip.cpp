#include "Player_SpaceShip.h"
#include <iostream>

Player_SpaceShip::Player_SpaceShip()
{
	this->_energyTimer = MR_Utils::CountdownTimer(1.0f);
	this->_energyTimer.StartCountdown();
}

Player_SpaceShip::Player_SpaceShip(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed)
	: Player_TopDown_SFML(texture, imageCount, switchTime, speed)
{
	this->_energyTimer = MR_Utils::CountdownTimer(1.0f);
	this->_energyTimer.StartCountdown();
}

Player_SpaceShip::Player_SpaceShip(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f playerSize, sf::Vector2f playerPos)
	: Player_TopDown_SFML(texture, imageCount, switchTime, speed, playerSize, playerPos)
{
	this->_energyTimer = MR_Utils::CountdownTimer(1.0f);
	this->_energyTimer.StartCountdown();
}

Player_SpaceShip::~Player_SpaceShip() {}

void Player_SpaceShip::Update(float fDeltaTime, int row)
{
	if (this->_isAlive)
	{
		Player_TopDown_SFML::Update(fDeltaTime, row);
		this->_energyTimer.UpdateTimer(fDeltaTime);
		this->Execute_EnergyDepletion();
	}
}

void Player_SpaceShip::OnObstacleHit()
{
	// TODO: May have to tweak after play test; for better gameplay.
	this->RemoveEnergy(7);

	// Player is hit and no more energy = DEAD
	if (this->_energy <= 0)
		this->_isAlive = false;
}

void Player_SpaceShip::AddEnergy(int energyToAdd)
{
	this->_energy += energyToAdd;
	this->CheckEnergyBounds();

	// TODO: Testing purposes only!!!
	std::cout << "Energy Added Player Energy = " << this->_energy << "\n";
}

void Player_SpaceShip::RemoveEnergy(int energyToRemove)
{
	this->_energy -= energyToRemove;
	this->CheckEnergyBounds();

	// TODO: Testing purposes only!!!
	//std::cout << "Energy Removed. Player Energy = " << this->_energy << "\n";
}

void Player_SpaceShip::CheckEnergyBounds()
{
	if (this->_energy > 100)
		this->_energy = 100;
	else if (this->_energy < 0)
		this->_energy = 0;
}

void Player_SpaceShip::Execute_EnergyDepletion()
{
	if (!this->_energyTimer.IsCountingDown())
	{
		this->RemoveEnergy(1);
		this->_energyTimer.StartCountdown();
	}
}

void Player_SpaceShip::ResetPlayer()
{
	if (!this->_isAlive)
	{
		this->_energy = 100;
		this->_isAlive = true;
	}
}

int Player_SpaceShip::Get_Energy() { return this->_energy; }
bool Player_SpaceShip::HasEnergy() { return this->_energy > 0; }
bool Player_SpaceShip::IsAlive() { return this->_isAlive; }
