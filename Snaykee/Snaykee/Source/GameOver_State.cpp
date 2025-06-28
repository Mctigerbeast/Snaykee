#include "GameOver_State.h"

GameOver_State::GameOver_State(GameContext& gameContext, float playerScore)
	:_gameContext(gameContext), _playerScore(playerScore), _restartButton(gameContext.AssetManager),
	_mainMenuButton(gameContext.AssetManager), _gameOverTitle(*_pauseMenuFont),
	_playerScoreUI(*_pauseMenuFont), _highscoreUI(*_pauseMenuFont) {
}

GameOver_State::~GameOver_State() {
}

void GameOver_State::Initialize()
{
	float midWindowPosX = this->_gameContext.Get_Window_WidthF() / 2.0f;
	float midWindowPosY = this->_gameContext.Get_Window_HeightF() / 2.0f;
	float window_Width = this->_gameContext.Get_Window_WidthF();
	float window_Height = this->_gameContext.Get_Window_HeightF();

	this->_gameOverBackground = sf::RectangleShape({ 1800.0f /*this->Get_Window_WidthF()*/, this->_gameContext.Get_Window_HeightF() });
	this->_gameOverBackground.setTexture(&this->_gameContext.AssetManager.Get_Texture("purpleBackground"));
	this->_gameOverBackground.setFillColor(sf::Color{ 255,255,255,50 });

	this->_pauseMenuFont = &this->_gameContext.AssetManager.Get_Font("mainFont");

#pragma region UI Text
	// Pause menu title text
	this->_gameOverTitle = sf::Text(*this->_pauseMenuFont);
	this->_gameOverTitle.setPosition({ midWindowPosX, window_Height * 0.15f });
	this->_gameOverTitle.setCharacterSize(100.0f);
	this->_gameOverTitle.setLetterSpacing(2.0f);
	this->_gameOverTitle.setString("GAME OVER");
	this->_gameOverTitle.setFillColor(sf::Color::Black);
	this->_gameOverTitle.setOutlineThickness(4.0f);
	this->_gameOverTitle.setOutlineColor(sf::Color(255, 50, 50));
	this->_gameOverTitle.setOrigin(this->_gameOverTitle.getGlobalBounds().size / 2.0f);

	// Player score text
	this->_playerScoreUI = sf::Text(this->_gameContext.AssetManager.Get_Font("mainFont"));
	this->_playerScoreUI.setPosition({ midWindowPosX, window_Height * 0.35f });
	this->_playerScoreUI.setCharacterSize(50.0f);
	this->_playerScoreUI.setLetterSpacing(2.0f);
	this->_playerScoreUI.setString("SCORE: " + std::to_string(this->_playerScore));
	this->_playerScoreUI.setFillColor(sf::Color::Black);
	this->_playerScoreUI.setOutlineThickness(2.0f);
	this->_playerScoreUI.setOutlineColor(sf::Color::White);
	this->_playerScoreUI.setOrigin(this->_playerScoreUI.getGlobalBounds().size / 2.0f);

	// Highscore text
	this->_gameContext.SaveSystem.LoadPlayerData(); // Load player data
	float playerHighScore = this->_gameContext.SaveSystem.Get_PlayerData().HighScore;

	this->_highscoreUI = sf::Text(this->_gameContext.AssetManager.Get_Font("mainFont"));
	this->_highscoreUI.setPosition({ midWindowPosX, window_Height * 0.45f });
	this->_highscoreUI.setCharacterSize(50.0f);
	this->_highscoreUI.setLetterSpacing(2.0f);
	this->_highscoreUI.setString("HIGHSCORE: " + std::to_string(playerHighScore));
	this->_highscoreUI.setFillColor(sf::Color::Black);
	this->_highscoreUI.setOutlineThickness(2.0f);
	this->_highscoreUI.setOutlineColor(sf::Color::White);
	this->_highscoreUI.setOrigin(this->_highscoreUI.getGlobalBounds().size / 2.0f);
#pragma endregion

#pragma region UI Buttons
	// Resume Button
	this->_restartButton.Set_ButtonPosition(midWindowPosX, window_Height * 0.60f);
	this->_restartButton.MutiplyButtonSize(3.0f);
	this->_restartButton.Set_ButtonText("RESTART");
	this->_restartButton.Set_ButtonTextFont(this->_gameContext.AssetManager.Get_Font("mainFont"));

	this->_restartButton.Set_ButtonColor_Idle(sf::Color(170, 170, 170));
	this->_restartButton.Set_ButtonColor_Hover(sf::Color(85, 85, 85));
	this->_restartButton.Set_ButtonOulineThickness(2.0f);
	this->_restartButton.Set_ButtonTextOulineThickness(2.0f);
	this->_restartButton.Set_ButtonTextOulineColor(sf::Color::White);
	this->_restartButton.Set_ButtonPressedFunction([this] {this->onRestart_ButtonPressed(); });

	// Main Menu Button
	this->_mainMenuButton.Set_ButtonPosition(midWindowPosX, window_Height * 0.75f);
	this->_mainMenuButton.MutiplyButtonSize(3.0f);
	this->_mainMenuButton.Set_ButtonText(" MENU ");
	this->_mainMenuButton.Set_ButtonTextFont(this->_gameContext.AssetManager.Get_Font("mainFont"));

	this->_mainMenuButton.Set_ButtonColor_Idle(sf::Color(170, 170, 170));
	this->_mainMenuButton.Set_ButtonColor_Hover(sf::Color(85, 85, 85));
	this->_mainMenuButton.Set_ButtonOulineThickness(2.0f);
	this->_mainMenuButton.Set_ButtonTextOulineThickness(2.0f);
	this->_mainMenuButton.Set_ButtonTextOulineColor(sf::Color::White);
	this->_mainMenuButton.Set_ButtonPressedFunction([this] {this->onMainMenu_ButtonPressed(); });
#pragma endregion
}

void GameOver_State::HandleInput()
{
	while (const std::optional event = this->_gameContext.window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			this->_gameContext.window->close();
	}
}

void GameOver_State::Update(float fDeltaTime)
{
	this->HandleInput();
	this->_restartButton.Update(this->_gameContext.CurrentMousePositionView());
	this->_mainMenuButton.Update(this->_gameContext.CurrentMousePositionView());
}

void GameOver_State::Draw(sf::RenderWindow& window)
{
	window.draw(this->_gameOverBackground);
	window.draw(this->_gameOverTitle);
	window.draw(this->_playerScoreUI);
	window.draw(this->_highscoreUI);
	this->_restartButton.Draw(window);
	this->_mainMenuButton.Draw(window);
}

void GameOver_State::onRestart_ButtonPressed()
{
	this->_gameContext.CurrentGameState = GAME;
	this->_gameContext.GameStateManager.AddState(std::unique_ptr<GameState_SFML>(new Game(this->_gameContext)), true);
}

void GameOver_State::onMainMenu_ButtonPressed()
{
	this->_gameContext.CurrentGameState = MAIN_MENU;

	// Replace 'Game Over' state with 'Main Menu' state.
	this->_gameContext.GameStateManager.AddState(std::unique_ptr<GameState_SFML>(new MainMenu_State(this->_gameContext)), true);
}
