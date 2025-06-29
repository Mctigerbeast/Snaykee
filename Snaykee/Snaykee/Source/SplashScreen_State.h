#pragma once
#include "MTigerCore/CountdownTimer.h"
#include "MainMenu_State.h"

using namespace MR_SFML;
using namespace MR_Utils;

class SplashScreen_State : public GameState_SFML
{
public:
	SplashScreen_State(GameContext& gameContext);
	~SplashScreen_State();

	void Initialize() override;
	void HandleInput() override;
	void Update(float fDeltaTime = 0.0f) override;
	void Draw(sf::RenderWindow& window) override;

	void PauseState() override {}
	void StartState() override {}

private:
	GameContext& _gameContext;

	float _splashScreenDuration = 5.0f;
	CountdownTimer _splashScreenTimer;

	sf::RectangleShape _splashScreenLogoBanner;

private:
	void OnSplashscreenTimerEnd();
};