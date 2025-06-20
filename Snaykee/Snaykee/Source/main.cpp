#include <iostream>
//#include <SFML/Graphics.hpp>
#include "Game.h"

// TODO: Testing Button
#include "Button_SFML.h"
#include "GameStateManager_SFML.h"
#include "Defines_SFML.h"
#include "SplashScreen_State.h"

#pragma region Forward Declarations (Time/Clock)
void Handle_FPS(double deltaTime);
void Handle_GameClock(Game& game);
#pragma endregion


int main()
{
	// Seed time
	//srand(time(0));
	srand(static_cast<unsigned>(time(0)));

	GameContext LeGameContext;

	// Initialize game window
	LeGameContext.window = new sf::RenderWindow(sf::VideoMode({ (unsigned int)(Game::WINDOW_WIDTH), (unsigned int)(Game::WINDOW_HEIGHT) }), "Snaykee");
	LeGameContext.window->setFramerateLimit(60.0f);

	LeGameContext.GameStateManager.AddState(std::unique_ptr<GameState_SFML>(new SplashScreen_State(LeGameContext)));
	LeGameContext.GameStateManager.HandleStateChange();

	Game LeGame("Snaykee", LeGameContext);

	/*
	// Create asset manager
	//AssetManager_SFML AssetManager;

	// Create game state manager
	//GameStateManager_SFML GameStateManager;

	// Create game
	Game LeGame("Snaykee", LeGameResources.AssetManager);

	// Create game window
	//sf::RenderWindow window(sf::VideoMode({ 200, 200 }), snakeGame.Get_GameTitle());
	//sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ (unsigned int)(LeGame.WINDOW_WIDTH), (unsigned int)(LeGame.WINDOW_HEIGHT) }), LeGame.Get_GameTitle());
	//window->setFramerateLimit(60);

	// TODO: Testing Button
	//Button_SFML playButton({ static_cast<float>(LeGame.WINDOW_WIDTH / 2.0f),  static_cast<float>(LeGame.WINDOW_HEIGHT / 2.0f) });
	//playButton.Set_ButtonText("  PLAY  ");
	//playButton.MutiplyButtonSize(4.0f);
	//playButton.Set_ButtonColor_Hover(sf::Color(170.0f, 170.0f, 170.0f));
	//playButton.Set_ButtonPressedFunction([]() {std::cout << "Button Clicked!!" << "\n"; });
	*/

	sf::RenderWindow* window = LeGameContext.window;
	while (window->isOpen())
	{
		// Handle FPS
		Handle_GameClock(LeGame);
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

		// Update
		if (LeGameContext.CurrentGameState == GAME)
			LeGame.Tick(static_cast<float>(LeGame.GAME_DELTA_TIME));
		else
		{
			if (LeGameContext.GameStateManager.Get_CurrentActiveState() != nullptr)
				LeGameContext.GameStateManager.Get_CurrentActiveState()->Update(static_cast<float>(LeGame.GAME_DELTA_TIME));
		}

		window->clear(sf::Color::Black);

		// Drawing
		if (LeGameContext.CurrentGameState == GAME)
			LeGame.Draw(*window);
		else
		{
			if (LeGameContext.GameStateManager.Get_CurrentActiveState() != nullptr)
				LeGameContext.GameStateManager.Get_CurrentActiveState()->Draw(*window);
		}

		window->display();

		/*
		// Update
		//GameStateManager.Get_CurrentActiveState()->HandleInput();
		//GameStateManager.Get_CurrentActiveState()->Update(static_cast<float>(LeGame.GAME_DELTA_TIME));
		LeGame.Tick(static_cast<float>(LeGame.GAME_DELTA_TIME));
		// TODO: Testing Button
		//playButton.Update(mousePosView);
		//LeGameResources.GameStateManager.HandleStateChange();
		LeGameResources.GameStateManager.Get_CurrentActiveState()->Update(static_cast<float>(LeGame.GAME_DELTA_TIME));

		//window->clear(sf::Color(106, 146, 166));
		window->clear(sf::Color::Black);

		// Drawing
		LeGame.Draw(*window);
		LeGameResources.GameStateManager.Get_CurrentActiveState()->Draw(*window);
		//GameStateManager.Get_CurrentActiveState()->Draw(*window);
		// TODO: Testing Button
		//playButton.Draw(*window);

		window->display();
		*/
	}

	delete window;
	return 0;
}

/// <summary>
/// Perform game clock/time calculations.
/// </summary>
void Handle_GameClock(Game& game)
{
	double ending = game.GAME_CLOCK.getElapsedTime().asSeconds();
	game.GAME_DELTA_TIME = ending - game.GAME_STARTING_TIME;
	game.GAME_STARTING_TIME = ending;
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



// TODO: Maybe use object pooling for asteroids. Creacte a vector of 200-300 asteroids and just keep using those, instead of creating and deleting them constantly.

// TODO: Implement Save/load sytem.
	// Save player score.
	// Save player ship.

// TODO: Add pregame menu screen.
	// Menu screen should have play button.
	// High-score.
	// Ship selection (3 ships). Use button class. May need to create a new one (that has image instead of text).

// TODO: Add space background.
// TODO: Add asteroid texture(s).
// TODO: Make obstacles (asteroids) spin.
// TODO: Add background objects (planets, shiprecks, etc.) that slowly move down giving illusion of player flying by them.

// TODO: Maybe have event for resetting player. Event will be sent from Game and player will listen.
// TODO: Create function that determines values based (relative-to) on window or screen) Use this function when setting position and size of objects.
// TODO: Maybe change eneryscor UI ouline color based on how much energy. Red (0-24), Orange(25-49), Yellow(50-74), Green(75-100)
// TODO: Maybe move game window dimensions 'WINDOW_WIDTH' and "WINDOW_HEIGHT' into GameContext struct. Make const/read-only.


// DONE: Game over functionality.
// DONE: Make player energy deplete by 1 every second.
// DONE: Add countdown timer to C++ Utils folder
// DONE: Link scoring to star energy.
// DONE: Create star spawning functionality. Maybe also create a star array.
// DONE: Create button class.
	// Add function pointer to button class for when button is pressed.
// DONE: Add text on screen for player score.
// DONE: Add namespaces to SFMLCore files (.h and .cpp).
// DONE: Create resources manager class.
// DONE: Add spacehip texture(s).