#include "Game.h"

Game::Game(std::string gameTitle)
	: _gameTitle(gameTitle)
{
	this->_playertexture = new sf::Texture;
	_playertexture->loadFromFile("Resources/SpriteSheet_Example.png");

	this->_player = Player_SpaceShip(_playertexture, sf::Vector2u({ 8, 4 }), 0.1f, 500.0f);
	this->_player.SetupAnimation(1, 2, 3, 0);

	// Create game's screen (window) borders
	this->leftBorder = new Border({ 20.0f, static_cast<float>(WINDOW_HEIGHT) }, { 20.0f, Get_CenterOfScreen().y }, nullptr, sf::Color::Black);
	this->rightBorder = new Border({ 20.0f, static_cast<float>(WINDOW_HEIGHT) }, { MR_Math::Convert_To_Float(WINDOW_WIDTH) - 20.f, Get_CenterOfScreen().y }, nullptr, sf::Color::Black);
	this->topBorder = new Border({ static_cast<float>(WINDOW_WIDTH), 20.0f }, { Get_CenterOfScreen().x, 20.0f }, nullptr, sf::Color::Black);
	this->bottomBorder = new Border({ static_cast<float>(WINDOW_WIDTH), 20.0f }, { Get_CenterOfScreen().x, MR_Math::Convert_To_Float(WINDOW_HEIGHT) - 20.0f }, nullptr, sf::Color::Black);

	// Other Visuals
	this->_backgroundTexture = new sf::Texture;
	this->_backgroundTexture->loadFromFile("Resources/Space-Background.jpg");
	this->_background = sf::RectangleShape({ 1800.0f, static_cast<float>(this->WINDOW_HEIGHT) });
	this->_background.setTexture(this->_backgroundTexture);
	this->_background.setFillColor(sf::Color{ 255,255,255,100 });
}

Game::~Game()
{
	delete this->_playertexture;

	delete leftBorder;
	delete rightBorder;
	delete topBorder;
	delete bottomBorder;

	delete this->_backgroundTexture;
}

void Game::Tick(float fDeltaTime)
{
	this->_deltaTime = fDeltaTime;

	this->score += this->_deltaTime;

	// Calculations
	this->GenerateObstacles();
	this->CheckObstacleCollisions();
	this->GenerateStarEnergy();
	this->CheckStarEnergyCollisions();

	// Updating
	this->_player.Update(fDeltaTime);

	for (Obstacle& ob : this->_obstacles) // Update obstacles
		ob.Update(fDeltaTime);
}

void Game::Draw(sf::RenderWindow& window)
{
	window.draw(this->_background);

	this->_player.Draw(window);

	for (Obstacle& ob : this->_obstacles) // Draw obstacles
		ob.Draw(window);

	for (StarEnergy& se : this->_starEnergies)
		se.Draw(window);

	// Screen (window) borders
	leftBorder->Draw(window);
	rightBorder->Draw(window);
	topBorder->Draw(window);
	bottomBorder->Draw(window);
}

void Game::GenerateObstacles()
{
	int rn = MR_Math::RandomInt(100);

	if (rn > 10)
		return;

	// Used to spawn obstacles within a certain percentage of the window.
	// In this case, obstcles won't spawn within the outer 5% of the window.
	float percentage = this->WINDOW_WIDTH * 0.05f; // (5%)

	float randSize = MR_Math::RandomFloatRange(5.0f, 10.0f);
	float randPosX = MR_Math::RandomFloatRange(percentage, (this->WINDOW_WIDTH - percentage));
	float randPosY = MR_Math::RandomFloat(percentage);
	float randSpeed = MR_Math::RandomFloat(1.0f);

	Obstacle ob({ randSize, randSize }, { randPosX, randPosY }, randSpeed);
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
			this->score += 5;
			this->_player.AddEnergy(this->_starEnergies[i].Get_EnergyPower());
			this->_starEnergies.erase(this->_starEnergies.begin() + i);
		}
	}
}

void Game::Execute_GameOver()
{
	std::cout << "GAME OVER!!! [Score: " << this->score << "]\n";
}