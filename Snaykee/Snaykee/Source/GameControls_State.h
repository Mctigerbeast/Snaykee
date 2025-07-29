#pragma once
#include "Defines.h"
#include "MainMenu_State.h"

namespace Snaykee
{
	class GameControls_State : public MR_SFML::GameState_SFML
	{
	public:
		GameControls_State(GameContext& gameContext);
		~GameControls_State();

		void Initialize() override;
		void HandleInput() override;
		void Update(float fDeltaTime = 0.0f) override;
		void Draw(sf::RenderWindow& window) override;

		void PauseState() override {}
		void StartState() override {}

	private:
		GameContext& _gameContext;

		sf::RectangleShape _menuBackground;
		sf::Texture* _menuBackgroundTexture = nullptr;

		sf::Text _gameControlsTitleUI;
		sf::Text _gameControlsUI;
		sf::Font* _gameControlsTextFont = nullptr;

		MR_SFML::Button_SFML _menuButton;

		std::string _gameControlsString = "W - Move Up\n"
			"A - Move Left\n"
			"S - Move Down\n"
			"D - Move Right\n\n\n"
			"Space Bar - Shoot/fire laser shot\n\n\n"

			"Up Arrow Key - Move Up\n"
			"Left Arrow Key - Move Left\n"
			"Down Arrow Key - Move Down\n"
			"Right Arrow Key - Move Right\n\n\n"

			"Enable/disable the player's (ship) hitbox from the pause menu.\n"
			" - Game uses bounding box collision.\n"
			" - This setting will help when determining where to position yourself when avoiding/dodging asteroids.\n\n\n"

			"HOW TO PLAY (tips):\n"
			"- Use your piloting skills, dodge asteroids to stay alive. If an asteroid hits you, your ship's energy will decrease.\n"
			"- Your ship's energy is constantly depleting. Collect star energy to replenish your ship energy's and increase your score.\n"
			"- Shoot laser rounds/shots to destroy asteroids. Use this wisely because shooting lasers will decrease your ship's energy.\n"
			"- Enable ship hitbox for more percise maneuvering.\n";

	private:
		void SetupText();
		void SetupButtons();
		void onMainMenu_ButtonPressed();
	};
}
