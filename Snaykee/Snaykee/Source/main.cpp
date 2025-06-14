#include <iostream>
//#include <SFML/Graphics.hpp>
#include "Game.h"

// TODO: Testing Button
#include "Button_SFML.h"

#pragma region Forward Declarations (Time/Clock)
void Handle_FPS(double deltaTime);
void Handle_GameClock();
#pragma endregion

Game LeGame("Snaykee");

int main()
{
	//srand(time(0));
	srand(static_cast<unsigned>(time(0)));

	//sf::RenderWindow window(sf::VideoMode({ 200, 200 }), snakeGame.Get_GameTitle());
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ (unsigned int)(LeGame.WINDOW_WIDTH), (unsigned int)(LeGame.WINDOW_HEIGHT) }), LeGame.Get_GameTitle());
	window->setFramerateLimit(60);

	// TODO: Testing Button
	//Button_SFML playButton({ static_cast<float>(LeGame.WINDOW_WIDTH / 2.0f),  static_cast<float>(LeGame.WINDOW_HEIGHT / 2.0f) });
	//playButton.Set_ButtonText("  PLAY  ");
	//playButton.MutiplyButtonSize(4.0f);
	//playButton.Set_ButtonColor_Hover(sf::Color(170.0f, 170.0f, 170.0f));
	//playButton.Set_ButtonPressedFunction([]() {std::cout << "Button Clicked!!" << "\n"; });

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

		// Keep track of mouse position (relative to window).
		sf::Vector2f mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

		LeGame.Tick(static_cast<float>(LeGame.GAME_DELTA_TIME));

		// TODO: Testing Button
		//playButton.Update(mousePosView);

		//window->clear(sf::Color(106, 146, 166));
		window->clear(sf::Color::Black);

		// Drawing
		LeGame.Draw(*window);

		// TODO: Testing Button
		//playButton.Draw(*window);

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


// TODO: Add text on screen for player score.
// TODO: Create resources manager class.

// TODO: Implement Save/load sytem.
	// Save player score.
	// Save player ship.

// TODO: Add pregame menu screen.
	// Menu screen should have play button.
	// High-score.
	// Ship selection (3 ships).

// TODO: Add space background.
// TODO: Add spacehip texture.
// TODO: Add asteroid texture(s).
// TODO: Make obstacles (asteroids) spin.
// TODO: Add background objects (planets, shiprecks, etc.) that slowly move down giving illusion of player flying by them.

// TODO: Maybe have event for resetting player. Event will be sent from Game and player will listen.



// DONE: Game over functionality.
// DONE: Make player energy deplete by 1 every second.
// DONE: Add countdown timer to C++ Utils folder
// DONE: Link scoring to star energy.
// DONE: Create star spawning functionality. Maybe also create a star array.
// DONE: Create button class.
	// Add function pointer to button class for when button is pressed.