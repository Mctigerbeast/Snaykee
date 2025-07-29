#pragma once
#include <iostream>
#include <functional>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "AssetManager_SFML.h"

namespace MR_SFML
{
	enum BUTTON_STATE
	{
		BUTTON_IDLE = 0,
		BUTTON_HOVER = 1,
		BUTTON_PRESSED = 2,
		BUTTON_HELD = 3
	};

	class Button_SFML
	{
	public:
		Button_SFML(AssetManager_SFML& assetManager);
		Button_SFML(AssetManager_SFML& assetManager, sf::Vector2f buttonPosition, sf::Vector2f buttonSize = { 100.0f, 35.0f }, sf::Texture* btnTexture = nullptr);
		~Button_SFML();

		/// <summary>
		/// Update the buton.
		/// </summary>
		/// <param name="mousePositionInWindow">Position of the mouse in the game window.</param>
		void Update(sf::Vector2f mousePositionInWindow);

		/// <summary>
		/// Perform Draw functionality/logic.
		/// </summary>
		/// <param name="window"></param>
		void Draw(sf::RenderWindow& window);

		/// <summary>
		/// Multiplies the button's size by a passed in value.
		/// </summary>
		/// <param name="multiplier"></param>
		void MutiplyButtonSize(float multiplier);

		/// <summary>
		/// Changes the button's 'ButtonPressed' function (callback).
		/// </summary>
		/// <param name="newButnPressFunc"></param>
		void Set_ButtonPressedFunction(std::function<void()> newButnPressFunc);

		/// <summary>
		/// Changes the button's text.
		/// </summary>
		/// <param name="newText">The button's new text.</param>
		void Set_ButtonText(const std::string& newText);

		/// <summary>
		/// [Overloaded] Changes the button's text AND text's character size.
		/// </summary>
		/// <param name="newText">The button's new text.</param>
		/// <param name="newCharSize">The button's new text.</param>
		void Set_ButtonText(const std::string& newText, float newCharSize);

		/// <summary>
		/// Changes the button's text font
		/// </summary>
		/// <param name="newFont">The button's new text font.</param>
		void Set_ButtonTextFont(sf::Font& newFont);

		/// <summary>
		/// Changes the button's position.
		/// </summary>
		/// <param name="posX">X position of button.</param>
		/// <param name="posY">Y position of button.</param>
		void Set_ButtonPosition(float posX, float posY);

		/// <summary>
		/// Changes the button's size.
		/// </summary>
		/// <param name="width">Width of the button.</param>
		/// <param name="height">Height of the button.</param>
		void Set_ButtonSize(float width, float height);

		/// <summary>
		/// Changes the button's outline thickness. By default, the button's outline thickness is 0.
		/// </summary>
		/// <param name="newThicknessVal"></param>
		void Set_ButtonOulineThickness(float newThicknessVal);

		/// <summary>
		/// Changes the button's text outline thickness. By default, the button's text outline thickness is 0.
		/// </summary>
		/// <param name="newThicknessVal"></param>
		void Set_ButtonTextOulineThickness(float newThicknessVal);

		/// <summary>
		/// Set/changes the button's texture.
		/// </summary>
		/// <param name="newTexture">The button's new texture.</param>
		void Set_ButtonTexture(sf::Texture* newTexture);

		/// <summary>
		/// Set the outline color of the button. By default, the button's outline color is opaque white.
		/// </summary>
		/// <param name="newOutlineColor"></param>
		void Set_ButtonOulineColor(sf::Color newOutlineColor);

		/// <summary>
		/// Set the outline color of the button's text. By default, the button's text outline color is opaque white.
		/// </summary>
		/// <param name="newOutlineColor"></param>
		void Set_ButtonTextOulineColor(sf::Color newOutlineColor);

		/// <summary>
		/// Changes the button's colors.
		/// </summary>
		/// <param name="idleColor">Color for when button is idle.</param>
		/// <param name="hoverColor">Color for when button is being hovered on by the mouse.</param>
		/// <param name="pressedColor">Color for when button is pressed (clicked).</param>
		void Set_ButtonStateColors(sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor);

		/// <summary>
		/// Changes the button's 'idle' color.
		/// </summary>
		/// <param name="idleColor">Color for when button is idle.</param>
		void Set_ButtonColor_Idle(sf::Color idleColor);

		/// <summary>
		/// Changes the button's 'hover' color.
		/// </summary>
		/// <param name="hoverColor">Color for when button is being hovered on by the mouse.</param>
		void Set_ButtonColor_Hover(sf::Color hoverColor);

		/// <summary>
		/// Changes the button's 'pressed' color.
		/// </summary>
		/// <param name="pressedColor">Color for when button is pressed (clicked).</param>
		void Set_ButtonColor_Pressed(sf::Color pressedColor);

		/// <summary>
		/// Determines if button is being hovered on.
		/// </summary>
		/// <returns>True, if button is being hovered.</returns>
		const bool IsHover() const;

		/// <summary>
		/// Determines if button is pressed (clicked).
		/// </summary>
		/// <returns>True, if button is pressed (clicked).</returns>
		const bool IsPressed() const;

		/// <summary>
		/// Determines if button is pressed (clicked) AND held down.
		/// </summary>
		/// <returns>True, if button is pressed (clicked) AND held down.</returns>
		const bool IsHeld() const;

		/// <summary>
		/// </summary>
		/// <returns>The button's text.</returns>
		const std::string& Get_ButtonText() const;

	private:
		AssetManager_SFML& _assetManager;
		sf::RectangleShape _buttonBody;

		sf::Color _buttonColor_Idle = sf::Color::White;
		sf::Color _buttonColor_Hover = sf::Color::Blue;
		sf::Color _buttonColor_Pressed = sf::Color::Green;
		sf::Texture* _buttonTexture = nullptr;

		uint32_t _buttonState = BUTTON_IDLE; // 0 = idle, 1 = hover, 2 = pressed, 3 = held

		sf::Text _buttonText;
		sf::Font* _buttonTextFont;
		std::string _buttonTextString = "";

		std::function<void()> ButtonPressedFunction;
		bool isButtonPressed = false;

	private:
		/// <summary>
		/// Updates the button's origin, to be the center of the button.
		/// </summary>
		void UpdateButtonOrigin();
	};
}
