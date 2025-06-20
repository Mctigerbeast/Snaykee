#include "SplashScreen_State.h"

SplashScreen_State::SplashScreen_State(GameContext& gameContext)
	: _gameContext(gameContext)
{
}

SplashScreen_State::~SplashScreen_State() {}

void SplashScreen_State::Initialize()
{
	this->_gameContext.AssetManager.LoadTexture("splashScreen", "Resources/spr_splashscreen_logo.jpg");
	this->_gameContext.AssetManager.LoadFont("splashScreenFont", "Resources/font_playful_time_star.ttf");

	// Logo
	this->_splashScreenLogo = sf::RectangleShape({ static_cast<float>(this->_gameContext.window->getSize().x) / 2.50f,static_cast<float>(this->_gameContext.window->getSize().y) / 2.50f });
	this->_splashScreenLogo.setTexture(&this->_gameContext.AssetManager.Get_Texture("splashScreen"));
	this->_splashScreenLogo.setOrigin(this->_splashScreenLogo.getSize() / 2.0f);
	float logoPosX = static_cast<float>(this->_gameContext.window->getSize().x) / 2.0f;
	float logoPosY = static_cast<float>(this->_gameContext.window->getSize().y) / 2.0f;
	this->_splashScreenLogo.setPosition({ logoPosX, logoPosY - 100.0f });

	this->_splashScreenTimer = CountdownTimer(this->_splashScreenDuration);
	this->_splashScreenTimer.StartCountdown();
}

void SplashScreen_State::HandleInput()
{
	while (const std::optional event = this->_gameContext.window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			this->_gameContext.window->close();
	}
}

void SplashScreen_State::Update(float fDeltaTime)
{
	this->_splashScreenTimer.UpdateTimer(fDeltaTime);
	this->HandleInput();

	if (this->_splashScreenTimer.IsCountingDown() == false && this->_isSplashScreenDone == false)
	{
		this->_isSplashScreenDone = true;

		// TODO: Change "GAME" to "MAIN_MENU", when all game states have been created.
		this->_gameContext.CurrentGameState = GAME;

		this->_gameContext.GameStateManager.RemoveState();
		this->_gameContext.GameStateManager.HandleStateChange();
	}
}

void SplashScreen_State::Draw(sf::RenderWindow& window)
{
	window.clear();
	window.draw(this->_splashScreenLogo);
}
