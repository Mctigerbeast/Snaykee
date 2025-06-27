#include "Game.h"
#include "SplashScreen_State.h"
#include "MainMenu_State.h"

#pragma region Forward Declarations (Time/Clock)
void Handle_FPS(double deltaTime);
void Handle_GameClock(Game& game);
#pragma endregion


int main()
{
	// Seed time
	//srand(time(0));
	srand(static_cast<unsigned>(time(0)));

	// Screen/window dimensions
	//std::cout << "Screen Dimensions: " << sf::VideoMode::getDesktopMode().size.x << " x " << sf::VideoMode::getDesktopMode().size.y << "\n";
	int windowX = sf::VideoMode::getDesktopMode().size.y * 0.80f;
	int windowY = sf::VideoMode::getDesktopMode().size.y * 0.80f;

	// Create game context
	GameContext LeGameContext("SNAYKEE", windowX, windowY);
	LeGameContext.window->setFramerateLimit(60.0f);

	LeGameContext.GameStateManager.AddState(std::unique_ptr<GameState_SFML>(new SplashScreen_State(LeGameContext)));
	LeGameContext.GameStateManager.HandleStateChange();

	// Create game
	Game LeGame(LeGameContext);

	sf::RenderWindow* window = LeGameContext.window;
	while (window->isOpen())
	{
		// Handle FPS
		Handle_GameClock(LeGame);
		Handle_FPS(LeGame.GAME_DELTA_TIME);
		std::string fps = std::to_string(static_cast<int>(1 / LeGame.GAME_DELTA_TIME));
		window->setTitle(LeGameContext.GAME_TITLE + "     FPS: " + fps);

		while (const std::optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window->close();
		}

		// Update
		if (LeGameContext.GameStateManager.Get_CurrentActiveState() != nullptr)
			LeGameContext.GameStateManager.Get_CurrentActiveState()->Update(static_cast<float>(LeGame.GAME_DELTA_TIME));

		window->clear(sf::Color::Black);

		// Drawing
		if (LeGameContext.GameStateManager.Get_CurrentActiveState() != nullptr)
			LeGameContext.GameStateManager.Get_CurrentActiveState()->Draw(*window);

		window->display();
	}

	delete window;
	return 0;
}

#pragma region HELPERS
/// <summary>
/// Perform game clock/time calculations.
/// </summary>
void Handle_GameClock(Game& game)
{
	double ending = game.GAME_CLOCK.getElapsedTime().asSeconds();
	game.GAME_DELTA_TIME = ending - game.GAME_STARTING_TIME;
	game.GAME_STARTING_TIME = ending;
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
#pragma endregion



// TODO: Maybe use object pooling for asteroids. Creacte a vector of 200-300 asteroids and just keep using those, instead of creating and deleting them constantly.

// TODO: Implement Save/load sytem.
	// Save player score.
	// Save player ship.
	// Load player data during splashscreen or on main menu.

// TODO: Add space background.
// TODO: Add asteroid texture(s).
// TODO: Make obstacles (asteroids) spin.
// TODO: Add background objects (planets, shiprecks, etc.) that slowly move down giving illusion of player flying by them.

// TODO: Maybe have callback function for resetting player. Callback function will be called from Game and player will listen.
// TODO: Create function that determines values based (relative-to) on window or screen) Use this function when setting position and size of objects.
// TODO: Make asteroid travel faster as time goes by.

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
// DONE: Maybe change energyScore UI ouline color based on how much energy. Red (0-24), Orange(25-49), Yellow(50-74), Green(75-100)

// DONE: Update button class. 
	// Create function for setting/changing button's text font.
	// Add default button font to resources.

// DONE: Maybe move game window dimensions 'WINDOW_WIDTH' and "WINDOW_HEIGHT' into GameContext struct. Make const/read-only.

// DONE: Add pregame menu screen.
	// Menu screen should have play button.
	// High-score.
	// Ship selection (4 ships). Use button class. May need to create a new one (that has image instead of text).
	// Menu background