#pragma once
#include "Defines_SFML.h"
#include "Button_SFML.h"

using namespace MR_SFML;

class MainMenu_State : public GameState_SFML
{
public:
	MainMenu_State(GameContext& gameContext);
	~MainMenu_State();

	void Initialize();
	void HandleInput();
	void Update(float fDeltaTime = 0.0f);
	void Draw(sf::RenderWindow& window);

	void PauseState();
	void StartState();

private:
	GameContext& _gameContext;

	sf::RectangleShape _menuBackground;

	Button_SFML _playButton;
};
