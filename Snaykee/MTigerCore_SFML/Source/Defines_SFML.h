#pragma once
#include "AssetManager_SFML.h"
#include "GameStateManager_SFML.h"

namespace MR_SFML
{
	struct GameContext
	{
		GameContext(const std::string& gameTitle, int windowWidth, int windowHeight)
			: GAME_TITLE(gameTitle), WINDOW_WIDTH(windowWidth), WINDOW_HEIGHT(windowHeight)
		{
			this->window = new sf::RenderWindow(sf::VideoMode({ this->WINDOW_WIDTH, this->WINDOW_HEIGHT }), gameTitle);
		}

		// Create asset manager
		AssetManager_SFML AssetManager;

		// Create game state manager
		GameStateManager_SFML GameStateManager;

		// Creat game window
		sf::RenderWindow* window;

		// Tracks game's current state
		CurrentGameState CurrentGameState = SPLASH_SCREEN;

		// Keep track of mouse position (relative to window).
		sf::Vector2f CurrentMousePositionView()
		{
			return this->window->mapPixelToCoords(sf::Mouse::getPosition(*window));
		}

		// Game window size (dimensions)
		const unsigned int WINDOW_WIDTH;
		const unsigned int WINDOW_HEIGHT;

		// Game's Title
		const std::string GAME_TITLE;
	};
}
