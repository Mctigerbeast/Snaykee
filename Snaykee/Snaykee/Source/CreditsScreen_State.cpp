#include "CreditsScreen_State.h"

namespace Snaykee
{
	CreditsScreen_State::CreditsScreen_State(GameContext& gameContext)
		: _gameContext(gameContext), _creditsTitleUI(*_creditsTextFont), _devsUI(*_creditsTextFont), _soundsUI(*_creditsTextFont), _musicUI(*_creditsTextFont),
		_imagesTexturesUI(*_creditsTextFont), _madeWithUI(*_creditsTextFont), _menuButton(gameContext.AssetManager) {
	}

	CreditsScreen_State::~CreditsScreen_State() {}

	void CreditsScreen_State::Initialize()
	{
		this->_menuBackgroundTexture = &this->_gameContext.AssetManager.Get_Texture("purpleBackground");
		this->_menuBackground = sf::RectangleShape({ this->_gameContext.Get_Window_WidthF() * 1.5f, this->_gameContext.Get_Window_HeightF() });
		this->_menuBackground.setTexture(this->_menuBackgroundTexture);
		this->_menuBackground.setFillColor(sf::Color(255, 255, 255, 60));

		this->SetupText();
		this->SetupButtons();
	}

	void CreditsScreen_State::HandleInput()
	{
		while (const std::optional event = this->_gameContext.window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				this->_gameContext.window->close();
		}
	}

	void CreditsScreen_State::Update(float fDeltaTime)
	{
		if (!this->_gameContext.window->hasFocus())
			return;

		this->HandleInput();
		this->_menuButton.Update(this->_gameContext.CurrentMousePositionView());
	}

	void CreditsScreen_State::Draw(sf::RenderWindow& window)
	{
		window.clear();
		window.draw(this->_menuBackground);
		window.draw(this->_creditsTitleUI);
		window.draw(this->_devsUI);
		window.draw(this->_soundsUI);
		window.draw(this->_musicUI);
		window.draw(this->_imagesTexturesUI);
		window.draw(this->_madeWithUI);
		this->_menuButton.Draw(window);
	}

	void CreditsScreen_State::SetupText()
	{
		float titleCharSize = this->_gameContext.PercentOfWindow_X(4.5f);
		float characterSize = this->_gameContext.PercentOfWindow_X(1.6f);

		float charPosX = this->_gameContext.PercentOfWindow_X(5.0f);

		// Credits title text
		this->_creditsTitleUI = sf::Text(this->_gameContext.AssetManager.Get_Font("defaultFont"));
		this->_creditsTitleUI.setPosition({ charPosX, this->_gameContext.PercentOfWindow_Y(05.0f) });
		this->_creditsTitleUI.setCharacterSize(titleCharSize);
		this->_creditsTitleUI.setLetterSpacing(1.0f);
		this->_creditsTitleUI.setString("CREDITS");
		this->_creditsTitleUI.setFillColor(sf::Color::Black);
		this->_creditsTitleUI.setOutlineThickness(3.0f);
		this->_creditsTitleUI.setOutlineColor(sf::Color::White);

		// Developers text
		this->_devsUI = sf::Text(this->_gameContext.AssetManager.Get_Font("defaultFont"));
		this->_devsUI.setPosition({ charPosX, this->_gameContext.PercentOfWindow_Y(15.0f) });
		this->_devsUI.setCharacterSize(characterSize);
		this->_devsUI.setLetterSpacing(1.0f);
		this->_devsUI.setString(this->_devsString);
		this->_devsUI.setFillColor(sf::Color::Black);
		this->_devsUI.setOutlineThickness(2.0f);
		this->_devsUI.setOutlineColor(sf::Color::White);

		// Sounds text
		this->_soundsUI = sf::Text(this->_gameContext.AssetManager.Get_Font("defaultFont"));
		this->_soundsUI.setPosition({ charPosX, this->_gameContext.PercentOfWindow_Y(27.0f) });
		this->_soundsUI.setCharacterSize(characterSize);
		this->_soundsUI.setLetterSpacing(1.0f);
		this->_soundsUI.setString(this->_soundsString);
		this->_soundsUI.setFillColor(sf::Color::Black);
		this->_soundsUI.setOutlineThickness(2.0f);
		this->_soundsUI.setOutlineColor(sf::Color::White);

		// Music text
		this->_musicUI = sf::Text(this->_gameContext.AssetManager.Get_Font("defaultFont"));
		this->_musicUI.setPosition({ charPosX, this->_gameContext.PercentOfWindow_Y(55.0f) });
		this->_musicUI.setCharacterSize(characterSize);
		this->_musicUI.setLetterSpacing(1.0f);
		this->_musicUI.setString(this->_musicString);
		this->_musicUI.setFillColor(sf::Color::Black);
		this->_musicUI.setOutlineThickness(2.0f);
		this->_musicUI.setOutlineColor(sf::Color::White);

		// Images/textures text
		this->_imagesTexturesUI = sf::Text(this->_gameContext.AssetManager.Get_Font("defaultFont"));
		this->_imagesTexturesUI.setPosition({ charPosX, this->_gameContext.PercentOfWindow_Y(70.0f) });
		this->_imagesTexturesUI.setCharacterSize(characterSize);
		this->_imagesTexturesUI.setLetterSpacing(1.0f);
		this->_imagesTexturesUI.setString(this->_imagesTexturesString);
		this->_imagesTexturesUI.setFillColor(sf::Color::Black);
		this->_imagesTexturesUI.setOutlineThickness(2.0f);
		this->_imagesTexturesUI.setOutlineColor(sf::Color::White);

		this->_madeWithUI = sf::Text(this->_gameContext.AssetManager.Get_Font("defaultFont"));
		this->_madeWithUI.setPosition({ charPosX, this->_gameContext.PercentOfWindow_Y(80.0f) });
		this->_madeWithUI.setCharacterSize(characterSize);
		this->_madeWithUI.setLetterSpacing(1.0f);
		this->_madeWithUI.setString(this->_madeWithString);
		this->_madeWithUI.setFillColor(sf::Color::Black);
		this->_madeWithUI.setOutlineThickness(2.0f);
		this->_madeWithUI.setOutlineColor(sf::Color::White);
	}

	void CreditsScreen_State::SetupButtons()
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

	void CreditsScreen_State::onMainMenu_ButtonPressed()
	{
		this->_gameContext.CurrentGameState = MR_SFML::MAIN_MENU;
		this->_gameContext.AudioManager.PlaySound("buttonClick", this->_gameContext.AssetManager);
		this->_gameContext.GameStateManager.RemoveState();
	}
}
