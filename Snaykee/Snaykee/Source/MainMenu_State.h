#pragma once
#include "Defines.h"
#include "Game.h"

using namespace MR_SFML;

class MainMenu_State : public GameState_SFML
{
public:
	MainMenu_State(GameContext& gameContext);
	~MainMenu_State();

	void Initialize() override;
	void HandleInput() override;
	void Update(float fDeltaTime = 0.0f) override;
	void Draw(sf::RenderWindow& window) override;

	void PauseState() override {}
	void StartState() override {}

private:
	GameContext& _gameContext;

	sf::RectangleShape _menuBackground;
	sf::Texture* _menuBackgroundTexture = nullptr;

	sf::Text _gameTitleUI;
	sf::Text _shipSelectUI;
	sf::Text _highScoreUI;
	sf::Text _debriefUI;
	sf::Font* _menuTextFont = nullptr;

	Button_SFML _playButton;
	Button_SFML _selectShipButton_1;
	Button_SFML _selectShipButton_2;
	Button_SFML _selectShipButton_3;
	Button_SFML _selectShipButton_4;
	unsigned int _selectedShipID = 1; // 1 = ship (green), 2 = ship (yellow), 3 = ship (white), 4 = ship (dark)

	std::string _debriefString = "DEBRIEF: \nAs the captain of a lone spacecraft hurtling through the cosmos, your mission is simple: \nSTAY ALIVE. Dodge deadly obstacles, navigate treacherous celestial terrain, \nand collect vital star energy to keep your ship fueled and functional.";

private:
	void SetupText();
	void SetupButtons();
	void OnPlayButtonPressed();
	void OnSelectShip1_ButtonPressed();
	void OnSelectShip2_ButtonPressed();
	void OnSelectShip3_ButtonPressed();
	void OnSelectShip4_ButtonPressed();
	void NewShipSelected(unsigned int shipID);
};
