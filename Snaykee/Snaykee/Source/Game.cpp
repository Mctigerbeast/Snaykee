#include "Game.h"

const std::string& Game::Get_GameTitle() const { return this->_gameTitle; }

sf::Vector2f Game::Get_CenterOfScreen()
{
	return sf::Vector2f{ static_cast<float>(WINDOW_WIDTH / 2), static_cast<float>(WINDOW_HEIGHT / 2) };
}

Game::Game(std::string gameTitle, GameContext& gameContext)
	: _gameTitle(gameTitle), _gameContext(gameContext), _scoreText_UI(*_scoreTextFont_UI), _energyText_UI(*_energyTextFont_UI)
{
	// Load and set resources
	this->_gameContext.AssetManager.LoadTexture("greenShip", "Resources/spr_spaceship_green.png");
	this->_gameContext.AssetManager.LoadTexture("yellowShip", "Resources/spr_spaceship_yellow.png");
	this->_gameContext.AssetManager.LoadTexture("whiteShip", "Resources/spr_spaceship_white.png");
	this->_gameContext.AssetManager.LoadTexture("darkShip", "Resources/spr_spaceship_dark.png");
	this->_gameContext.AssetManager.LoadTexture("purpleBackground", "Resources/bg_space_purple.jpg");
	this->_gameContext.AssetManager.LoadTexture("asteroid_1_Texture", "Resources/Asteroid1.png");

	this->_playerTexture_1 = &this->_gameContext.AssetManager.Get_Texture("greenShip");
	this->_playerTexture_2 = &this->_gameContext.AssetManager.Get_Texture("yellowShip");
	this->_playerTexture_3 = &this->_gameContext.AssetManager.Get_Texture("whiteShip");
	this->_playerTexture_4 = &this->_gameContext.AssetManager.Get_Texture("darkShip");
	this->_backgroundTexture = &this->_gameContext.AssetManager.Get_Texture("purpleBackground");
	this->_asteroid_1_Texture = &this->_gameContext.AssetManager.Get_Texture("asteroid_1_Texture");

	this->_gameContext.AssetManager.LoadFont("mainFont", "Resources/font_playful_time_star.ttf");
	this->_scoreTextFont_UI = &this->_gameContext.AssetManager.Get_Font("mainFont");
	this->_energyTextFont_UI = &this->_gameContext.AssetManager.Get_Font("mainFont");

	// Create game's screen (window) borders
	this->leftBorder = new Border({ 20.0f, static_cast<float>(WINDOW_HEIGHT) }, { 10.0f, Get_CenterOfScreen().y }, nullptr, sf::Color::Black);
	this->rightBorder = new Border({ 20.0f, static_cast<float>(WINDOW_HEIGHT) }, { MR_Math::Convert_To_Float(WINDOW_WIDTH) - 10.f, Get_CenterOfScreen().y }, nullptr, sf::Color::Black);
	this->topBorder = new Border({ static_cast<float>(WINDOW_WIDTH), 20.0f }, { Get_CenterOfScreen().x, 10.0f }, nullptr, sf::Color::Black);
	this->bottomBorder = new Border({ static_cast<float>(WINDOW_WIDTH), 20.0f }, { Get_CenterOfScreen().x, MR_Math::Convert_To_Float(WINDOW_HEIGHT) - 10.0f }, nullptr, sf::Color::Black);

	// Player
	this->_player = Player_SpaceShip(this->_playerTexture_2, sf::Vector2u({ 1, 1 }), 0.1f, 500.0f);
	//this->_player.SetupAnimation(1, 2, 3, 0);
	this->_player.Set_PlayerSize({ 80.0f, 100.0f });
	this->_player.Set_PlayerPostition({ static_cast<float>(this->WINDOW_WIDTH / 2.0f),  static_cast<float>(this->WINDOW_HEIGHT / 2.0f) });

	// Other Visuals
	this->_background = sf::RectangleShape({ 1800.0f, static_cast<float>(this->WINDOW_HEIGHT) });
	this->_background.setTexture(this->_backgroundTexture);
	this->_background.setFillColor(sf::Color{ 255,255,255,100 });

	// UI (score text)
	this->_scoreText_UI = sf::Text(*this->_scoreTextFont_UI);
	this->_scoreText_UI.setPosition({ static_cast<float>(this->WINDOW_WIDTH) * 0.05f, static_cast<float>(this->WINDOW_HEIGHT) * 0.95f });
	this->_scoreText_UI.setOrigin(this->_scoreText_UI.getGlobalBounds().size / 2.0f);
	this->_scoreText_UI.setLetterSpacing(2.0f);
	this->_scoreText_UI.setFillColor(sf::Color::Black);
	this->_scoreText_UI.setOutlineThickness(2.0f);
	this->_scoreText_UI.setOutlineColor(sf::Color::White);
	this->_scoreText_UI.setCharacterSize(20.0f);

	this->_energyText_UI = sf::Text(*this->_energyTextFont_UI);
	this->_energyText_UI.setPosition({ static_cast<float>(this->WINDOW_WIDTH) * 0.825f, static_cast<float>(this->WINDOW_HEIGHT) * 0.95f });
	this->_energyText_UI.setOrigin(this->_energyText_UI.getGlobalBounds().size / 2.0f);
	this->_energyText_UI.setLetterSpacing(2.0f);
	this->_energyText_UI.setFillColor(sf::Color::Black);
	this->_energyText_UI.setOutlineThickness(2.0f);
	this->_energyText_UI.setOutlineColor(sf::Color::White);
	this->_energyText_UI.setCharacterSize(20.0f);
}

Game::~Game()
{
	delete leftBorder;
	delete rightBorder;
	delete topBorder;
	delete bottomBorder;
}

void Game::Tick(float fDeltaTime)
{
	if (this->_isGameOVer)
	{
		// TODO: Testing purposes only!!! Update to be linked to on screen button press (Game over menu).
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
			this->Execute_StartGame();

		return;
	}

	this->_deltaTime = fDeltaTime;

	this->_score += this->_deltaTime;

	// Calculations
	this->GenerateObstacles();
	this->CheckObstacleCollisions();
	this->GenerateStarEnergy();
	this->CheckStarEnergyCollisions();

	// Updating
	this->_player.Update(fDeltaTime);

	for (Obstacle& ob : this->_obstacles) // Update obstacles
		ob.Update(fDeltaTime);

	this->_scoreText_UI.setString("SCORE: " + std::to_string(this->_score));
	this->_energyText_UI.setString("ENERGY: " + std::to_string(this->_player.Get_Energy()));
}

void Game::Draw(sf::RenderWindow& window)
{
	// Draw background
	window.draw(this->_background);

	// Draw player
	this->_player.Draw(window);

	// Draw obstacles
	for (Obstacle& ob : this->_obstacles)
		ob.Draw(window);

	// Draw star energys
	for (StarEnergy& se : this->_starEnergies)
		se.Draw(window);

	// Draw Screen (window) borders
	leftBorder->Draw(window);
	rightBorder->Draw(window);
	topBorder->Draw(window);
	bottomBorder->Draw(window);

	// Draw UI (score text)
	window.draw(this->_scoreText_UI);
	window.draw(this->_energyText_UI);
}

void Game::GenerateObstacles()
{
	//int rn = MR_Math::RandomInt(100);
	int rn = MR_Math::RandomInt(200);

	if (rn > 10)
		return;

	// Used to spawn obstacles within a certain percentage of the window.
	// In this case, obstcles won't spawn within the outer 5% of the window.
	float percentage = this->WINDOW_WIDTH * 0.05f; // (5%)

	//float randSize = MR_Math::RandomFloatRange(5.0f, 10.0f);
	float randSize = MR_Math::RandomFloatRange(20.0f, 50.0f); // TODO: Testing value
	float randPosX = MR_Math::RandomFloatRange(percentage, (this->WINDOW_WIDTH - percentage));
	float randPosY = MR_Math::RandomFloat(percentage);
	float randSpeed = MR_Math::RandomFloat(1.0f);

	Obstacle ob({ randSize, randSize }, { randPosX, randPosY }, randSpeed, this->_asteroid_1_Texture);
	this->_obstacles.push_back(ob);
}

void Game::CheckObstacleCollisions()
{
	Collider_SFML playerCollider = this->_player.Get_Gollider();
	Collider_SFML bottomBorderCollider = this->bottomBorder->Get_Collider();

	for (int i = 0; i < this->_obstacles.size(); ++i)
	{
		// Collision(s) with player
		if (this->_obstacles[i].Get_Collider().CheckCollision(playerCollider, 1.0f))
		{
			this->_player.OnObstacleHit();
			this->_obstacles.erase(this->_obstacles.begin() + i); // TODO: May cause some issues

			if (!this->_player.IsAlive())
				this->Execute_GameOver();
		}

		// Collision(s) with border(s)
		if (this->_obstacles[i].Get_Collider().CheckCollision(bottomBorderCollider, 0.0f))
			this->_obstacles.erase(this->_obstacles.begin() + i); // TODO: May cause some issues
	}

	// Screen (window) borders
	this->leftBorder->Get_Collider().CheckCollision(playerCollider, 1.0f);
	this->rightBorder->Get_Collider().CheckCollision(playerCollider, 1.0f);
	this->topBorder->Get_Collider().CheckCollision(playerCollider, 1.0f);
	this->bottomBorder->Get_Collider().CheckCollision(playerCollider, 1.0f);
}

void Game::GenerateStarEnergy()
{
	if (this->_starEnergies.size() >= 3)
		return;

	int rn = MR_Math::RandomInt(1000);

	if (rn > 10)
		return;

	// Used to spawn star energy within a certain percentage of the window.
	// In this case, star energy won't spawn within the outer 10% of the window.
	float percentageX = this->WINDOW_WIDTH * 0.10f;
	float percentageY = this->WINDOW_HEIGHT * 0.10f;

	float randPosX = MR_Math::RandomFloatRange(percentageX, (this->WINDOW_WIDTH - percentageX));
	float randPosY = MR_Math::RandomFloatRange(percentageY, (this->WINDOW_HEIGHT - percentageY));

	StarEnergy se({ randPosX, randPosY });
	this->_starEnergies.push_back(se);
}

void Game::CheckStarEnergyCollisions()
{
	Collider_SFML playerCollider = this->_player.Get_Gollider();

	// Collision(s) with player
	for (int i = 0; i < this->_starEnergies.size(); ++i)
	{
		if (this->_starEnergies[i].Get_Collider().CheckCollision(playerCollider, 1.0f))
		{
			this->_score += 5;
			this->_player.AddEnergy(this->_starEnergies[i].Get_EnergyPower());
			this->_starEnergies.erase(this->_starEnergies.begin() + i);
		}
	}
}

void Game::Execute_GameOver()
{
	this->_isGameOVer = true;
	std::cout << "GAME OVER!!! [Score: " << this->_score << "]\n";

	// TODO: Save player's score

	// TODO: Show game over screen
}

void Game::Execute_StartGame()
{
	this->_score = 0; // Reset player score
	this->_player.Set_PlayerPostition({ static_cast<float>(this->WINDOW_WIDTH / 2.0f),  static_cast<float>(this->WINDOW_HEIGHT / 2.0f) }); // Reset player's position
	this->_player.ResetPlayer(); // Reset player's health, etc.

	// Clean and reset obstacles vector
	std::vector<Obstacle>().swap(this->_obstacles);

	// Clean and reset star energies vector
	std::vector<StarEnergy>().swap(this->_starEnergies);

	this->_isGameOVer = false;
}

