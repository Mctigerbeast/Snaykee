#include "PauseMenu_State.h"

namespace Snaykee
{
	PauseMenu_State::PauseMenu_State(GameContext& gameContext)
		: _gameContext(gameContext), _pauseMenuTitle(*_pauseMenuFont), _resumeButton(gameContext.AssetManager),
		_mainMenuButton(gameContext.AssetManager), _showPlayerHitboxBtn(_gameContext.AssetManager) {
	}

	PauseMenu_State::~PauseMenu_State() {
	}

	void PauseMenu_State::Initialize()
	{
		float midWindowPosX = this->_gameContext.Get_Window_WidthF() / 2.0f;

		this->_pauseMenuBackground = sf::RectangleShape({ this->_gameContext.Get_Window_WidthF(), this->_gameContext.Get_Window_HeightF() });
		this->_pauseMenuBackground.setTexture(&this->_gameContext.AssetManager.Get_Texture("nebulaBackground"));
		this->_pauseMenuBackground.setFillColor(sf::Color(255, 255, 255, 50));

		// Pause menu title text
		this->_pauseMenuFont = &this->_gameContext.AssetManager.Get_Font("mainFont");
		this->_pauseMenuTitle = sf::Text(*this->_pauseMenuFont);
		this->_pauseMenuTitle.setPosition({ midWindowPosX, this->_gameContext.PercentOfWindow_Y(15.0f) });
		this->_pauseMenuTitle.setCharacterSize(this->_gameContext.PercentOfWindow_X(10.0f));
		this->_pauseMenuTitle.setLetterSpacing(2.0f);
		this->_pauseMenuTitle.setString("GAME PAUSED");
		this->_pauseMenuTitle.setFillColor(sf::Color::Black);
		this->_pauseMenuTitle.setOutlineThickness(4.0f);
		this->_pauseMenuTitle.setOutlineColor(sf::Color::White);
		this->_pauseMenuTitle.setOrigin(this->_pauseMenuTitle.getGlobalBounds().size / 2.0f);

		// Resume Button
		this->_resumeButton.Set_ButtonPosition(midWindowPosX, this->_gameContext.PercentOfWindow_Y(40.0f));
		this->_resumeButton.MutiplyButtonSize(this->_gameContext.PercentOfWindow_X(0.25f));
		this->_resumeButton.Set_ButtonText(" RESUME ");
		this->_resumeButton.Set_ButtonTextFont(this->_gameContext.AssetManager.Get_Font("mainFont"));

		this->_resumeButton.Set_ButtonColor_Idle(sf::Color(170, 170, 170));
		this->_resumeButton.Set_ButtonColor_Hover(sf::Color(85, 85, 85));
		this->_resumeButton.Set_ButtonOulineThickness(2.0f);
		this->_resumeButton.Set_ButtonTextOulineThickness(2.0f);
		this->_resumeButton.Set_ButtonTextOulineColor(sf::Color::White);
		this->_resumeButton.Set_ButtonPressedFunction([this] {this->onResume_ButtonPressed(); });

		// Main Menu Button
		this->_mainMenuButton.Set_ButtonPosition(midWindowPosX, this->_gameContext.PercentOfWindow_Y(55.0f));
		this->_mainMenuButton.MutiplyButtonSize(this->_gameContext.PercentOfWindow_X(0.25f));
		this->_mainMenuButton.Set_ButtonText(" MENU ");
		this->_mainMenuButton.Set_ButtonTextFont(this->_gameContext.AssetManager.Get_Font("mainFont"));

		this->_mainMenuButton.Set_ButtonColor_Idle(sf::Color(170, 170, 170));
		this->_mainMenuButton.Set_ButtonColor_Hover(sf::Color(85, 85, 85));
		this->_mainMenuButton.Set_ButtonOulineThickness(2.0f);
		this->_mainMenuButton.Set_ButtonTextOulineThickness(2.0f);
		this->_mainMenuButton.Set_ButtonTextOulineColor(sf::Color::White);
		this->_mainMenuButton.Set_ButtonPressedFunction([this] {this->onMainMenu_ButtonPressed(); });

		// Show player hitbox button
		this->_showPlayerHitboxBtn.Set_ButtonPosition(midWindowPosX, this->_gameContext.PercentOfWindow_Y(70.0f));
		this->_showPlayerHitboxBtn.MutiplyButtonSize(this->_gameContext.PercentOfWindow_X(0.25f));
		this->_showPlayerHitboxBtn.Set_ButtonText(" HITBOX ");
		this->_showPlayerHitboxBtn.Set_ButtonTextFont(this->_gameContext.AssetManager.Get_Font("mainFont"));

		this->_showPlayerHitboxBtn.Set_ButtonOulineThickness(2.0f);
		this->_showPlayerHitboxBtn.Set_ButtonTextOulineThickness(2.0f);
		this->_showPlayerHitboxBtn.Set_ButtonTextOulineColor(sf::Color::White);
		this->_showPlayerHitboxBtn.Set_ButtonPressedFunction([this]() {this->OnToggle_ShowPlayerHitBox(); });

		this->_showPlayerHitboxBtn.Set_ButtonOulineThickness(2.0f);
		if (this->_gameContext.SaveSystem.Get_PlayerData().ShowPlayerHitbox)
			this->_showPlayerHitboxBtn.Set_ButtonStateColors(sf::Color::Green, sf::Color::Green, sf::Color::Green);
		else
			this->_showPlayerHitboxBtn.Set_ButtonStateColors(sf::Color::Red, sf::Color::Red, sf::Color::Red);
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
		if (!this->_gameContext.window->hasFocus())
			return;

		this->HandleInput();
		this->_resumeButton.Update(this->_gameContext.CurrentMousePositionView());
		this->_mainMenuButton.Update(this->_gameContext.CurrentMousePositionView());
		this->_showPlayerHitboxBtn.Update(this->_gameContext.CurrentMousePositionView());
	}

	void PauseMenu_State::Draw(sf::RenderWindow& window)
	{
		window.draw(this->_pauseMenuBackground);
		window.draw(this->_pauseMenuTitle);
		this->_resumeButton.Draw(window);
		this->_mainMenuButton.Draw(window);
		this->_showPlayerHitboxBtn.Draw(window);
	}

	void PauseMenu_State::onResume_ButtonPressed()
	{
		this->_gameContext.CurrentGameState = MR_SFML::GAME;
		this->_gameContext.AudioManager.PlaySound("buttonClick", this->_gameContext.AssetManager);
		this->_gameContext.AudioManager.ResumeMusic();
		this->_gameContext.GameStateManager.RemoveState();
	}

	void PauseMenu_State::onMainMenu_ButtonPressed()
	{
		this->_gameContext.CurrentGameState = MR_SFML::MAIN_MENU;
		this->_gameContext.AudioManager.PlaySound("buttonClick", this->_gameContext.AssetManager);

		// Remove pause state. Now there is only 'Game' state.
		this->_gameContext.GameStateManager.RemoveState();

		// Replace 'Game' state with 'Main Menu' state.
		this->_gameContext.GameStateManager.AddState(std::unique_ptr<GameState_SFML>(new MainMenu_State(this->_gameContext)), true);
	}

	void PauseMenu_State::OnToggle_ShowPlayerHitBox()
	{
		if (this->_gameContext.SaveSystem.Get_PlayerData().ShowPlayerHitbox)
		{
			this->_gameContext.SaveSystem.SavePlayer_ShowPlayerHitbox(false);
			this->_showPlayerHitboxBtn.Set_ButtonStateColors(sf::Color::Red, sf::Color::Red, sf::Color::Red);
		}
		else
		{
			this->_gameContext.SaveSystem.SavePlayer_ShowPlayerHitbox(true);
			this->_showPlayerHitboxBtn.Set_ButtonStateColors(sf::Color::Green, sf::Color::Green, sf::Color::Green);
		}
	}
}
