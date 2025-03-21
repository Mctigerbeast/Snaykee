#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

#pragma region Forward Declarations (Time/Clock)
void Handle_FPS(double deltaTime);
void Handle_GameClock();
#pragma endregion

Game LeGame("Snaykee");

int main()
{
	srand(time(0));

	//sf::RenderWindow window(sf::VideoMode({ 200, 200 }), snakeGame.Get_GameTitle());
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ (unsigned int)(LeGame.WINDOW_WIDTH), (unsigned int)(LeGame.WINDOW_HEIGHT) }), LeGame.Get_GameTitle());
	window->setFramerateLimit(60);

	while (window->isOpen())
	{
		// Handle FPS
		Handle_GameClock();
		Handle_FPS(LeGame.GAME_DELTA_TIME);
		std::string fps = std::to_string(static_cast<int>(1 / LeGame.GAME_DELTA_TIME));
		window->setTitle(LeGame.Get_GameTitle() + "     FPS: " + fps);

		while (const std::optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window->close();
		}

		LeGame.Tick(static_cast<float>(LeGame.GAME_DELTA_TIME));

		window->clear(sf::Color(106, 146, 166));

		// Drawing
		LeGame.Draw(*window);
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
	double ending = LeGame.GAME_CLOCK.getElapsedTime().asSeconds();
	LeGame.GAME_DELTA_TIME = ending - LeGame.GAME_STARTING_TIME;
	LeGame.GAME_STARTING_TIME = ending;
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
#pragma endregion