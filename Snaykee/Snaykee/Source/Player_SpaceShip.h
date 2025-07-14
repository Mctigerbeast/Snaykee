#pragma once
#include "Player_TopDown_SFML.h"
#include "MTigerCore/CountdownTimer.h"

using namespace MR_SFML;

namespace Snaykee
{
	class Player_SpaceShip : public Player_TopDown_SFML
	{
	public:
		/// <summary>
		/// [Default Constructor] No initialization/setup.
		/// </summary>
		Player_SpaceShip();

		Player_SpaceShip(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);

		Player_SpaceShip(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f playerSize, sf::Vector2f playerPos);

		~Player_SpaceShip();

		/// <summary>
		/// 'Starts' the player ship. To be called after construction.
		/// </summary>
		void Start();

		/// <summary>
		/// Update the player.
		/// </summary>
		/// <param name="fDeltaTime"></param>
		void Update(float fDeltaTime, int row = 0) override;

		/// <summary>
		/// Logic for when player hits an obstacle.
		/// </summary>
		void OnObstacleHit();

		/// <summary>
		/// Increase player ship's energy.
		/// </summary>
		/// <param name="energyToAdd"></param>
		void AddEnergy(int energyToAdd);

		/// <summary>
		/// Decrease player ship's energy.
		/// </summary>
		/// <param name="energyToAdd"></param>
		void RemoveEnergy(int energyToAdd);

		/// <summary>
		/// Checks and updates player ship's energy to stay within bounds.
		/// </summary>
		void CheckEnergyBounds();

		/// <summary>
		/// Resets the player, after death. If user chooses to play again.
		/// </summary>
		void ResetPlayer();

		/// <summary>
		/// </summary>
		/// <returns>The player ship's current energy.</returns>
		int Get_Energy();

		/// <summary>
		/// </summary>
		/// <returns>(True) if player ship has energy.</returns>
		bool HasEnergy();

		/// <summary>
		/// </summary>
		/// <returns>(True) if player is alive.</returns>
		bool IsAlive();

	private:
		/// <summary>
		/// Logic for player ship's energy depletion.
		/// Continuously decrease energy by one, every second.
		/// </summary>
		void Execute_EnergyDepletion();

	private:
		int _energy = 100;
		bool _isAlive = true;
		MR_Utils::CountdownTimer _energyTimer;

		bool _isShipStarted = false;
	};
}
