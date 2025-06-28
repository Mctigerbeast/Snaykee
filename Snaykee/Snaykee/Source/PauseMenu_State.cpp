#include "PauseMenu_State.h"

PauseMenu_State::PauseMenu_State(GameContext& gameContext)
	: _gameContext(gameContext), _pauseMenuTitle(*_pauseMenuFont), _resumeButton(gameContext.AssetManager),
	_mainMenuButton(gameContext.AssetManager) {
}

PauseMenu_State::~PauseMenu_State() {
}

void PauseMenu_State::Initialize()
{
	float midWindowPosX = this->_gameContext.Get_Window_WidthF() / 2.0f;
	float midWindowPosY = this->_gameContext.Get_Window_HeightF() / 2.0f;
	float window_Width = this->_gameContext.Get_Window_WidthF();
	float window_Height = this->_gameContext.Get_Window_HeightF();

	this->_pauseMenuBackground = sf::RectangleShape({ 1800.0f /*this->Get_Window_WidthF()*/, this->_gameContext.Get_Window_HeightF() });
	this->_pauseMenuBackground.setTexture(&this->_gameContext.AssetManager.Get_Texture("purpleBackground"));
	this->_pauseMenuBackground.setFillColor(sf::Color{ 255,255,255,50 });

	// Pause menu title text
	this->_pauseMenuFont = &this->_gameContext.AssetManager.Get_Font("mainFont");
	this->_pauseMenuTitle = sf::Text(*this->_pauseMenuFont);
	this->_pauseMenuTitle.setPosition({ midWindowPosX, window_Height * 0.15f });
	this->_pauseMenuTitle.setCharacterSize(100.0f);
	this->_pauseMenuTitle.setLetterSpacing(2.0f);
	this->_pauseMenuTitle.setString("GAME PAUSED");
	this->_pauseMenuTitle.setFillColor(sf::Color::Black);
	this->_pauseMenuTitle.setOutlineThickness(4.0f);
	this->_pauseMenuTitle.setOutlineColor(sf::Color::White);
	this->_pauseMenuTitle.setOrigin(this->_pauseMenuTitle.getGlobalBounds().size / 2.0f);

	// Resume Button
	this->_resumeButton.Set_ButtonPosition(midWindowPosX, window_Height * 0.40f);
	this->_resumeButton.MutiplyButtonSize(3.0f);
	this->_resumeButton.Set_ButtonText(" RESUME");
	this->_resumeButton.Set_ButtonTextFont(this->_gameContext.AssetManager.Get_Font("mainFont"));

	this->_resumeButton.Set_ButtonColor_Idle(sf::Color(170, 170, 170));
	this->_resumeButton.Set_ButtonColor_Hover(sf::Color(85, 85, 85));
	this->_resumeButton.Set_ButtonOulineThickness(2.0f);
	this->_resumeButton.Set_ButtonTextOulineThickness(2.0f);
	this->_resumeButton.Set_ButtonTextOulineColor(sf::Color::White);
	this->_resumeButton.Set_ButtonPressedFunction([this] {this->onResume_ButtonPressed(); });

	// Main Menu Button
	this->_mainMenuButton.Set_ButtonPosition(midWindowPosX, window_Height * 0.55f);
	this->_mainMenuButton.MutiplyButtonSize(3.0f);
	this->_mainMenuButton.Set_ButtonText(" MENU");
	this->_mainMenuButton.Set_ButtonTextFont(this->_gameContext.AssetManager.Get_Font("mainFont"));

	this->_mainMenuButton.Set_ButtonColor_Idle(sf::Color(170, 170, 170));
	this->_mainMenuButton.Set_ButtonColor_Hover(sf::Color(85, 85, 85));
	this->_mainMenuButton.Set_ButtonOulineThickness(2.0f);
	this->_mainMenuButton.Set_ButtonTextOulineThickness(2.0f);
	this->_mainMenuButton.Set_ButtonTextOulineColor(sf::Color::White);
	this->_mainMenuButton.Set_ButtonPressedFunction([this] {this->onMainMenu_ButtonPressed(); });
}

void PauseMenu_State::HandleInput()
{
	while (const std::optional event = this->_gameContext.window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			this->_gameContext.window->close();
	}
}

void PauseMenu_State::Update(float fDeltaTime)
{
	this->HandleInput();
	this->_resumeButton.Update(this->_gameContext.CurrentMousePositionView());
	this->_mainMenuButton.Update(this->_gameContext.CurrentMousePositionView());
}

void PauseMenu_State::Draw(sf::RenderWindow& window)
{
	window.draw(this->_pauseMenuBackground);
	window.draw(this->_pauseMenuTitle);
	this->_resumeButton.Draw(window);
	this->_mainMenuButton.Draw(window);
}

void PauseMenu_State::onResume_ButtonPressed()
{
	this->_gameContext.CurrentGameState = GAME;
	this->_gameContext.GameStateManager.RemoveState();
}

void PauseMenu_State::onMainMenu_ButtonPressed()
{
	this->_gameContext.CurrentGameState = MAIN_MENU;

	// Remove pause state. Now there is only 'Game' state.
	this->_gameContext.GameStateManager.RemoveState();

	// Replace 'Game' state with 'Main Menu' state.
	this->_gameContext.GameStateManager.AddState(std::unique_ptr<GameState_SFML>(new MainMenu_State(this->_gameContext)), true);
}
