#pragma once
#include <iostream>
//#include <SFML/Graphics.hpp>
#include "MTigerCore_SFML/Player_TopDown_SFML.h"
#include "Obstacle.h"

class Game
{
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
	double GetDeltaTime() { return this->_deltaTime; }
	Player_TopDown_SFML Get_Player_Copy() { return this->_player; }
	Player_TopDown_SFML& Get_Player_Ref() { return this->_player; }

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
	Player_TopDown_SFML _player;
	sf::Texture* _playertexture;

	// Obstacles
	std::vector<Obstacle> _obstacles;
};

