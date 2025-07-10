#pragma once
#include "AssetManager_SFML.h"
#include "AudioManager_SFML.h"
#include "GameStateManager_SFML.h"
#include "SaveLoadSystem.h"

using namespace MR_SFML;

struct GameContext
{
	GameContext(const std::string& gameTitle, int windowWidth, int windowHeight)
		: GAME_TITLE(gameTitle), WINDOW_WIDTH(windowWidth), WINDOW_HEIGHT(windowHeight)
	{
		this->window = new sf::RenderWindow(sf::VideoMode({ this->WINDOW_WIDTH, this->WINDOW_HEIGHT }), gameTitle);

		this->AudioManager.Initialize();
	}

	// Game save system
	SaveLoadSystem SaveSystem;

	// Create asset manager
	AssetManager_SFML AssetManager;

	// Create Audio Manager
	AudioManager_SFML AudioManager;

	// Create game state manager
	GameStateManager_SFML GameStateManager;

	// Tracks game's current state
	CurrentGameState CurrentGameState = SPLASH_SCREEN;

	// Creat game window
	sf::RenderWindow* window;

	// Keep track of mouse position (relative to window).
	sf::Vector2f CurrentMousePositionView()
	{
		return this->window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	}

	// Game window size (dimensions)
	const unsigned int WINDOW_WIDTH;
	const unsigned int WINDOW_HEIGHT;
	float Get_Window_WidthF() { return static_cast<float>(this->WINDOW_WIDTH); }
	float Get_Window_HeightF() { return static_cast<float>(this->WINDOW_HEIGHT); }

	// Game's Title
	const std::string GAME_TITLE;
};
