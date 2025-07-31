#include "Player_SpaceShip.h"
#include <iostream>

namespace Snaykee
{
	Player_SpaceShip::Player_SpaceShip() {
	}

	Player_SpaceShip::Player_SpaceShip(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed)
		: Player_TopDown_SFML(texture, imageCount, switchTime, speed) {
	}

	Player_SpaceShip::Player_SpaceShip(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f playerSize, sf::Vector2f playerPos)
		: Player_TopDown_SFML(texture, imageCount, switchTime, speed, playerSize, playerPos) {
	}

	Player_SpaceShip::~Player_SpaceShip() {
	}

	void Player_SpaceShip::Start()
	{
		if (!this->_isShipStarted)
		{
			this->_isShipStarted = true;

			this->_fireRateTimer = MR_Utils::CountdownTimer(this->_fireRate, [this]() {this->OnResetFire(); });

			this->_energyTimer = MR_Utils::CountdownTimer(1.0f, [this]() {this->Execute_EnergyDepletion(); });
			this->_energyTimer.StartCountdown();

			this->_playerDamageEffectTimer = MR_Utils::CountdownTimer(0.5f, [this]() {this->_playerBody.setFillColor(sf::Color::White); });
			this->_playerCollectStarEffectTimer = MR_Utils::CountdownTimer(0.5f, [this]() {this->_playerBody.setFillColor(sf::Color::White); });
			this->_playerBody.setOutlineColor(sf::Color(255, 255, 255, 100));
		}
	}

	void Player_SpaceShip::Update(float fDeltaTime, int row)
	{
		if (this->_isAlive)
		{
			if (this->HasEnergy()) // Player ship should not be able to move, if no energy
				Player_TopDown_SFML::Update(fDeltaTime, row);

			this->_energyTimer.UpdateTimer(fDeltaTime);
			this->_fireRateTimer.UpdateTimer(fDeltaTime);
			this->_playerDamageEffectTimer.UpdateTimer(fDeltaTime);
			this->_playerCollectStarEffectTimer.UpdateTimer(fDeltaTime);
		}
	}

	void Player_SpaceShip::OnObstacleHit()
	{
		this->RemoveEnergy(7);

		// Player is hit and no more energy = DEAD
		if (this->_energy <= 0)
			this->_isAlive = false;

		// Visual effects
		this->_playerCollectStarEffectTimer.StopCountdown(); // In case collect star visual effect was taking place.
		this->_playerBody.setFillColor(sf::Color::Red);
		this->_playerDamageEffectTimer.StartCountdown();
	}

	void Player_SpaceShip::AddEnergy(int energyToAdd)
	{
		this->_energy += energyToAdd;
		this->CheckEnergyBounds();

		// Visual effects
		this->_playerDamageEffectTimer.StopCountdown(); // In case take damage visual effect was taking place.
		//this->_playerBody.setFillColor(sf::Color::Green);
		this->_playerBody.setFillColor(sf::Color(100, 250, 160, 255));
		this->_playerCollectStarEffectTimer.StartCountdown();
	}

	void Player_SpaceShip::RemoveEnergy(int energyToRemove)
	{
		this->_energy -= energyToRemove;
		this->CheckEnergyBounds();
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
		this->RemoveEnergy(1);
		this->_energyTimer.StartCountdown();
	}

	void Player_SpaceShip::ResetPlayer()
	{
		if (!this->_isAlive)
		{
			this->_energy = 100;
			this->_isAlive = true;
		}
	}

	void Player_SpaceShip::FireProjectile()
	{
		if (!this->_canFire || this->_energy < 2)
			return;

		this->_canFire = false;
		this->_energy -= 2;
		this->_fireRateTimer.StartCountdown();
	}

	void Player_SpaceShip::OnResetFire()
	{
		this->_canFire = true;
	}

	void Player_SpaceShip::ShowHitbox(bool enableHitbox)
	{
		if (enableHitbox)
			this->_playerBody.setOutlineThickness(3.0f);
		else
			this->_playerBody.setOutlineThickness(0.0f);
	}

	int Player_SpaceShip::Get_Energy() { return this->_energy; }
	bool Player_SpaceShip::HasEnergy() { return this->_energy > 0; }
	bool Player_SpaceShip::IsAlive() { return this->_isAlive; }
	bool Player_SpaceShip::CanFireProjectile() { return this->_canFire && (this->_energy > 1); }
}
