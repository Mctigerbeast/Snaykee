#include "SplashScreen_State.h"

#pragma region Forward Declarations
// (Time/Clock)
double GAME_STARTING_TIME = 0.0001;
sf::Clock GAME_CLOCK;
double GAME_DELTA_TIME;
void Handle_FPS(double deltaTime);
void Handle_GameClock();

// Other
void LoadGameAssets(MR_SFML::AssetManager_SFML& assetManager);
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
	LeGameContext.SaveSystem.LoadPlayerData();
	LeGameContext.window->setFramerateLimit(120.0f); // TODO: Maybe update the way that frame limit is being set.

	// Load all game assets
	LoadGameAssets(LeGameContext.AssetManager);

	// Add the first game state
	LeGameContext.GameStateManager.AddState(std::unique_ptr<MR_SFML::GameState_SFML>(new Snaykee::SplashScreen_State(LeGameContext)));
	sf::RenderWindow* window = LeGameContext.window;
	while (window->isOpen())
	{
		// Handle FPS
		Handle_GameClock();
		Handle_FPS(GAME_DELTA_TIME);
		std::string fps = std::to_string(static_cast<int>(1 / GAME_DELTA_TIME));
		window->setTitle(LeGameContext.GAME_TITLE + "     FPS: " + fps);

		while (const std::optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window->close();
		}

		LeGameContext.GameStateManager.HandleStateChange();

		// Update
		if (LeGameContext.GameStateManager.Get_CurrentActiveState() != nullptr)
			LeGameContext.GameStateManager.Get_CurrentActiveState()->Update(static_cast<float>(GAME_DELTA_TIME));

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

/// <summary>
/// Loads ALL game assets.
/// </summary>
void LoadGameAssets(MR_SFML::AssetManager_SFML& assetManager)
{
	// Fonts
	assetManager.LoadFont("mainFont", "Resources/font_playful_time_star.ttf");
	assetManager.LoadFont("defaultFont", "Resources/font_cera_pro_modern_medium.ttf");

	// Textures
	assetManager.LoadTexture("splashScreenBanner", "Resources/spr_splashscreen_logo_banner.jpg");
	assetManager.LoadTexture("purpleBackground", "Resources/bg_space_purple.jpg");
	assetManager.LoadTexture("confetti", "Resources/spr_confetti_3.png");

	assetManager.LoadTexture("greenShip", "Resources/spr_spaceship_green.png");
	assetManager.LoadTexture("yellowShip", "Resources/spr_spaceship_yellow.png");
	assetManager.LoadTexture("whiteShip", "Resources/spr_spaceship_white.png");
	assetManager.LoadTexture("darkShip", "Resources/spr_spaceship_dark.png");

	assetManager.LoadTexture("asteroid_1_Texture", "Resources/spr_asteroid_1.png");
	assetManager.LoadTexture("asteroid_2_Texture", "Resources/spr_asteroid_2.png");
	assetManager.LoadTexture("asteroid_3_Texture", "Resources/spr_asteroid_3.png");
	assetManager.LoadTexture("asteroid_4_Texture", "Resources/spr_asteroid_4.png");

	assetManager.LoadTexture("starEnergy_1_Texture", "Resources/spr_star_energy_1.png");
	assetManager.LoadTexture("starEnergy_2_Texture", "Resources/spr_star_energy_2.png");
	assetManager.LoadTexture("starEnergy_3_Texture", "Resources/spr_star_energy_3.png");

	assetManager.LoadTexture("shipProjectile", "Resources/spr_circle_plain.png");
	assetManager.LoadTexture("explosion", "Resources/spr_explosion.png");

	// Sounds
	assetManager.LoadSoundBuffer("buttonClick", "Resources/sfx_button_click.wav");
	assetManager.LoadSoundBuffer("starCollect", "Resources/sfx_collect_star_energy.wav");
	assetManager.LoadSoundBuffer("lowFeul", "Resources/sfx_low_fuel.wav");
	assetManager.LoadSoundBuffer("obstacleHit", "Resources/sfx_collision.flac");
	assetManager.LoadSoundBuffer("playerDeathGameOver", "Resources/sfx_game_over.wav");
	assetManager.LoadSoundBuffer("audienceCheer", "Resources/sfx_audience_cheering.wav");
	assetManager.LoadSoundBuffer("partyHorn", "Resources/sfx_party_horn.wav");
	assetManager.LoadSoundBuffer("laserShot", "Resources/sfx_laser_shot.wav");
	assetManager.LoadSoundBuffer("explosion", "Resources/sfx_small_explosion.wav");
}
#pragma endregion




// TODO: Add space background.
// TODO: Add background objects (planets, shiprecks, etc.) that slowly move down giving illusion of player flying by them.
// TODO: Maybe have callback function for resetting player. Callback function will be called from Game and player will listen.

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

// DONE: Create 'Pause Menu' State.
// DONE: Create 'Game Over' State.
// DONE: Add mission debrief (story) to main menu screen towards the bottom.

// DONE: Implement Save/load sytem.
	// Save player score.
	// Save player ship.
	// Load player data during splashscreen or on main menu.

// DONE: Maybe use object pooling for asteroids. Creacte a vector of 200-300 asteroids and just keep using those, instead of creating and deleting them constantly.
// DONE: Add asteroid texture(s).
// DONE: Create audio manager class for playing audio (sfx and music).
// DONE: Add a HELD state to the button class for when button is pressed and held down on.

// DONE: Add game audio
	// Ship hitting obstacles, Player (ship) death/game over sound.
	// Ship collect star energy, Ship low on energy (energy < 20).
	// Main menu music, Gameplay music, Button clicked sound.

// DONE: Add game namespace.
// DONE: Change ship color to red (briefly) after hitting obstacle.
// DONE: Make obstacles (asteroids) spin.
// DONE: Create credits state (page).
// DONE: [MAYBE] Add projectiles. Cost 2 energy, destroys projectile that it collides with. 0.5 - 1 second cooldown.
// DONE: Create function that determines values based-on (relative-to) window or screen. Use this function when setting position and size of objects.
// DONE: Create controls state (page/screen).