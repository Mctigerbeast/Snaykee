#pragma once
#include <iostream>
#include "MTigerCore/MR_Math.h"
#include "Player_SpaceShip.h"

#include "Obstacle.h"
#include "Border.h"
#include "StarEnergy.h"
#include "AssetManager_SFML.h"

class Game
{
public:
	// TODO: Get size of screen and do math so that game window is relative to size of screen.
	/*unsigned int WINDOW_WIDTH = 1200;
	unsigned int WINDOW_HEIGHT = 1200;*/

	unsigned int WINDOW_WIDTH = 900;
	unsigned int WINDOW_HEIGHT = 900;

	double GAME_STARTING_TIME = 0.0001;
	sf::Clock GAME_CLOCK;
	double GAME_DELTA_TIME;

	/// <summary>
	/// Returns center/middle of screen.
	/// </summary>
	/// <returns></returns>
	sf::Vector2f Get_CenterOfScreen();

	/// <summary>
	/// Returns the title of the game.
	/// </summary>
	/// <returns></returns>
	const std::string& Get_GameTitle() const;

	/// <summary>
	/// Returns reference of/to the game's resource manager.
	/// </summary>
	/// <returns></returns>
	AssetManager_SFML& Get_ResourceManager();

public:
	/// <summary>
	/// [Constructor] Setup the class.
	/// </summary>
	/// <param name="gameTitle"></param>
	Game(std::string gameTitle, AssetManager_SFML& assetManager);

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

private:
	std::string _gameTitle = "[Game Name/Title]";
	float _score = 0;
	bool _isGameOVer = false;

	AssetManager_SFML& _gameAssetManager;

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
	// TODO: Maybe move into UI class/manager/handler.
	sf::Text _scoreText_UI;
	sf::Font* _scoreTextFont_UI;
	sf::Text _energyText_UI;
	sf::Font* _energyTextFont_UI;
};

