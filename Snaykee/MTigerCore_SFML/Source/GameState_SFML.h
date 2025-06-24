#pragma once
#include "SFML/Graphics.hpp"

namespace MR_SFML
{
	class GameState_SFML
	{
	public:
		GameState_SFML() = default;
		~GameState_SFML() = default;

		/// <summary>
		/// Intialize the state (buttons, textures, audio, etc.).
		/// </summary>
		virtual void Initialize() = 0;

		/// <summary>
		/// Functionality/logic for handling inputs.
		/// </summary>
		virtual void HandleInput() = 0;

		/// <summary>
		/// Perform state's update functionalit/logic.
		/// </summary>
		/// <param name="fDeltaTime"></param>
		virtual void Update(float fDeltaTime = 0.0f) = 0;

		/// <summary>
		/// Perform Draw functionality/logic.
		/// </summary>
		/// <param name="window"></param>
		virtual void Draw(sf::RenderWindow& window) = 0;

		/// <summary>
		/// Functionality for pausing the state.
		/// </summary>
		virtual void PauseState() {}

		/// <summary>
		/// Functionality for starting/resuming the state.
		/// </summary>
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
