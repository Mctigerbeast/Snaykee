#include "MainMenu_State.h"

MainMenu_State::MainMenu_State(GameContext& gameContext)
	: _gameContext(gameContext), _gameTitleUI(*_menuTextFont), _highScoreUI(*_menuTextFont), _shipSelectUI(*_menuTextFont),
	_debriefUI(*_menuTextFont), _playButton(gameContext.AssetManager), _selectShipButton_1(_gameContext.AssetManager),
	_selectShipButton_2(_gameContext.AssetManager), _selectShipButton_3(_gameContext.AssetManager),
	_selectShipButton_4(_gameContext.AssetManager) {
}

MainMenu_State::~MainMenu_State() {}

void MainMenu_State::Initialize()
{
	// Load player save data
	this->_gameContext.SaveSystem.LoadPlayerData();

	this->_menuBackgroundTexture = &this->_gameContext.AssetManager.GetLoad_Texture("purpleBackground", "Resources/bg_space_purple.jpg");
	this->_menuBackground = sf::RectangleShape({ 1800.0f /*this->Get_Window_WidthF()*/, this->_gameContext.Get_Window_HeightF() });
	this->_menuBackground.setTexture(this->_menuBackgroundTexture);
	this->_menuBackground.setFillColor(sf::Color{ 255,255,255,50 });

	this->_gameContext.AssetManager.GetLoad_Audio("buttonClick", "Resources/sfx_button_click.wav");

	this->SetupText();
	this->SetupButtons();
	this->_selectedShipID = this->_gameContext.SaveSystem.Get_PlayerData().SelectedShip;
	this->NewShipSelected(this->_selectedShipID);
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
	window.draw(this->_debriefUI);
}

void MainMenu_State::SetupText()
{
	float midWindowPosX = this->_gameContext.Get_Window_WidthF() / 2.0f;
	float midWindowPosY = this->_gameContext.Get_Window_HeightF() / 2.0f;
	float window_Width = this->_gameContext.Get_Window_WidthF();
	float window_Height = this->_gameContext.Get_Window_HeightF();

	// Game title text
	this->_gameTitleUI = sf::Text(this->_gameContext.AssetManager.GetLoad_Font("mainFont", "Resources/font_playful_time_star.ttf"));
	this->_gameTitleUI.setPosition({ midWindowPosX, window_Height * 0.15f });
	this->_gameTitleUI.setCharacterSize(200.0f);
	this->_gameTitleUI.setLetterSpacing(2.0f);
	this->_gameTitleUI.setString(this->_gameContext.GAME_TITLE);
	this->_gameTitleUI.setFillColor(sf::Color::Black);
	this->_gameTitleUI.setOutlineThickness(4.0f);
	this->_gameTitleUI.setOutlineColor(sf::Color::White);
	this->_gameTitleUI.setOrigin(this->_gameTitleUI.getGlobalBounds().size / 2.0f);

	// Ship select text
	this->_shipSelectUI = sf::Text(this->_gameContext.AssetManager.GetLoad_Font("mainFont", "Resources/font_playful_time_star.ttf"));
	this->_shipSelectUI.setPosition({ midWindowPosX, window_Height * 0.50f });
	this->_shipSelectUI.setCharacterSize(50.0f);
	this->_shipSelectUI.setLetterSpacing(2.0f);
	this->_shipSelectUI.setString("SHIP SELECT");
	this->_shipSelectUI.setFillColor(sf::Color::Black);
	this->_shipSelectUI.setOutlineThickness(2.0f);
	this->_shipSelectUI.setOutlineColor(sf::Color::White);
	this->_shipSelectUI.setOrigin(this->_shipSelectUI.getGlobalBounds().size / 2.0f);


	// Highscore text
	float playerHighScore = this->_gameContext.SaveSystem.Get_PlayerData().HighScore;
	this->_highScoreUI = sf::Text(this->_gameContext.AssetManager.GetLoad_Font("mainFont", "Resources/font_playful_time_star.ttf"));
	this->_highScoreUI.setPosition({ midWindowPosX, window_Height * 0.75f });
	this->_highScoreUI.setCharacterSize(50.0f);
	this->_highScoreUI.setLetterSpacing(2.0f);
	this->_highScoreUI.setString("HIGHSCORE: " + std::to_string(playerHighScore));
	this->_highScoreUI.setFillColor(sf::Color::Black);
	this->_highScoreUI.setOutlineThickness(2.0f);
	this->_highScoreUI.setOutlineColor(sf::Color::White);
	this->_highScoreUI.setOrigin(this->_highScoreUI.getGlobalBounds().size / 2.0f);

	// Debrief text
	this->_debriefUI = sf::Text(this->_gameContext.AssetManager.GetLoad_Font("defaultFont", "Resources/font_cera_pro_modern_medium.ttf"));
	this->_debriefUI.setPosition({ midWindowPosX, window_Height * 0.90f });
	this->_debriefUI.setCharacterSize(25.0f);
	this->_debriefUI.setLetterSpacing(1.0f);
	this->_debriefUI.setString(this->_debriefString);
	this->_debriefUI.setFillColor(sf::Color::Black);
	this->_debriefUI.setOutlineThickness(1.25f);
	this->_debriefUI.setOutlineColor(sf::Color::White);
	this->_debriefUI.setOrigin(this->_debriefUI.getGlobalBounds().size / 2.0f);
}

void MainMenu_State::SetupButtons()
{
	float midWindowPosX = this->_gameContext.Get_Window_WidthF() / 2.0f;
	float midWindowPosY = this->_gameContext.Get_Window_HeightF() / 2.0f;
	float window_Width = this->_gameContext.Get_Window_WidthF();
	float window_Height = this->_gameContext.Get_Window_HeightF();

	// Play Button
	this->_playButton.Set_ButtonPosition(midWindowPosX, window_Height * 0.35f);
	this->_playButton.MutiplyButtonSize(3.0f);
	this->_playButton.Set_ButtonText("  PLAY  ");
	this->_playButton.Set_ButtonTextFont(this->_gameContext.AssetManager.GetLoad_Font("mainFont", "Resources/font_playful_time_star.ttf"));
	this->_playButton.Set_ButtonPressedFunction([this]() {this->OnPlayButtonPressed(); });

	this->_playButton.Set_ButtonColor_Idle(sf::Color(170, 170, 170));
	this->_playButton.Set_ButtonColor_Hover(sf::Color(85, 85, 85));
	this->_playButton.Set_ButtonOulineThickness(2.0f);
	this->_playButton.Set_ButtonTextOulineThickness(2.0f);
	this->_playButton.Set_ButtonTextOulineColor(sf::Color::White);

	// Ship 1 select button
	this->_selectShipButton_1.Set_ButtonSize(window_Width * 0.10f, window_Width * 0.10f);
	this->_selectShipButton_1.Set_ButtonPosition(window_Width * 0.30f, window_Height * 0.60f);
	this->_selectShipButton_1.Set_ButtonTexture(&this->_gameContext.AssetManager.GetLoad_Texture("greenShip", "Resources/spr_spaceship_green.png"));
	this->_selectShipButton_1.Set_ButtonColor_Hover(sf::Color(170, 170, 170));
	this->_selectShipButton_1.Set_ButtonPressedFunction([this]() {this->OnSelectShip1_ButtonPressed(); });

	this->_selectShipButton_1.Set_ButtonOulineThickness(2.0f);
	this->_selectShipButton_1.Set_ButtonOulineColor(sf::Color(255, 255, 255, 0));

	// Ship 2 select button
	this->_selectShipButton_2.Set_ButtonSize(window_Width * 0.10f, window_Width * 0.10f);
	this->_selectShipButton_2.Set_ButtonPosition(window_Width * 0.43f, window_Height * 0.60f);
	this->_selectShipButton_2.Set_ButtonTexture(&this->_gameContext.AssetManager.GetLoad_Texture("yellowShip", "Resources/spr_spaceship_yellow.png"));
	this->_selectShipButton_2.Set_ButtonColor_Hover(sf::Color(170, 170, 170));
	this->_selectShipButton_2.Set_ButtonPressedFunction([this]() {this->OnSelectShip2_ButtonPressed(); });

	this->_selectShipButton_2.Set_ButtonOulineThickness(2.0f);
	this->_selectShipButton_2.Set_ButtonOulineColor(sf::Color(255, 255, 255, 0));

	// Ship 3 select button
	this->_selectShipButton_3.Set_ButtonSize(window_Width * 0.10f, window_Width * 0.10f);
	this->_selectShipButton_3.Set_ButtonPosition(window_Width * 0.56f, window_Height * 0.60f);
	this->_selectShipButton_3.Set_ButtonTexture(&this->_gameContext.AssetManager.GetLoad_Texture("whiteShip", "Resources/spr_spaceship_white.png"));
	this->_selectShipButton_3.Set_ButtonColor_Hover(sf::Color(170, 170, 170));
	this->_selectShipButton_3.Set_ButtonPressedFunction([this]() {this->OnSelectShip3_ButtonPressed(); });

	this->_selectShipButton_3.Set_ButtonOulineThickness(2.0f);
	this->_selectShipButton_3.Set_ButtonOulineColor(sf::Color(255, 255, 255, 0));

	// Ship 4 select button
	this->_selectShipButton_4.Set_ButtonSize(window_Width * 0.10f, window_Width * 0.10f);
	this->_selectShipButton_4.Set_ButtonPosition(window_Width * 0.69f, window_Height * 0.60f);
	this->_selectShipButton_4.Set_ButtonTexture(&this->_gameContext.AssetManager.GetLoad_Texture("darkShip", "Resources/spr_spaceship_dark.png"));
	this->_selectShipButton_4.Set_ButtonColor_Hover(sf::Color(170, 170, 170));
	this->_selectShipButton_4.Set_ButtonPressedFunction([this]() {this->OnSelectShip4_ButtonPressed(); });

	this->_selectShipButton_4.Set_ButtonOulineThickness(2.0f);
	this->_selectShipButton_4.Set_ButtonOulineColor(sf::Color(255, 255, 255, 0));
}

void MainMenu_State::OnPlayButtonPressed()
{
	this->_gameContext.GameStateManager.Get_CurrentActiveState()->PauseState();
	this->_gameContext.CurrentGameState = GAME;
	this->_gameContext.GameStateManager.AddState(std::unique_ptr<GameState_SFML>(new Game(this->_gameContext)), true);

	// Play Audio
}

void MainMenu_State::OnSelectShip1_ButtonPressed()
{
	this->NewShipSelected(1);

	// Play Audio
	this->_gameContext.AudioManager.PlaySound("buttonClick");
}
void MainMenu_State::OnSelectShip2_ButtonPressed()
{
	this->NewShipSelected(2);
}
void MainMenu_State::OnSelectShip3_ButtonPressed()
{
	this->NewShipSelected(3);
}
void MainMenu_State::OnSelectShip4_ButtonPressed()
{
	this->NewShipSelected(4);
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
