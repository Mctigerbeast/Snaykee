#pragma once
#include "SFML/Graphics.hpp"

namespace MR_SFML
{
	class GameState_SFML
	{
	public:
		GameState_SFML() = default;
		~GameState_SFML() = default;

		virtual void Initialize() = 0;
		virtual void HandleInput() = 0;
		virtual void Update(float fDeltaTime = 0.0f) = 0;
		virtual void Draw(sf::RenderWindow& window) = 0;

		virtual void PauseState() {}
		virtual void StartState() {}
	};

	enum CurrentGameState
	{
		SPLASH_SCREEN = 0,
		MAIN_MENU,
		GAME,
		GAME_OVER
	};
}
