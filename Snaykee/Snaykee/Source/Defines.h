#pragma once
#include "AssetManager_SFML.h"
#include "AudioManager_SFML.h"
#include "GameStateManager_SFML.h"
#include "SaveLoadSystem.h"

struct GameContext
{
	// Game save system
	SaveLoadSystem SaveSystem;

	// Create asset manager
	MR_SFML::AssetManager_SFML AssetManager;

	// Create Audio Manager
	MR_SFML::AudioManager_SFML AudioManager;

	// Create game state manager
	MR_SFML::GameStateManager_SFML GameStateManager;

	// Tracks game's current state
	MR_SFML::CurrentGameState CurrentGameState = MR_SFML::SPLASH_SCREEN;

	// Game's Title
	const std::string GAME_TITLE;

	// Game window && size (dimensions)
	const unsigned int WINDOW_WIDTH = 0;
	const unsigned int WINDOW_HEIGHT = 0;
	sf::VideoMode* vidMode = nullptr;
	sf::RenderWindow* window = nullptr;

	GameContext(const std::string& gameTitle, unsigned int windowWidth, unsigned int windowHeight)
		: GAME_TITLE(gameTitle), WINDOW_WIDTH(windowWidth), WINDOW_HEIGHT(windowHeight)
	{
		this->vidMode = new sf::VideoMode({ windowWidth, windowHeight });
		this->window = new sf::RenderWindow(*vidMode, "SNAYKEE");
		this->AudioManager.Initialize();
	}

	~GameContext()
	{
		delete this->vidMode;
		delete this->window;
	}

	// Keep track of mouse position (relative to window).
	sf::Vector2f CurrentMousePositionView()
	{
		return this->window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	}

	float Get_Window_WidthF() { return static_cast<float>(this->WINDOW_WIDTH); }
	float Get_Window_HeightF() { return static_cast<float>(this->WINDOW_HEIGHT); }

	void Toggle_PlayerHitbox() { this->_shwHtbx = (this->_shwHtbx) ? false : true; }
	bool PlayerHitbox_Enabled() { return this->_shwHtbx; }

	/// <summary>
	/// Calculates a percentage value (passed-in) of the window's width.
	/// </summary>
	/// <param name="value">Pecentage of window.</param>
	/// <returns>The width value relative-to (based-on) the game window's dimensions.</returns>
	float PercentOfWindow_X(float value) { return  (value / 100.0f) * this->Get_Window_WidthF(); }

	/// <summary>
	/// Calculates a percentage value (passed-in) of the window's height.
	/// </summary>
	/// <param name="value">Pecentage of window.</param>
	/// <returns>The height value relative-to (based-on) the game window's dimensions.</returns>
	float PercentOfWindow_Y(float value) { return  (value / 100.0f) * this->Get_Window_HeightF(); }

private:
	bool _shwHtbx = false;
};
