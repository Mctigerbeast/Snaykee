#pragma once
#include "AssetManager_SFML.h"
#include "GameStateManager_SFML.h"

namespace MR_SFML
{
	struct GameContext
	{
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
	};
}
