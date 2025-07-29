#include "MainMenu_State.h"

namespace Snaykee
{
	MainMenu_State::MainMenu_State(GameContext& gameContext)
		: _gameContext(gameContext), _gameTitleUI(*_menuTextFont), _highScoreUI(*_menuTextFont), _shipSelectUI(*_menuTextFont),
		_debriefUI(*_menuTextFont), _playButton(gameContext.AssetManager), _selectShipButton_1(_gameContext.AssetManager),
		_selectShipButton_2(_gameContext.AssetManager), _selectShipButton_3(_gameContext.AssetManager),
		_selectShipButton_4(_gameContext.AssetManager), _controlsButton(_gameContext.AssetManager),
		_creditsButton(_gameContext.AssetManager) {
	}

	MainMenu_State::~MainMenu_State() {}

	void MainMenu_State::Initialize()
	{
		// Load player save data
		this->_gameContext.SaveSystem.LoadPlayerData();

		this->_menuBackgroundTexture = &this->_gameContext.AssetManager.Get_Texture("purpleBackground");
		this->_menuBackground = sf::RectangleShape({ 1800.0f /*this->Get_Window_WidthF()*/, this->_gameContext.Get_Window_HeightF() });
		this->_menuBackground.setTexture(this->_menuBackgroundTexture);
		this->_menuBackground.setFillColor(sf::Color{ 255,255,255,50 });

		this->_gameContext.AssetManager.Get_SoundBuffer("buttonClick");

		this->SetupText();
		this->SetupButtons();
		this->_selectedShipID = this->_gameContext.SaveSystem.Get_PlayerData().SelectedShip;
		this->NewShipSelected(this->_selectedShipID);

		// Play menu music
		this->_gameContext.AudioManager.PlayMusic("Resources/mus_menu_ambience.wav");
	}

	void MainMenu_State::HandleInput()
	{
		while (const std::optional event = this->_gameContext.window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				this->_gameContext.window->close();
		}
	}

	void MainMenu_State::Update(float fDeltaTime)
	{
		this->HandleInput();
		this->_playButton.Update(this->_gameContext.CurrentMousePositionView());
		this->_selectShipButton_1.Update(this->_gameContext.CurrentMousePositionView());
		this->_selectShipButton_2.Update(this->_gameContext.CurrentMousePositionView());
		this->_selectShipButton_3.Update(this->_gameContext.CurrentMousePositionView());
		this->_selectShipButton_4.Update(this->_gameContext.CurrentMousePositionView());
		this->_controlsButton.Update(this->_gameContext.CurrentMousePositionView());
		this->_creditsButton.Update(this->_gameContext.CurrentMousePositionView());
	}

	void MainMenu_State::Draw(sf::RenderWindow& window)
	{
		window.clear();
		window.draw(this->_menuBackground);
		window.draw(this->_gameTitleUI);
		this->_playButton.Draw(window);
		window.draw(this->_shipSelectUI);
		this->_selectShipButton_1.Draw(window);
		this->_selectShipButton_2.Draw(window);
		this->_selectShipButton_3.Draw(window);
		this->_selectShipButton_4.Draw(window);
		window.draw(this->_highScoreUI);
		this->_controlsButton.Draw(window);
		this->_creditsButton.Draw(window);
		window.draw(this->_debriefUI);
	}

	void MainMenu_State::SetupText()
	{
		float midWindowPosX = this->_gameContext.Get_Window_WidthF() / 2.0f;

		// Game title text
		this->_gameTitleUI = sf::Text(this->_gameContext.AssetManager.Get_Font("mainFont"));
		this->_gameTitleUI.setPosition({ midWindowPosX, this->_gameContext.PercentOfWindow_Y(10.0f) });
		this->_gameTitleUI.setCharacterSize(this->_gameContext.PercentOfWindow_X(20.0f));
		this->_gameTitleUI.setLetterSpacing(2.0f);
		this->_gameTitleUI.setString(this->_gameContext.GAME_TITLE);
		this->_gameTitleUI.setFillColor(sf::Color::Black);
		this->_gameTitleUI.setOutlineThickness(4.0f);
		this->_gameTitleUI.setOutlineColor(sf::Color::White);
		this->_gameTitleUI.setOrigin(this->_gameTitleUI.getGlobalBounds().size / 2.0f);

		// Ship select text
		this->_shipSelectUI = sf::Text(this->_gameContext.AssetManager.Get_Font("mainFont"));
		this->_shipSelectUI.setPosition({ midWindowPosX, this->_gameContext.PercentOfWindow_Y(45.0f) });
		this->_shipSelectUI.setCharacterSize(this->_gameContext.PercentOfWindow_X(5.0f));
		this->_shipSelectUI.setLetterSpacing(2.0f);
		this->_shipSelectUI.setString("SHIP SELECT");
		this->_shipSelectUI.setFillColor(sf::Color::Black);
		this->_shipSelectUI.setOutlineThickness(2.0f);
		this->_shipSelectUI.setOutlineColor(sf::Color::White);
		this->_shipSelectUI.setOrigin(this->_shipSelectUI.getGlobalBounds().size / 2.0f);

		// Highscore text
		float playerHighScore = this->_gameContext.SaveSystem.Get_PlayerData().HighScore;
		this->_highScoreUI = sf::Text(this->_gameContext.AssetManager.Get_Font("mainFont"));
		this->_highScoreUI.setPosition({ midWindowPosX, this->_gameContext.PercentOfWindow_Y(70.0f) });
		this->_highScoreUI.setCharacterSize(this->_gameContext.PercentOfWindow_X(5.0f));
		this->_highScoreUI.setLetterSpacing(2.0f);
		this->_highScoreUI.setString("HIGHSCORE: " + std::to_string(playerHighScore));
		this->_highScoreUI.setFillColor(sf::Color::Black);
		this->_highScoreUI.setOutlineThickness(2.0f);
		this->_highScoreUI.setOutlineColor(sf::Color::White);
		this->_highScoreUI.setOrigin(this->_highScoreUI.getGlobalBounds().size / 2.0f);

		// Debrief text
		this->_debriefUI = sf::Text(this->_gameContext.AssetManager.Get_Font("defaultFont"));
		this->_debriefUI.setPosition({ midWindowPosX, this->_gameContext.PercentOfWindow_Y(90.0f) });
		this->_debriefUI.setCharacterSize(this->_gameContext.PercentOfWindow_X(2.25f));
		this->_debriefUI.setLetterSpacing(1.0f);
		this->_debriefUI.setString(this->_debriefString);
		this->_debriefUI.setFillColor(sf::Color::Black);
		this->_debriefUI.setOutlineThickness(2.0f);
		this->_debriefUI.setOutlineColor(sf::Color::White);
		this->_debriefUI.setOrigin(this->_debriefUI.getGlobalBounds().size / 2.0f);
	}

	void MainMenu_State::SetupButtons()
	{
		float midWindowPosX = this->_gameContext.Get_Window_WidthF() / 2.0f;

		// Play Button
		this->_playButton.Set_ButtonPosition(midWindowPosX, this->_gameContext.PercentOfWindow_Y(30.0f));
		this->_playButton.MutiplyButtonSize(3.0f);
		this->_playButton.Set_ButtonText("  PLAY  ");
		this->_playButton.Set_ButtonTextFont(this->_gameContext.AssetManager.Get_Font("mainFont"));
		this->_playButton.Set_ButtonPressedFunction([this]() {this->OnPlayButtonPressed(); });

		this->_playButton.Set_ButtonColor_Idle(sf::Color(170, 170, 170));
		this->_playButton.Set_ButtonColor_Hover(sf::Color(85, 85, 85));
		this->_playButton.Set_ButtonOulineThickness(2.0f);
		this->_playButton.Set_ButtonTextOulineThickness(2.0f);
		this->_playButton.Set_ButtonTextOulineColor(sf::Color::White);

		float shipSelBtnSize = this->_gameContext.PercentOfWindow_X(10.0f);

		// Ship 1 select button
		this->_selectShipButton_1.Set_ButtonSize(shipSelBtnSize, shipSelBtnSize);
		this->_selectShipButton_1.Set_ButtonPosition(this->_gameContext.PercentOfWindow_X(30.0f), this->_gameContext.PercentOfWindow_Y(55.0f));
		this->_selectShipButton_1.Set_ButtonTexture(&this->_gameContext.AssetManager.Get_Texture("greenShip"));
		this->_selectShipButton_1.Set_ButtonColor_Hover(sf::Color(170, 170, 170));
		this->_selectShipButton_1.Set_ButtonPressedFunction([this]() {this->OnSelectShip1_ButtonPressed(); });

		this->_selectShipButton_1.Set_ButtonOulineThickness(2.0f);
		this->_selectShipButton_1.Set_ButtonOulineColor(sf::Color(255, 255, 255, 0));

		// Ship 2 select button
		this->_selectShipButton_2.Set_ButtonSize(shipSelBtnSize, shipSelBtnSize);
		this->_selectShipButton_2.Set_ButtonPosition(this->_gameContext.PercentOfWindow_X(43.0f), this->_gameContext.PercentOfWindow_Y(55.0f));
		this->_selectShipButton_2.Set_ButtonTexture(&this->_gameContext.AssetManager.Get_Texture("yellowShip"));
		this->_selectShipButton_2.Set_ButtonColor_Hover(sf::Color(170, 170, 170));
		this->_selectShipButton_2.Set_ButtonPressedFunction([this]() {this->OnSelectShip2_ButtonPressed(); });

		this->_selectShipButton_2.Set_ButtonOulineThickness(2.0f);
		this->_selectShipButton_2.Set_ButtonOulineColor(sf::Color(255, 255, 255, 0));

		// Ship 3 select button
		this->_selectShipButton_3.Set_ButtonSize(shipSelBtnSize, shipSelBtnSize);
		this->_selectShipButton_3.Set_ButtonPosition(this->_gameContext.PercentOfWindow_X(56.0f), this->_gameContext.PercentOfWindow_Y(55.0f));
		this->_selectShipButton_3.Set_ButtonTexture(&this->_gameContext.AssetManager.Get_Texture("whiteShip"));
		this->_selectShipButton_3.Set_ButtonColor_Hover(sf::Color(170, 170, 170));
		this->_selectShipButton_3.Set_ButtonPressedFunction([this]() {this->OnSelectShip3_ButtonPressed(); });

		this->_selectShipButton_3.Set_ButtonOulineThickness(2.0f);
		this->_selectShipButton_3.Set_ButtonOulineColor(sf::Color(255, 255, 255, 0));

		// Ship 4 select button
		this->_selectShipButton_4.Set_ButtonSize(shipSelBtnSize, shipSelBtnSize);
		this->_selectShipButton_4.Set_ButtonPosition(this->_gameContext.PercentOfWindow_X(69.0f), this->_gameContext.PercentOfWindow_Y(55.0f));
		this->_selectShipButton_4.Set_ButtonTexture(&this->_gameContext.AssetManager.Get_Texture("darkShip"));
		this->_selectShipButton_4.Set_ButtonColor_Hover(sf::Color(170, 170, 170));
		this->_selectShipButton_4.Set_ButtonPressedFunction([this]() {this->OnSelectShip4_ButtonPressed(); });

		this->_selectShipButton_4.Set_ButtonOulineThickness(2.0f);
		this->_selectShipButton_4.Set_ButtonOulineColor(sf::Color(255, 255, 255, 0));

		// Controls Button
		this->_controlsButton.Set_ButtonPosition(this->_gameContext.PercentOfWindow_X(35.0f), this->_gameContext.PercentOfWindow_Y(80.0f));
		this->_controlsButton.MutiplyButtonSize(2.5f);
		this->_controlsButton.Set_ButtonText("KEYBINDS");
		this->_controlsButton.Set_ButtonTextFont(this->_gameContext.AssetManager.Get_Font("mainFont"));
		this->_controlsButton.Set_ButtonPressedFunction([this]() {this->OnControlsButtonPressed(); });

		this->_controlsButton.Set_ButtonColor_Idle(sf::Color(170, 170, 170));
		this->_controlsButton.Set_ButtonColor_Hover(sf::Color(85, 85, 85));
		this->_controlsButton.Set_ButtonOulineThickness(2.0f);
		this->_controlsButton.Set_ButtonTextOulineThickness(2.0f);
		this->_controlsButton.Set_ButtonTextOulineColor(sf::Color::White);

		// Credits Button
		this->_creditsButton.Set_ButtonPosition(this->_gameContext.PercentOfWindow_X(65.0f), this->_gameContext.PercentOfWindow_Y(80.0f));
		this->_creditsButton.MutiplyButtonSize(2.5f);
		this->_creditsButton.Set_ButtonText("CREDITS");
		this->_creditsButton.Set_ButtonTextFont(this->_gameContext.AssetManager.Get_Font("mainFont"));
		this->_creditsButton.Set_ButtonPressedFunction([this]() {this->OnCreditsButtonPressed(); });

		this->_creditsButton.Set_ButtonColor_Idle(sf::Color(170, 170, 170));
		this->_creditsButton.Set_ButtonColor_Hover(sf::Color(85, 85, 85));
		this->_creditsButton.Set_ButtonOulineThickness(2.0f);
		this->_creditsButton.Set_ButtonTextOulineThickness(2.0f);
		this->_creditsButton.Set_ButtonTextOulineColor(sf::Color::White);
	}

	void MainMenu_State::OnPlayButtonPressed()
	{
		this->_gameContext.GameStateManager.Get_CurrentActiveState()->PauseState();
		this->_gameContext.CurrentGameState = MR_SFML::GAME;
		this->_gameContext.GameStateManager.AddState(std::unique_ptr<GameState_SFML>(new Game(this->_gameContext)), true);

		// Play Audio
		this->_gameContext.AudioManager.PlaySound(
			this->_gameContext.AssetManager.Get_SoundBuffer("buttonClick"));
	}

	void MainMenu_State::OnSelectShip1_ButtonPressed()
	{
		this->NewShipSelected(1);
		this->_gameContext.AudioManager.PlaySound("buttonClick", this->_gameContext.AssetManager); // Play audio
	}
	void MainMenu_State::OnSelectShip2_ButtonPressed()
	{
		this->NewShipSelected(2);
		this->_gameContext.AudioManager.PlaySound("buttonClick", this->_gameContext.AssetManager); // Play audio
	}

	void MainMenu_State::OnSelectShip3_ButtonPressed()
	{
		this->NewShipSelected(3);
		this->_gameContext.AudioManager.PlaySound("buttonClick", this->_gameContext.AssetManager); // Play audio
	}

	void MainMenu_State::OnSelectShip4_ButtonPressed()
	{
		this->NewShipSelected(4);
		this->_gameContext.AudioManager.PlaySound("buttonClick", this->_gameContext.AssetManager); // Play audio
	}

	void MainMenu_State::OnControlsButtonPressed()
	{
		this->_gameContext.GameStateManager.Get_CurrentActiveState()->PauseState();
		this->_gameContext.CurrentGameState = MR_SFML::CONTROLS;
		this->_gameContext.GameStateManager.AddState(std::unique_ptr<GameState_SFML>(new GameControls_State(this->_gameContext)), false);

		// Play Audio
		this->_gameContext.AudioManager.PlaySound(
			this->_gameContext.AssetManager.Get_SoundBuffer("buttonClick"));
	}
	
	void MainMenu_State::OnCreditsButtonPressed()
	{
		this->_gameContext.GameStateManager.Get_CurrentActiveState()->PauseState();
		this->_gameContext.CurrentGameState = MR_SFML::CREDITS;
		this->_gameContext.GameStateManager.AddState(std::unique_ptr<GameState_SFML>(new CreditsScreen_State(this->_gameContext)), false);

		// Play Audio
		this->_gameContext.AudioManager.PlaySound(
			this->_gameContext.AssetManager.Get_SoundBuffer("buttonClick"));
	}

	void MainMenu_State::NewShipSelected(unsigned int shipID)
	{
		// Adjust ship ID if needed (too low/high).
		if (shipID > 4) { shipID = 4; }
		else if (shipID < 1) { shipID = 1; }
		this->_selectedShipID = shipID;

		// Save selected ship
		this->_gameContext.SaveSystem.SavePlayer_SelectedShip(this->_selectedShipID);

		// Reset all ship button outlines
		this->_selectShipButton_1.Set_ButtonOulineColor(sf::Color(255, 255, 255, 0));
		this->_selectShipButton_2.Set_ButtonOulineColor(sf::Color(255, 255, 255, 0));
		this->_selectShipButton_3.Set_ButtonOulineColor(sf::Color(255, 255, 255, 0));
		this->_selectShipButton_4.Set_ButtonOulineColor(sf::Color(255, 255, 255, 0));

		// Ouline the selected ship
		switch (this->_selectedShipID)
		{
		case 1:
			this->_selectShipButton_1.Set_ButtonOulineColor(sf::Color::Yellow);
			break;
		case 2:
			this->_selectShipButton_2.Set_ButtonOulineColor(sf::Color::Yellow);
			break;
		case 3:
			this->_selectShipButton_3.Set_ButtonOulineColor(sf::Color::Yellow);
			break;
		case 4:
			this->_selectShipButton_4.Set_ButtonOulineColor(sf::Color::Yellow);
			break;

		default:
			break;
		}
	}
}
