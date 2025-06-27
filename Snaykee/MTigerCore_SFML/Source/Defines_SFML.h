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
		float Get_Window_WidthF() { return static_cast<float>(this->WINDOW_WIDTH); }
		float Get_Window_HeightF() { return static_cast<float>(this->WINDOW_HEIGHT); }

		// Game's Title
		const std::string GAME_TITLE;

		// Player ship
		void SetPlayerShipID(unsigned int newPlayerShipId)
		{
			this->_playerShipId = newPlayerShipId;

			if (newPlayerShipId > 4)
				this->_playerShipId = 4;
			else if (newPlayerShipId < 1)
				this->_playerShipId = 1;
		}
		unsigned int GetPlayerShipID() { return this->_playerShipId; }
	private:
		unsigned int _playerShipId = 1;
	};
}
