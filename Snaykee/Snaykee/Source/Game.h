#pragma once
#pragma once
#include <iostream>
#include "MTigerCore/MR_Math.h"
#include "MTigerCore/CountdownTimer.h"

#include "Player_SpaceShip.h"
#include "Obstacle.h"
#include "Border.h"
#include "StarEnergy.h"
#include "ShipProjectile.h"

#include "PauseMenu_State.h"
#include "GameOver_State.h"

namespace Snaykee
{
	class Game : public MR_SFML::GameState_SFML
	{
	public:
		const unsigned int OBSTACLES_POOL_SIZE = 200;
		const unsigned int STAR_ENERGY_POOL_SIZE = 3;
		const unsigned int SHIP_PROJECTILE_POOL_SIZE = 20;

		/// <summary>
		/// Returns center/middle of screen.
		/// </summary>
		/// <returns></returns>
		sf::Vector2f Get_CenterOfScreen();

	public:
		/// <summary>
		/// [Constructor] Setup the class.
		/// </summary>
		/// <param name="gameContext"></param>
		Game(GameContext& gameContext);

		/// <summary>
		/// [Destructor] Cleans up the class.
		/// </summary>
		~Game();

		void Initialize() override;
		void HandleInput() override;

		/// <summary>
		/// To be called every frame.
		/// </summary>
		void Update(float fDeltaTime = 0.0f) override;

		/// <summary>
		/// Perform Draw functionality/logic.
		/// </summary>
		/// <param name="window"></param>
		void Draw(sf::RenderWindow& window) override;

		void PauseState() override;
		void StartState() override;

	private:
		/// <summary>
		/// Functionality/logic for generating obstacles.
		/// </summary>
		void GenerateObstacles();

		/// <summary>
		/// Functionality/logic for checking obstacle collisions with player and bottom border.
		/// </summary>
		void CheckObstacleCollisions();

		/// <summary>
		/// Functionality/logic for generating star energy.
		/// </summary>
		void GenerateStarEnergy();

		/// <summary>
		/// Functionality/logic for checking star energy collisions with player.
		/// </summary>
		void CheckStarEnergyCollisions();

		/// <summary>
		/// Functionality/logic for checking ship projectile collisions with obstacles and border(s).
		/// </summary>
		void CheckShipProjectileCollisions();

		/// <summary>
		/// Functionality/logic for game over.
		/// </summary>
		void Execute_GameOver();

		/// <summary>
		/// Functionality for starting (resetting) the game.
		/// </summary>
		void Execute_StartGame();

		/// <summary>
		/// Determine player's ship texture. Based on the ship ID (from Save/Load System).
		/// </summary>
		/// <returns></returns>
		sf::Texture* DeterminePlayerShipTexture();

		/// <summary>
		/// Determine a random obstacle texture.
		/// </summary>
		/// <returns></returns>
		sf::Texture* DetermineObstacleTexture();

		/// <summary>
		/// Resets the firing state after ship projectile has been fired and firing cooldown is over.
		/// </summary>
		void OnResetFire();

		/// <summary>
		/// Get game window's width, as a float.
		/// </summary>
		/// <returns>Return game window's width.</returns>
		float Get_Window_WidthF();

		/// <summary>
		/// Get game window's height, as a float.
		/// </summary>
		/// <returns>Return game window's height.</returns>
		float Get_Window_HeightF();

	private:
		float _score = 0.0f;
		bool _isGameOver = false;
		bool _isGamePaused = false;
		bool _isLowEnergy = false;

		GameContext& _gameContext;

		// Player
		int _direction;
		Player_SpaceShip _player;
		sf::Texture* _playerTexture_1 = nullptr;
		sf::Texture* _playerTexture_2 = nullptr;
		sf::Texture* _playerTexture_3 = nullptr;
		sf::Texture* _playerTexture_4 = nullptr;
		sf::Color _playerProjectileColor;

		// Obstacles
		std::vector<Obstacle_PooledObject> _obstaclesPool;
		int _nextValidPoolObject_Index = 0;

		// Star Energies
		std::vector<StarEnergy_PooledObject> _starEnergiesPool;

		// Ship projectiles (shooting/firing)
		std::vector<ShipProjectile_PooledObject> _shipProjectilesPool;
		MR_Utils::CountdownTimer _fireRateTimer;
		float _fireRate = 0.5f;
		bool _canFire = true;

		// Screen (window) borders
		Border* leftBorder = nullptr;
		Border* rightBorder = nullptr;
		Border* topBorder = nullptr;
		Border* bottomBorder = nullptr;

		// Other Visuals
		sf::RectangleShape _background;
		sf::Texture* _backgroundTexture = nullptr;

		sf::Texture* _asteroid_1_Texture = nullptr;
		sf::Texture* _asteroid_2_Texture = nullptr;
		sf::Texture* _asteroid_3_Texture = nullptr;
		sf::Texture* _asteroid_4_Texture = nullptr;

		sf::Texture* _starEnergy_1_Texture = nullptr;
		sf::Texture* _starEnergy_2_Texture = nullptr;
		sf::Texture* _starEnergy_3_Texture = nullptr;

		sf::Shader _playerProjectileShader = sf::Shader();

		// UI Visuals
		sf::Text _scoreText_UI;
		sf::Font* _scoreTextFont_UI = nullptr;
		sf::Text _energyText_UI;
		sf::Font* _energyTextFont_UI = nullptr;
	};
}
