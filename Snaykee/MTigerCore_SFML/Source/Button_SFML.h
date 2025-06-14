#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

enum BUTTON_STATE
{
	BUTTON_IDLE = 0,
	BUTTON_HOVER = 1,
	BUTTON_PRESSED = 2
};

class Button_SFML
{
public:
	Button_SFML(sf::Vector2f buttonPosition, sf::Vector2f buttonSize = { 100.0f, 35.0f }, sf::Texture* btnTexture = nullptr);
	~Button_SFML();

	void Update(sf::Vector2f mousePositionInWindow);
	void Draw(sf::RenderWindow& window);
	void MutiplyButtonSize(float multiplier);

	// Setters (mutators)
	void Set_ButtonText(const std::string& newText);
	void Set_ButtonPressedFunction(void(*newButnPressFunc)());

	void Set_ButtonColors(sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor);
	void Set_ButtonColor_Idle(sf::Color idleColor);
	void Set_ButtonColor_Hover(sf::Color hoverColor);
	void Set_ButtonColor_Pressed(sf::Color pressedColor);
	void Set_ButtonTexture(sf::Texture* newTexture);

	// Getters (accessors)
	const bool IsHover() const;
	const bool IsPressed() const;
	const std::string& Get_ButtonText() const;

private:
	sf::RectangleShape _buttonBody;

	sf::Color _buttonColor_Idle = sf::Color::White;
	sf::Color _buttonColor_Hover = sf::Color::Blue;
	sf::Color _buttonColor_Pressed = sf::Color::Green;
	sf::Texture* _buttonTexture;

	uint32_t _buttonState = BUTTON_IDLE; // 0 = idle, 1 = hover, 2 = pressed

	sf::Font _buttonTextFont;
	sf::Text _buttonText;
	std::string _buttonTextString = "";

	void(*ButtonPressedFunction)() = nullptr;
};