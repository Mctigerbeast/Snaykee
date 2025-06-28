#pragma once
#include "Button_SFML.h"
#include "MainMenu_State.h"

using namespace MR_SFML;

class PauseMenu_State : public GameState_SFML
{
public:
	PauseMenu_State(GameContext& gameContext);
	~PauseMenu_State();

	void Initialize();
	void HandleInput();
	void Update(float fDeltaTime = 0.0f);
	void Draw(sf::RenderWindow& window);

	void PauseState() {}
	void StartState() {}

private:
	GameContext& _gameContext;

	sf::RectangleShape _pauseMenuBackground;
	Button_SFML _resumeButton;
	Button_SFML _mainMenuButton;

	sf::Text _pauseMenuTitle;
	sf::Font* _pauseMenuFont = nullptr;

private:
	/// <summary>
	/// Functionality/logic for resuming the game from pause state.
	/// </summary>
	void onResume_ButtonPressed();

	/// <summary>
	/// Functionality/logic for going to main menu.
	/// </summary>
	void onMainMenu_ButtonPressed();
};
