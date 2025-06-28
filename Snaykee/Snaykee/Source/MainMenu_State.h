#pragma once
#include "Defines_SFML.h"
#include "Button_SFML.h"
#include "Game.h"

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

	void PauseState() {}
	void StartState() {}

private:
	GameContext& _gameContext;

	sf::RectangleShape _menuBackground;
	sf::Texture* _menuBackgroundTexture = nullptr;

	sf::Text _gameTitleUI;
	sf::Text _shipSelectUI;
	sf::Text _highScoreUI;
	sf::Font* _menuTextFont = nullptr;

	Button_SFML _playButton;
	Button_SFML _selectShipButton_1;
	Button_SFML _selectShipButton_2;
	Button_SFML _selectShipButton_3;
	Button_SFML _selectShipButton_4;

	unsigned int _selectedShipID = 1; // 1 = ship (green), 2 = ship (yellow), 3 = ship (white), 4 = ship (dark)

private:
	void SetupButtons();
	void OnPlayButtonPressed();
	void OnSelectShip1_ButtonPressed();
	void OnSelectShip2_ButtonPressed();
	void OnSelectShip3_ButtonPressed();
	void OnSelectShip4_ButtonPressed();
	void NewShipSelected(unsigned int shipID);
};
