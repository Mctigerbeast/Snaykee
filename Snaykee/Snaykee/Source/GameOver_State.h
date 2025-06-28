#pragma once
#include "Defines_SFML.h"
#include "Button_SFML.h"
#include "Game.h"
#include "MainMenu_State.h"

using namespace MR_SFML;

class GameOver_State : public GameState_SFML
{
public:
	GameOver_State(GameContext& gameContext, float playerScore);
	~GameOver_State();

	void Initialize();
	void HandleInput();
	void Update(float fDeltaTime = 0.0f);
	void Draw(sf::RenderWindow& window);

	void PauseState() {}
	void StartState() {}

private:
	float _playerScore;

	GameContext& _gameContext;

	sf::RectangleShape _gameOverBackground;
	Button_SFML _restartButton;
	Button_SFML _mainMenuButton;

	sf::Text _gameOverTitle;
	sf::Text _playerScoreUI;
	sf::Text _highscoreUI;
	sf::Font* _pauseMenuFont = nullptr;

private:
	/// <summary>
	/// Functionality/logic for restarting (playing again).
	/// </summary>
	void onRestart_ButtonPressed();

	/// <summary>
	/// Functionality/logic for going to main menu.
	/// </summary>
	void onMainMenu_ButtonPressed();
};
