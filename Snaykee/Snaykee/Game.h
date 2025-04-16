#pragma once
#include <iostream>
#include "MTigerCore_Math/MR_Math.h"
#include "Player_SpaceShip.h"

#include "Obstacle.h"
#include "Border.h"
#include "StarEnergy.h"

class Game
{
public:
	unsigned int WINDOW_WIDTH = 1200;
	unsigned int WINDOW_HEIGHT = 1200;

	double GAME_STARTING_TIME = 0.0001;
	sf::Clock GAME_CLOCK;
	double GAME_DELTA_TIME;

	/// <summary>
	/// Returns center/middle of screen.
	/// </summary>
	/// <returns></returns>
	sf::Vector2f Get_CenterOfScreen()
	{
		return sf::Vector2f{ static_cast<float>(WINDOW_WIDTH / 2), static_cast<float>(WINDOW_HEIGHT / 2) };
	}

public:
	/// <summary>
	/// [Constructor] Setup the class.
	/// </summary>
	/// <param name="tt"></param>
	Game(std::string gameTitle);

	/// <summary>
	/// [Destructor] Cleans up the class.
	/// </summary>
	~Game();

	/// <summary>
	/// To be called every frame.
	/// </summary>
	void Tick(float fDeltaTime);

	/// <summary>
	/// Perform Draw functionality/logic.
	/// </summary>
	/// <param name="window"></param>
	void Draw(sf::RenderWindow& window);

	std::string Get_GameTitle() { return this->_gameTitle; }

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

private:
	std::string _gameTitle = "[Game Name/Title]";
	float score = 0;

	// Time (clock)
	double _deltaTime;

	// Player
	int _direction;
	Player_SpaceShip _player;
	sf::Texture* _playertexture;

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
};

