#pragma once
#include "Button_SFML.h"
#include "MainMenu_State.h"

namespace Snaykee
{
	class PauseMenu_State : public MR_SFML::GameState_SFML
	{
	public:
		PauseMenu_State(GameContext& gameContext);
		~PauseMenu_State();

		void Initialize() override;
		void HandleInput() override;
		void Update(float fDeltaTime = 0.0f) override;
		void Draw(sf::RenderWindow& window) override;

		void PauseState() override {}
		void StartState() override {}

	private:
		GameContext& _gameContext;

		sf::RectangleShape _pauseMenuBackground;
		MR_SFML::Button_SFML _resumeButton;
		MR_SFML::Button_SFML _mainMenuButton;

		sf::Text _pauseMenuTitle;
		sf::Font* _pauseMenuFont = nullptr;

	private:
		/// <summary>
		/// Functionality/logic for resuming the game from pause state.
		/// </summary>
		void onResume_ButtonPressed();

		/// <summary>
		/// Functionality/logic for going to main menu.
		/// </summary>
		void onMainMenu_ButtonPressed();
	};
}
