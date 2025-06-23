#pragma once
#include "Defines_SFML.h"
#include "MTigerCore/CountdownTimer.h"

using namespace MR_SFML;
using namespace MR_Utils;

class SplashScreen_State : public GameState_SFML
{
public:
	SplashScreen_State(GameContext& gameContext);
	~SplashScreen_State();

	void Initialize();
	void HandleInput();
	void Update(float fDeltaTime = 0.0f);
	void Draw(sf::RenderWindow& window);

	void PauseState() {}
	void StartState() {}

private:
	GameContext& _gameContext;

	float _splashScreenDuration = 5.0f;
	CountdownTimer _splashScreenTimer;
	bool _isSplashScreenDone = false;

	sf::RectangleShape _splashScreenLogoBanner;
};