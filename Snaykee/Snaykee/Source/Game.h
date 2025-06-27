#pragma once
#include <iostream>
#include "MTigerCore/MR_Math.h"
#include "Defines_SFML.h"

#include "Player_SpaceShip.h"
#include "Obstacle.h"
#include "Border.h"
#include "StarEnergy.h"

class Game : public GameState_SFML
{
public:
	double GAME_STARTING_TIME = 0.0001;
	sf::Clock GAME_CLOCK;
	double GAME_DELTA_TIME;

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

	void Initialize();
	void HandleInput();

	/// <summary>
	/// To be called every frame.
	/// </summary>
	void Update(float fDeltaTime = 0.0f);

	/// <summary>
	/// Perform Draw functionality/logic.
	/// </summary>
	/// <param name="window"></param>
	void Draw(sf::RenderWindow& window);

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
	/// Functionality/logic for game over.
	/// </summary>
	void Execute_GameOver();

	/// <summary>
	/// Functionality for starting (resetting) the game.
	/// </summary>
	void Execute_StartGame();

	/// <summary>
	/// Determine player's ship texture. Based on the ship ID that is within the Game Context.
	/// </summary>
	/// <returns></returns>
	sf::Texture* DeterminePlayerShipTexture();

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
	float _score = 0;
	bool _isGameOVer = false;

	GameContext& _gameContext;

	// Time (clock)
	double _deltaTime;

	// Player
	int _direction;
	Player_SpaceShip _player;
	sf::Texture* _playerTexture_1;
	sf::Texture* _playerTexture_2;
	sf::Texture* _playerTexture_3;
	sf::Texture* _playerTexture_4;
	int _playerShipModel = 0; // 0 = ship (green), 1 = ship (yellow), 2 = ship (white), 3 = ship (dark)

	// Obstacles
	std::vector<Obstacle> _obstacles;

	// Star Energy
	std::vector<StarEnergy> _starEnergies;

	// Screen (window) borders
	Border* leftBorder;
	Border* rightBorder;
	Border* topBorder;
	Border* bottomBorder;

	// Other Visuals
	sf::RectangleShape _background;
	sf::Texture* _backgroundTexture;
	sf::Texture* _asteroid_1_Texture;
	sf::Texture* _asteroid_2_Texture;
	sf::Texture* _asteroid_3_Texture;

	// UI Visuals
	sf::Text _scoreText_UI;
	sf::Font* _scoreTextFont_UI;
	sf::Text _energyText_UI;
	sf::Font* _energyTextFont_UI;
};
