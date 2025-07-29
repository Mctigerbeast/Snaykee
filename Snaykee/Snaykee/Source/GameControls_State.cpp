#include "GameControls_State.h"

namespace Snaykee
{
	GameControls_State::GameControls_State(GameContext& gameContext)
		: _gameContext(gameContext), _gameControlsTitleUI(*_gameControlsTextFont), _gameControlsUI(*_gameControlsTextFont),
		_menuButton(gameContext.AssetManager) {
	}

	GameControls_State::~GameControls_State() {}

	void GameControls_State::Initialize()
	{
		this->_menuBackgroundTexture = &this->_gameContext.AssetManager.Get_Texture("purpleBackground");
		this->_menuBackground = sf::RectangleShape({ this->_gameContext.Get_Window_WidthF() * 1.5f, this->_gameContext.Get_Window_HeightF() });
		this->_menuBackground.setTexture(this->_menuBackgroundTexture);
		this->_menuBackground.setFillColor(sf::Color(255, 255, 255, 60));

		this->SetupText();
		this->SetupButtons();
	}

	void GameControls_State::HandleInput()
	{
		while (const std::optional event = this->_gameContext.window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				this->_gameContext.window->close();
		}
	}

	void GameControls_State::Update(float fDeltaTime)
	{
		if (!this->_gameContext.window->hasFocus())
			return;

		this->HandleInput();
		this->_menuButton.Update(this->_gameContext.CurrentMousePositionView());
	}

	void GameControls_State::Draw(sf::RenderWindow& window)
	{
		window.clear();
		window.draw(this->_menuBackground);
		window.draw(this->_gameControlsTitleUI);
		window.draw(this->_gameControlsUI);
		this->_menuButton.Draw(window);
	}

	void GameControls_State::SetupText()
	{
		float titleCharSize = this->_gameContext.PercentOfWindow_X(4.5f);
		float characterSize = this->_gameContext.PercentOfWindow_X(1.7f);

		float charPosX = this->_gameContext.PercentOfWindow_X(4.0f);

		// Game controls title text
		this->_gameControlsTitleUI = sf::Text(this->_gameContext.AssetManager.Get_Font("defaultFont"));
		this->_gameControlsTitleUI.setPosition({ charPosX, this->_gameContext.PercentOfWindow_Y(05.0f) });
		this->_gameControlsTitleUI.setCharacterSize(titleCharSize);
		this->_gameControlsTitleUI.setLetterSpacing(1.125f);
		this->_gameControlsTitleUI.setString("GAME CONTROLS");
		this->_gameControlsTitleUI.setFillColor(sf::Color::Black);
		this->_gameControlsTitleUI.setOutlineThickness(3.0);
		this->_gameControlsTitleUI.setOutlineColor(sf::Color::White);

		// Developers text
		this->_gameControlsUI = sf::Text(this->_gameContext.AssetManager.Get_Font("defaultFont"));
		this->_gameControlsUI.setPosition({ charPosX, this->_gameContext.PercentOfWindow_Y(15.0f) });
		this->_gameControlsUI.setCharacterSize(characterSize);
		this->_gameControlsUI.setLetterSpacing(1.125f);
		this->_gameControlsUI.setString(this->_gameControlsString);
		this->_gameControlsUI.setFillColor(sf::Color::Black);
		this->_gameControlsUI.setOutlineThickness(2.0f);
		this->_gameControlsUI.setOutlineColor(sf::Color::White);
	}

	void GameControls_State::SetupButtons()
	{
		float midWindowPosX = this->_gameContext.Get_Window_WidthF() / 2.0f;

		// Main Menu Button
		this->_menuButton.Set_ButtonPosition(midWindowPosX, this->_gameContext.PercentOfWindow_Y(90.0f));
		this->_menuButton.MutiplyButtonSize(this->_gameContext.PercentOfWindow_X(0.25f));
		this->_menuButton.Set_ButtonText(" MENU ");
		this->_menuButton.Set_ButtonTextFont(this->_gameContext.AssetManager.Get_Font("mainFont"));
		this->_menuButton.Set_ButtonPressedFunction([this]() {this->onMainMenu_ButtonPressed(); });

		this->_menuButton.Set_ButtonColor_Idle(sf::Color(170, 170, 170));
		this->_menuButton.Set_ButtonColor_Hover(sf::Color(85, 85, 85));
		this->_menuButton.Set_ButtonOulineThickness(2.0f);
		this->_menuButton.Set_ButtonTextOulineThickness(2.0f);
		this->_menuButton.Set_ButtonTextOulineColor(sf::Color::White);
	}

	void GameControls_State::onMainMenu_ButtonPressed()
	{
		this->_gameContext.CurrentGameState = MR_SFML::MAIN_MENU;
		this->_gameContext.AudioManager.PlaySound("buttonClick", this->_gameContext.AssetManager);
		this->_gameContext.GameStateManager.RemoveState();
	}
}
