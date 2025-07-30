#pragma once
#include "Game.h"
#include "MainMenu_State.h"

namespace Snaykee
{
	class GameOver_State : public MR_SFML::GameState_SFML
	{
	public:
		GameOver_State(GameContext& gameContext, float playerScore, bool isNewHighscore);
		~GameOver_State();

		void Initialize() override;
		void HandleInput() override;
		void Update(float fDeltaTime = 0.0f) override;
		void Draw(sf::RenderWindow& window) override;

		void PauseState() override {}
		void StartState() override {}

	private:
		float _playerScore = 0;
		bool _isNewHighscore = false;

		GameContext& _gameContext;

		sf::RectangleShape _gameOverBackground;
		sf::RectangleShape _newHighscoreVisuals;
		MR_SFML::Button_SFML _restartButton;
		MR_SFML::Button_SFML _mainMenuButton;

		sf::Text _gameOverTitle;
		sf::Text _playerScoreUI;
		sf::Text _highscoreUI;
		sf::Font* _pauseMenuFont = nullptr;

		MR_Utils::CountdownTimer _playNewHighscoreEffectsTimer;

	private:
		/// <summary>
		/// Functionality/logic for restarting (playing again).
		/// </summary>
		void onRestart_ButtonPressed();

		/// <summary>
		/// Functionality/logic for going to main menu.
		/// </summary>
		void onMainMenu_ButtonPressed();

		/// <summary>
		/// Functionality/logic for when player achieves new high score.
		/// </summary>
		void onNewHighscore();
	};
}
