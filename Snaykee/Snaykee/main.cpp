#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Border.h"
#include "MTigerCore_Math/MR_Math.h"

unsigned int WINDOW_WIDTH = 1200;
unsigned int WINDOW_HEIGHT = 1200;

#pragma region Forward Declarations (Time/Clock)
double GAME_STARTING_TIME = 0.0001;
sf::Clock GAME_CLOCK;
double GAME_DELTA_TIME;

void Handle_FPS(double deltaTime);
void Handle_GameClock();
sf::Vector2f Get_CenterOfScreen();
#pragma endregion

int main()
{
	srand(time(0));

	Game LeGame("Snaykee");

	//sf::RenderWindow window(sf::VideoMode({ 200, 200 }), snakeGame.Get_GameTitle());
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ (unsigned int)(WINDOW_WIDTH), (unsigned int)(WINDOW_HEIGHT) }), LeGame.Get_GameTitle());
	window->setFramerateLimit(60);

#pragma region Stage Borders
	Border leftBorder({ 20.0f, static_cast<float>(WINDOW_HEIGHT) }, { 20.0f, Get_CenterOfScreen().y }, nullptr, sf::Color::Black);
	Border rightBorder({ 20.0f, static_cast<float>(WINDOW_HEIGHT) }, { MR_Math::Convert_To_Float(WINDOW_WIDTH) - 20.f, Get_CenterOfScreen().y }, nullptr, sf::Color::Black);
	Border topBorder({ static_cast<float>(WINDOW_WIDTH), 20.0f }, { Get_CenterOfScreen().x, 20.0f }, nullptr, sf::Color::Black);
	Border bottomBorder({ static_cast<float>(WINDOW_WIDTH), 20.0f }, { Get_CenterOfScreen().x, MR_Math::Convert_To_Float(WINDOW_HEIGHT) - 20.0f }, nullptr, sf::Color::Black);
#pragma endregion

	while (window->isOpen())
	{
		// Handle FPS
		Handle_GameClock();
		Handle_FPS(GAME_DELTA_TIME);
		std::string fps = std::to_string(static_cast<int>(1 / GAME_DELTA_TIME));
		window->setTitle(LeGame.Get_GameTitle() + "     FPS: " + fps);

		while (const std::optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window->close();
		}

		LeGame.Tick(static_cast<float>(GAME_DELTA_TIME));

		window->clear(sf::Color(106, 146, 166));

		// Calculations
		Collider_SFML playerCollider = LeGame.Get_Player_Ref().Get_Gollider();
		leftBorder.Get_Collider().CheckCollision(playerCollider, 1.0f);
		rightBorder.Get_Collider().CheckCollision(playerCollider, 1.0f);
		topBorder.Get_Collider().CheckCollision(playerCollider, 1.0f);
		bottomBorder.Get_Collider().CheckCollision(playerCollider, 1.0f);

		// Drawing
		LeGame.Draw(*window);
		leftBorder.Draw(*window);
		rightBorder.Draw(*window);
		topBorder.Draw(*window);
		bottomBorder.Draw(*window);

		window->display();
	}

	delete window;
	return 0;
}

/// <summary>
/// Perform game clock/time calculations.
/// </summary>
void Handle_GameClock()
{
	double ending = GAME_CLOCK.getElapsedTime().asSeconds();
	GAME_DELTA_TIME = ending - GAME_STARTING_TIME;
	GAME_STARTING_TIME = ending;
}

#pragma region HELPERS
/// <summary>
/// Performs FPS calculations.
/// </summary>
/// <param name="deltaTime"></param>
void Handle_FPS(double deltaTime)
{
	// Set minimum FPS
	if (deltaTime > 1.0f / 20.0f)
		deltaTime = 1.0f / 20.0f;
}

/// <summary>
/// Returns center/middle of screen.
/// </summary>
/// <returns></returns>
sf::Vector2f Get_CenterOfScreen()
{
	return sf::Vector2f{ static_cast<float>(WINDOW_WIDTH / 2), static_cast<float>(WINDOW_HEIGHT / 2) };
}
#pragma endregion