#include "Button_SFML.h"

namespace MR_SFML
{
	Button_SFML::Button_SFML(AssetManager_SFML& assetManager)
		:_assetManager(assetManager), _buttonText(*_buttonTextFont)
	{
		this->_buttonBody.setPosition({ 0.0f, 0.0f });
		this->_buttonBody.setSize({ 100.0f, 35.0f });
		this->_buttonBody.setOrigin(this->_buttonBody.getSize() / 2.0f);
		this->_buttonBody.setFillColor(this->_buttonColor_Idle);

		this->_buttonTextFont = &this->_assetManager.GetLoad_Font("defaultFont", "Resources/font_cera_pro_modern_medium.ttf");

		this->_buttonText = sf::Text(*this->_buttonTextFont, this->_buttonTextString);
		this->_buttonText.setPosition({ 0.0f, 0.0f });
		this->_buttonText.setOrigin(this->_buttonBody.getOrigin());
		this->_buttonText.setFillColor(sf::Color::Black);
	}

	Button_SFML::Button_SFML(AssetManager_SFML& assetManager, sf::Vector2f buttonPosition, sf::Vector2f buttonSize, sf::Texture* btnTexture)
		: _assetManager(assetManager), _buttonText(*_buttonTextFont)
	{
		this->_buttonBody.setPosition(buttonPosition);
		this->_buttonBody.setSize(buttonSize);
		this->_buttonBody.setOrigin(this->_buttonBody.getSize() / 2.0f);
		this->_buttonBody.setFillColor(this->_buttonColor_Idle);

		// Button's texture
		this->_buttonTexture = btnTexture;
		if (btnTexture != nullptr)
			this->_buttonBody.setTexture(this->_buttonTexture);

		// Button's text
		this->_buttonTextFont = &this->_assetManager.GetLoad_Font("defaultFont", "Resources/font_cera_pro_modern_medium.ttf");
		this->_buttonText = sf::Text(*this->_buttonTextFont, this->_buttonTextString);
		this->_buttonText.setPosition(buttonPosition);
		this->_buttonText.setOrigin(this->_buttonBody.getOrigin());
		this->_buttonText.setFillColor(sf::Color::Black);
	}

	Button_SFML::~Button_SFML()
	{
		delete this->_buttonTexture;
	}

	void Button_SFML::Update(sf::Vector2f mousePositionInWindow)
	{
		// Mouse is hovering over button
		if (this->_buttonBody.getGlobalBounds().contains(mousePositionInWindow))
		{
			this->_buttonState = BUTTON_HOVER;
			this->_buttonBody.setFillColor(this->_buttonColor_Hover);

			// Mouse is pressed while hovering over button
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				this->_buttonState = BUTTON_PRESSED;
				this->_buttonBody.setFillColor(this->_buttonColor_Pressed);

				if (this->ButtonPressedFunction)
					this->ButtonPressedFunction();
			}
		}
		else
		{
			if (this->_buttonState != BUTTON_IDLE)
				this->_buttonState = BUTTON_IDLE;

			if (this->_buttonBody.getFillColor() != this->_buttonColor_Idle)
				this->_buttonBody.setFillColor(this->_buttonColor_Idle);
		}
	}

	void Button_SFML::Draw(sf::RenderWindow& window)
	{
		window.draw(this->_buttonBody);
		window.draw(this->_buttonText);
	}

	void Button_SFML::MutiplyButtonSize(float multiplier)
	{
		this->_buttonBody.setSize(this->_buttonBody.getSize() * multiplier);
		this->_buttonText.setCharacterSize(this->_buttonText.getCharacterSize() * multiplier);
		this->UpdateButtonOrigin();
	}

	void Button_SFML::Set_ButtonPressedFunction(std::function<void()> newButnPressFunc)
	{
		this->ButtonPressedFunction = newButnPressFunc;
	}

	void Button_SFML::Set_ButtonText(const std::string& newText)
	{
		this->_buttonText.setString(newText);
		this->_buttonTextString = newText;
	}

	void Button_SFML::Set_ButtonTextFont(sf::Font& newFont)
	{
		this->_buttonTextFont = &newFont;
		this->_buttonText.setFont(*this->_buttonTextFont);
	}

	void Button_SFML::Set_ButtonPosition(float posX, float posY)
	{
		this->_buttonBody.setPosition({ posX, posY });
		this->_buttonText.setPosition({ posX, posY });
		this->UpdateButtonOrigin();
	}

	void Button_SFML::Set_ButtonSize(float width, float height)
	{
		this->_buttonBody.setSize({ width, height });
		this->UpdateButtonOrigin();
	}

	void Button_SFML::Set_ButtonOulineThickness(float newThicknessVal)
	{
		this->_buttonBody.setOutlineThickness(newThicknessVal);
	}
	
	void Button_SFML::Set_ButtonTextOulineThickness(float newThicknessVal)
	{
		this->_buttonText.setOutlineThickness(newThicknessVal);
	}

	void Button_SFML::Set_ButtonTexture(sf::Texture* newTexture)
	{
		this->_buttonTexture = newTexture;
		this->_buttonBody.setTexture(_buttonTexture);
	}

	void Button_SFML::Set_ButtonOulineColor(sf::Color newOutlineColor)
	{
		this->_buttonBody.setOutlineColor(newOutlineColor);
	}
	
	void Button_SFML::Set_ButtonTextOulineColor(sf::Color newOutlineColor)
	{
		this->_buttonText.setOutlineColor(newOutlineColor);
	}

	void Button_SFML::Set_ButtonStateColors(sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor)
	{
		this->_buttonColor_Idle = idleColor;
		this->_buttonColor_Hover = hoverColor;
		this->_buttonColor_Pressed = pressedColor;
	}

	void Button_SFML::Set_ButtonColor_Idle(sf::Color idleColor) { this->_buttonColor_Idle = idleColor; }
	void Button_SFML::Set_ButtonColor_Hover(sf::Color hoverColor) { this->_buttonColor_Hover = hoverColor; }
	void Button_SFML::Set_ButtonColor_Pressed(sf::Color pressedColor) { this->_buttonColor_Pressed = pressedColor; }

	const bool Button_SFML::IsHover()const { return this->_buttonState == BUTTON_HOVER; }
	const bool Button_SFML::IsPressed()const { return this->_buttonState == BUTTON_PRESSED; }
	const std::string& Button_SFML::Get_ButtonText() const { return this->_buttonTextString; }

	void Button_SFML::UpdateButtonOrigin()
	{
		this->_buttonBody.setOrigin(this->_buttonBody.getSize() / 2.0f);
		this->_buttonText.setOrigin(this->_buttonBody.getOrigin());
	}
}
