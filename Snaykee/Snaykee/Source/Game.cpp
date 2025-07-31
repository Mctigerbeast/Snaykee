#include "Game.h"

namespace Snaykee
{
	sf::Vector2f Game::Get_CenterOfScreen()
	{
		return sf::Vector2f{ this->Get_Window_WidthF() / 2.0f, this->Get_Window_HeightF() / 2.0f };
	}

	Game::Game(GameContext& gameContext)
		: _gameContext(gameContext), _scoreText_UI(*_scoreTextFont_UI), _energyText_UI(*_energyTextFont_UI) {
	}

	Game::~Game()
	{
		delete leftBorder;
		delete rightBorder;
		delete topBorder;
		delete bottomBorder;
	}

	void Game::Initialize()
	{
		// Setup obstacles container (vector) (pooled)
		for (int i = 0; i < OBSTACLES_POOL_SIZE; ++i)
		{
			Obstacle_PooledObject obstacleObj = { false, Obstacle({1.0f, 1.0f}, {0.0f, 0.0f}, 0.0f, nullptr, sf::Color(150, 150, 150)) };
			this->_obstaclesPool.push_back(obstacleObj);
			//this->_obstaclesPool.emplace_back(Obstacle({ 1.0f, 1.0f }, { 0.0f, 0.0f }, 0.0f));
		}

		// Setup star energies container (vector) (pooled)
		for (int i = 0; i < STAR_ENERGY_POOL_SIZE; ++i)
		{
			StarEnergy_PooledObject starEnergyObj = { false, StarEnergy({1.0f, 1.0f}, &this->_starEnergy_1_Texture, &this->_starEnergy_2_Texture, &this->_starEnergy_3_Texture) };
			this->_starEnergiesPool.push_back(starEnergyObj);
		}

		// Setup ship projectiles container (vector) (pooled)
		for (int i = 0; i < SHIP_PROJECTILE_POOL_SIZE; ++i)
		{
			ShipProjectile_PooledObject shipProjectileObj = { false, ShipProjectile({1.0f, 1.0f}, {0.0f, 0.0f}, nullptr) };
			this->_shipProjectilesPool.push_back(shipProjectileObj);
		}


		// Set resources
		this->_backgroundTexture = &this->_gameContext.AssetManager.Get_Texture("nebulaBackground");

		this->_playerTexture_1 = &this->_gameContext.AssetManager.Get_Texture("greenShip");
		this->_playerTexture_2 = &this->_gameContext.AssetManager.Get_Texture("yellowShip");
		this->_playerTexture_3 = &this->_gameContext.AssetManager.Get_Texture("whiteShip");
		this->_playerTexture_4 = &this->_gameContext.AssetManager.Get_Texture("darkShip");

		this->_asteroid_1_Texture = &this->_gameContext.AssetManager.Get_Texture("asteroid_1_Texture");
		this->_asteroid_2_Texture = &this->_gameContext.AssetManager.Get_Texture("asteroid_2_Texture");
		this->_asteroid_3_Texture = &this->_gameContext.AssetManager.Get_Texture("asteroid_3_Texture");
		this->_asteroid_4_Texture = &this->_gameContext.AssetManager.Get_Texture("asteroid_4_Texture");

		this->_starEnergy_1_Texture = &this->_gameContext.AssetManager.Get_Texture("starEnergy_1_Texture");
		this->_starEnergy_2_Texture = &this->_gameContext.AssetManager.Get_Texture("starEnergy_2_Texture");
		this->_starEnergy_3_Texture = &this->_gameContext.AssetManager.Get_Texture("starEnergy_3_Texture");

		this->_scoreTextFont_UI = &this->_gameContext.AssetManager.Get_Font("mainFont");
		this->_energyTextFont_UI = &this->_gameContext.AssetManager.Get_Font("mainFont");

		this->_gameContext.AssetManager.Get_SoundBuffer("starCollect");
		this->_gameContext.AssetManager.Get_SoundBuffer("lowFeul");
		this->_gameContext.AssetManager.Get_SoundBuffer("obstacleHit");
		this->_gameContext.AssetManager.Get_SoundBuffer("playerDeathGameOver");

		// Create game's screen (window) borders
		this->leftBorder = new Border({ 20.0f, this->Get_Window_HeightF() }, { 10.0f, Get_CenterOfScreen().y }, nullptr, sf::Color::Black);
		this->rightBorder = new Border({ 20.0f, this->Get_Window_HeightF() }, { this->Get_Window_WidthF() - 10.f, Get_CenterOfScreen().y }, nullptr, sf::Color::Black);
		this->topBorder = new Border({ this->Get_Window_WidthF(), 20.0f }, { Get_CenterOfScreen().x, 10.0f }, nullptr, sf::Color::Black);
		this->bottomBorder = new Border({ this->Get_Window_WidthF(), 20.0f }, { Get_CenterOfScreen().x, this->Get_Window_HeightF() - 10.0f }, nullptr, sf::Color::Black);

		// Player
		this->_player = Player_SpaceShip(this->DeterminePlayerShipTexture(), sf::Vector2u({ 1, 1 }), 0.1f, 500.0f);
		this->_player.Set_PlayerSize({ 80.0f, 100.0f });
		this->_player.Set_PlayerPostition({ this->Get_Window_WidthF() / 2.0f,  this->Get_Window_HeightF() / 2.0f });
		this->_player.Start();
		this->_player.ShowHitbox(this->_gameContext.SaveSystem.Get_PlayerData().ShowPlayerHitbox);

		// Other Visuals
		this->_background = sf::RectangleShape({ this->Get_Window_WidthF(), this->Get_Window_HeightF() });
		this->_background.setTexture(this->_backgroundTexture);
		this->_background.setFillColor(sf::Color(255, 255, 255, 85));

		if (!this->_playerProjectileShader.loadFromFile("Resources/sh_outer_glow_attn.frag", sf::Shader::Type::Fragment))
			printf("shader 'sh_outer_glow_attn.frag' was not found/loaded.");

		this->explosion = std::make_unique<Explosion>(Explosion(&this->_gameContext.AssetManager.Get_Texture("explosion"), sf::Vector2u({ 8, 1 }), 0.125f));
		this->explosion->Init({ 0.0f, 0.0f }, { 0.0f, 0.0f });

		// UI (score text)
		this->_scoreText_UI = sf::Text(*this->_scoreTextFont_UI);
		this->_scoreText_UI.setPosition({ this->_gameContext.PercentOfWindow_X(05.f), this->_gameContext.PercentOfWindow_Y(95.0f) });
		this->_scoreText_UI.setOrigin(this->_scoreText_UI.getGlobalBounds().size / 2.0f);
		this->_scoreText_UI.setLetterSpacing(2.0f);
		this->_scoreText_UI.setFillColor(sf::Color::Black);
		this->_scoreText_UI.setOutlineThickness(2.0f);
		this->_scoreText_UI.setOutlineColor(sf::Color::White);
		this->_scoreText_UI.setCharacterSize(20.0f);

		this->_energyText_UI = sf::Text(*this->_energyTextFont_UI);
		this->_energyText_UI.setPosition({ this->_gameContext.PercentOfWindow_X(82.5f), this->_gameContext.PercentOfWindow_Y(95.0f) });
		this->_energyText_UI.setOrigin(this->_energyText_UI.getGlobalBounds().size / 2.0f);
		this->_energyText_UI.setLetterSpacing(2.0f);
		this->_energyText_UI.setFillColor(sf::Color::Black);
		this->_energyText_UI.setOutlineThickness(2.0f);
		this->_energyText_UI.setOutlineColor(sf::Color::White);
		this->_energyText_UI.setCharacterSize(20.0f);

		// Play game music
		this->_gameContext.AudioManager.PlayMusic("Resources/mus_gameplay.wav");
	}

	void Game::HandleInput()
	{
		while (const std::optional event = this->_gameContext.window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				this->_gameContext.window->close();
		}

		// Pausing the game
		if (!this->_isGamePaused && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			this->_gameContext.CurrentGameState = MR_SFML::PAUSE_MENU;
			this->_gameContext.AudioManager.PauseMusic();
			this->_gameContext.GameStateManager.AddState(std::unique_ptr<GameState_SFML>(new PauseMenu_State(this->_gameContext)), false);
		}

		// Firing Projectiles
		if (this->_player.CanFireProjectile() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			this->_player.FireProjectile();

			for (ShipProjectile_PooledObject& sp : this->_shipProjectilesPool)
			{
				if (!sp.IsInUse)
				{
					sp.IsInUse = true;
					sp.ShipProjectileObj.Reset({ 20.0f, 40.0f }, this->_player.Get_PlayerPosition(), &this->_gameContext.AssetManager.Get_Texture("shipProjectile"));
					sp.ShipProjectileObj.SetupShader(this->_playerProjectileShader, this->_playerProjectileColor_Inner, this->_playerProjectileColor_Outer);
					this->_gameContext.AudioManager.PlaySound("laserShot", this->_gameContext.AssetManager, 50.0f);
					break;
				}
			}
		}
	}

	void Game::Update(float fDeltaTime)
	{
		// Pausing the game if window goes out of focus
		if (!this->_gameContext.window->hasFocus() && !this->_isGamePaused)
		{
			this->_gameContext.CurrentGameState = MR_SFML::PAUSE_MENU;
			this->_gameContext.AudioManager.PauseMusic();
			this->_gameContext.GameStateManager.AddState(std::unique_ptr<GameState_SFML>(new PauseMenu_State(this->_gameContext)), false);
			return;
		}

		if (this->_isGamePaused)
			return;

		this->HandleInput();

		// Calculations (generation and collision)
		this->GenerateObstacles();
		this->CheckObstacleCollisions();
		this->GenerateStarEnergy();
		this->CheckStarEnergyCollisions();
		this->CheckShipProjectileCollisions();

		// Update player
		this->_player.Update(fDeltaTime);

		// Update obstacles
		for (Obstacle_PooledObject& ob : this->_obstaclesPool)
		{
			if (ob.IsInUse)
				ob.ObstacleObj.Update(fDeltaTime);
		}

		// Update ship projectiles
		for (ShipProjectile_PooledObject& sp : this->_shipProjectilesPool)
		{
			if (sp.IsInUse)
				sp.ShipProjectileObj.Update(fDeltaTime);
		}

		// Update score
		this->_score += fDeltaTime;
		this->_scoreText_UI.setString("SCORE: " + std::to_string(this->_score));
		this->_energyText_UI.setString("ENERGY: " + std::to_string(this->_player.Get_Energy()));

		// Low energy/fuel
		if (!this->_isLowEnergy && this->_player.Get_Energy() < 25)
		{
			this->_isLowEnergy = true;
			this->_gameContext.AudioManager.PlaySound("lowFeul", this->_gameContext.AssetManager, 200.0f, 2.0f);
		}
		else if (this->_isLowEnergy && this->_player.Get_Energy() > 24)
			this->_isLowEnergy = false;

		// explosion animation
		if (this->explosion != nullptr)
			this->explosion->Update(fDeltaTime);
		if (this->explosion_backup != nullptr)
			this->explosion_backup->Update(fDeltaTime);
	}

	void Game::Draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(this->_background);

		// Draw star energies
		for (StarEnergy_PooledObject& se : this->_starEnergiesPool)
		{
			if (se.IsInUse)
				se.StarEnergyObj.Draw(window);
		}

		// Draw ship projectiles
		for (ShipProjectile_PooledObject& sp : this->_shipProjectilesPool)
		{
			if (sp.IsInUse)
				sp.ShipProjectileObj.Draw(window);
		}

		// Draw player
		this->_player.Draw(window);

		// Draw obstacles
		for (Obstacle_PooledObject& ob : this->_obstaclesPool)
		{
			if (ob.IsInUse)
				ob.ObstacleObj.Draw(window);
		}

		// Draw explosion animation
		if (this->explosion != nullptr)
			this->explosion->Draw(window);
		if (this->explosion_backup != nullptr)
			this->explosion_backup->Draw(window);

		// Draw Screen (window) borders
		leftBorder->Draw(window);
		rightBorder->Draw(window);
		topBorder->Draw(window);
		bottomBorder->Draw(window);

		// Draw UI (score text)
		window.draw(this->_scoreText_UI);

		if (this->_player.Get_Energy() > 75)
			this->_energyText_UI.setOutlineColor(sf::Color::Green);
		else if (this->_player.Get_Energy() > 49)
			this->_energyText_UI.setOutlineColor(sf::Color::Yellow);
		else if (this->_player.Get_Energy() > 24)
			this->_energyText_UI.setOutlineColor(sf::Color(255, 165, 0));
		else
			this->_energyText_UI.setOutlineColor(sf::Color::Red);

		window.draw(this->_energyText_UI);
	}

#pragma region Game State
	void Game::PauseState()
	{
		this->_isGamePaused = true;
	}

	void Game::StartState()
	{
		this->_isGamePaused = false;
		this->_player.ShowHitbox(this->_gameContext.SaveSystem.Get_PlayerData().ShowPlayerHitbox);
	}

	void Game::Execute_GameOver()
	{
		this->_isGameOver = true;
		bool isNewHighscore = (this->_score > this->_gameContext.SaveSystem.Get_PlayerData().HighScore);

		// Save player's high score
		if (isNewHighscore)
			this->_gameContext.SaveSystem.SavePlayer_HighScore(this->_score);

		// Show game over screen
		this->_gameContext.CurrentGameState = MR_SFML::GAME_OVER;
		this->_gameContext.AudioManager.StopMusic();
		this->_gameContext.AudioManager.PlaySound("playerDeathGameOver", this->_gameContext.AssetManager, 70.0f);
		this->_gameContext.GameStateManager.AddState(std::unique_ptr<GameState_SFML>(new GameOver_State(this->_gameContext, this->_score, isNewHighscore)), true);
	}

	void Game::Execute_StartGame()
	{
		this->_score = 0; // Reset player score
		this->_player.Set_PlayerPostition({ this->Get_Window_WidthF() / 2.0f,  this->Get_Window_HeightF() / 2.0f }); // Reset player's position
		this->_player.ResetPlayer(); // Reset player's health, etc.

		// Reset obstacles pool objects
		for (Obstacle_PooledObject& ob : this->_obstaclesPool)
			ob.IsInUse = false;

		// Reset star energies pool objects
		for (StarEnergy_PooledObject& se : this->_starEnergiesPool)
			se.IsInUse = false;

		this->_isGameOver = false;
	}
#pragma endregion

	void Game::GenerateObstacles()
	{
		//int rn = MR_Math::RandomInt(100);
		int rn = MR_Math::RandomInt(200);

		if (rn > 10)
			return;

		// Used to spawn obstacles within a certain percentage of the window.
		// In this case, obstcles won't spawn within the outer 5% of the window.
		float percentage = this->Get_Window_WidthF() * 0.05f; // (5%)

		float randSize = MR_Math::RandomFloatRange(20.0f, 50.0f);
		float randPosX = MR_Math::RandomFloatRange(percentage, (this->Get_Window_WidthF() - percentage));
		float randPosY = MR_Math::RandomFloat(this->Get_Window_HeightF() * 0.05f);
		float randSpeed = MR_Math::RandomFloat(1.0f);

		// Choose a valid object form the obstacles pool
		for (int i = this->_nextValidPoolObject_Index; i < OBSTACLES_POOL_SIZE; ++i)
		{
			if (this->_obstaclesPool[i].IsInUse == false)
			{
				this->_obstaclesPool[i].IsInUse = true;
				this->_obstaclesPool[i].ObstacleObj.Reset({ randSize, randSize }, { randPosX, randPosY }, randSpeed, this->DetermineObstacleTexture(), sf::Color(150, 150, 150));
				this->_nextValidPoolObject_Index = i + 1;

				// Reset next valid pool object index/pointer, if end of the pool container (vector) is reached.
				if (this->_nextValidPoolObject_Index >= OBSTACLES_POOL_SIZE)
					this->_nextValidPoolObject_Index = 0;

				break;
			}
		}
	}

	void Game::CheckObstacleCollisions()
	{
		MR_SFML::Collider_SFML playerCollider = this->_player.Get_Gollider();
		MR_SFML::Collider_SFML bottomBorderCollider = this->bottomBorder->Get_Collider();

		for (Obstacle_PooledObject& ob : this->_obstaclesPool)
		{
			if (ob.IsInUse)
			{
				// Collision(s) with player
				if (ob.ObstacleObj.Get_Collider().CheckCollision(playerCollider, 1.0f))
				{
					this->_player.OnObstacleHit();
					ob.IsInUse = false;

					if (!this->_player.IsAlive())
						this->Execute_GameOver();
					else
						this->_gameContext.AudioManager.PlaySound("obstacleHit", this->_gameContext.AssetManager, 15.0f);
				}

				// Collision(s) with border(s)
				if (ob.ObstacleObj.Get_Collider().CheckCollision(bottomBorderCollider, 0.0f))
				{
					ob.IsInUse = false;
				}
			}
		}

		// Screen (window) borders
		this->leftBorder->Get_Collider().CheckCollision(playerCollider, 1.0f);
		this->rightBorder->Get_Collider().CheckCollision(playerCollider, 1.0f);
		this->topBorder->Get_Collider().CheckCollision(playerCollider, 1.0f);
		this->bottomBorder->Get_Collider().CheckCollision(playerCollider, 1.0f);
	}

	void Game::GenerateStarEnergy()
	{
		int activeStars = 0;
		for (StarEnergy_PooledObject& se : this->_starEnergiesPool)
		{
			if (se.IsInUse)
				activeStars++;

			if (activeStars >= 3)
				return;
		}

		int rn = MR_Math::RandomInt(10000);

		if (rn > 10)
			return;

		// Used to spawn star energy within a certain percentage of the window.
		// In this case, star energy won't spawn within the outer 10% of the window.
		float percentageX = this->Get_Window_WidthF() * 0.10f;
		float percentageY = this->Get_Window_HeightF() * 0.10f;

		float randPosX = MR_Math::RandomFloatRange(percentageX, (this->Get_Window_WidthF() - percentageX));
		float randPosY = MR_Math::RandomFloatRange(percentageY, (this->Get_Window_HeightF() - percentageY));

		// Use percentage (5% of window) for size. Star energy object's size should be relative to window size.
		float sizeX = this->Get_Window_WidthF() * 0.05f;
		float sizeY = this->Get_Window_HeightF() * 0.05f;

		// Choose a valid object form the star energies pool
		for (int i = 0; i < STAR_ENERGY_POOL_SIZE; ++i)
		{
			if (this->_starEnergiesPool[i].IsInUse == false)
			{
				this->_starEnergiesPool[i].IsInUse = true;
				this->_starEnergiesPool[i].StarEnergyObj.Reset({ randPosX, randPosY }, { sizeX, sizeY });
				break;
			}
		}
	}

	void Game::CheckStarEnergyCollisions()
	{
		MR_SFML::Collider_SFML playerCollider = this->_player.Get_Gollider();

		for (StarEnergy_PooledObject& se : this->_starEnergiesPool)
		{
			if (se.IsInUse)
			{
				// Collision(s) with player
				if (se.StarEnergyObj.Get_Collider().CheckCollision(playerCollider, 1.0f))
				{
					this->_score += 5;
					this->_player.AddEnergy(se.StarEnergyObj.Get_EnergyPower());
					se.IsInUse = false;
					this->_gameContext.AudioManager.PlaySound("starCollect", this->_gameContext.AssetManager, 60.0f);
				}
			}
		}
	}

	void Game::CheckShipProjectileCollisions()
	{
		MR_SFML::Collider_SFML topBorderCollider = this->topBorder->Get_Collider();

		for (ShipProjectile_PooledObject& sp : this->_shipProjectilesPool)
		{
			if (sp.IsInUse)
			{
				// Collision(s) with border(s)
				if (sp.ShipProjectileObj.Get_Collider().CheckCollision(topBorderCollider, 0.0f))
					sp.IsInUse = false;

				// Collision(s) with obstacle(s)
				for (Obstacle_PooledObject& ob : this->_obstaclesPool)
				{
					MR_SFML::Collider_SFML obstacleCollider = ob.ObstacleObj.Get_Collider();

					if (ob.IsInUse && sp.ShipProjectileObj.Get_Collider().CheckCollision(obstacleCollider, 1.0f))
					{
						ob.IsInUse = false;
						sp.IsInUse = false;
						this->_gameContext.AudioManager.PlaySound("explosion", this->_gameContext.AssetManager, 200.0f);

						// Visuals (animation)
						if (!this->explosion->IsAlive())
						{
							this->explosion = std::make_unique<Explosion>(Explosion(&this->_gameContext.AssetManager.Get_Texture("explosion"), sf::Vector2u({ 8, 1 }), 0.125f));
							this->explosion->Init(ob.ObstacleObj.Get_Position(), ob.ObstacleObj.Get_Size() * 2.0f, 1.0f);
						}
						else
						{
							this->explosion_backup = std::make_unique<Explosion>(Explosion(&this->_gameContext.AssetManager.Get_Texture("explosion"), sf::Vector2u({ 8, 1 }), 0.125f));
							this->explosion_backup->Init(ob.ObstacleObj.Get_Position(), ob.ObstacleObj.Get_Size() * 2.0f, 1.0f);
						}
					}
				}
			}
		}
	}

	sf::Texture* Game::DeterminePlayerShipTexture()
	{
		switch (this->_gameContext.SaveSystem.Get_PlayerData().SelectedShip)
		{
		case 1:
			//this->_playerProjectileColor = sf::Color(0, 255, 0, 255);
			this->_playerProjectileColor_Inner = sf::Color(3, 130, 60, 255);
			this->_playerProjectileColor_Outer = sf::Color::Green;
			return this->_playerTexture_1;
			break;
		case 2:
			this->_playerProjectileColor_Inner = sf::Color(240, 200, 40, 255);
			this->_playerProjectileColor_Outer = sf::Color::Yellow;
			return this->_playerTexture_2;
			break;
		case 3:
			this->_playerProjectileColor_Inner = sf::Color(50, 200, 200, 255);
			this->_playerProjectileColor_Outer = sf::Color(60, 100, 250);
			return this->_playerTexture_3;
			break;
		case 4:
			this->_playerProjectileColor_Inner = sf::Color(225, 70, 20, 255);
			this->_playerProjectileColor_Outer = sf::Color::Red;
			return this->_playerTexture_4;
			break;
		default:
			break;
		}
	}

	sf::Texture* Game::DetermineObstacleTexture()
	{
		int rn = MR_Math::RandomIntRange(2, 4);

		switch (rn)
		{
		case 1:
			return this->_asteroid_1_Texture;
			break;
		case 2:
			return this->_asteroid_2_Texture;
			break;
		case 3:
			return this->_asteroid_3_Texture;
			break;
		case 4:
			return this->_asteroid_4_Texture;
			break;
		default:
			break;
		}
	}

	float Game::Get_Window_WidthF() { return this->_gameContext.Get_Window_WidthF(); }

	float Game::Get_Window_HeightF() { return this->_gameContext.Get_Window_WidthF(); }
}
