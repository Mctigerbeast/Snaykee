#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

unsigned int WindowWidth = 1200;
unsigned int WindowHeight = 1200;

#pragma region Forward Declarations (Time/Clock)
double GAME_STARTING_TIME = 0.0001;
sf::Clock GAME_CLOCK;
double GAME_DELTA_TIME;

void Handle_FPS(double deltaTime);
void Handle_GameClock();
#pragma endregion

int main()
{
	srand(time(0));

	Game LeGame("Snaykee");

	//sf::RenderWindow window(sf::VideoMode({ 200, 200 }), snakeGame.Get_GameTitle());
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ (unsigned int)(WindowWidth), (unsigned int)(WindowHeight) }), LeGame.Get_GameTitle());
	window->setFramerateLimit(60);

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
	double ending = GAME_CLOCK.getElapsedTime().asSeconds();
	GAME_DELTA_TIME = ending - GAME_STARTING_TIME;
	GAME_STARTING_TIME = ending;
}

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