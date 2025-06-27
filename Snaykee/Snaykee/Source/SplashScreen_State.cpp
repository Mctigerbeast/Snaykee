#include "SplashScreen_State.h"
#include "MainMenu_State.h"

SplashScreen_State::SplashScreen_State(GameContext& gameContext)
	: _gameContext(gameContext)
{
}

SplashScreen_State::~SplashScreen_State() {}

void SplashScreen_State::Initialize()
{
	this->_gameContext.AssetManager.LoadTexture("splashScreenBanner", "Resources/spr_splashscreen_logo_banner.jpg");

	// Create splashscreen logo
	float logoPosX = static_cast<float>(this->_gameContext.window->getSize().x) / 2.0f;
	float logoPosY = static_cast<float>(this->_gameContext.window->getSize().y) / 2.0f;
	this->_splashScreenLogoBanner = sf::RectangleShape({ static_cast<float>(this->_gameContext.window->getSize().x) * 0.75f,static_cast<float>(this->_gameContext.window->getSize().y) * 0.1558f });
	this->_splashScreenLogoBanner.setTexture(&this->_gameContext.AssetManager.Get_Texture("splashScreenBanner"));
	this->_splashScreenLogoBanner.setOrigin(this->_splashScreenLogoBanner.getSize() / 2.0f);
	this->_splashScreenLogoBanner.setPosition({ logoPosX, logoPosY - 50.0f });
	this->_splashScreenLogoBanner.setOutlineThickness(5.0f);
	this->_splashScreenLogoBanner.setOutlineColor(sf::Color::Black);

	// Start splashscreen timer
	this->_splashScreenTimer = CountdownTimer(this->_splashScreenDuration, [this]() {this->OnSplashscreenTimerEnd(); });
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
	this->HandleInput();
	this->_splashScreenTimer.UpdateTimer(fDeltaTime);
}

void SplashScreen_State::Draw(sf::RenderWindow& window)
{
	window.clear(sf::Color(255, 116, 88)); // Set splashscreen background color
	window.draw(this->_splashScreenLogoBanner);
}

void SplashScreen_State::OnSplashscreenTimerEnd()
{
	this->_gameContext.CurrentGameState = MAIN_MENU;
	this->_gameContext.GameStateManager.AddState(std::unique_ptr<GameState_SFML>(new MainMenu_State(this->_gameContext)), true);
	this->_gameContext.GameStateManager.HandleStateChange();
}
