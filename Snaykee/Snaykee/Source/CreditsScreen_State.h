#pragma once
#include "Defines.h"
#include "MainMenu_State.h"

namespace Snaykee
{
	class CreditsScreen_State : public MR_SFML::GameState_SFML
	{
	public:
		CreditsScreen_State(GameContext& gameContext);
		~CreditsScreen_State();

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

		sf::Text _creditsTitleUI;
		sf::Text _devsUI;
		sf::Text _soundsUI;
		sf::Text _musicUI;
		sf::Text _imagesTexturesUI;
		sf::Text _madeWithUI;
		sf::Font* _creditsTextFont = nullptr;

		MR_SFML::Button_SFML _menuButton;

		std::string _devsString = "McTiger Raphael - Game Developer\n"
			"McTiger Rapahel - Software Engineer\n"
			"McTiger Raphael - Programmer\n"
			"McTiger Raphael - Game Designer\n";

		std::string _soundsString = "SOUNDS\n"
			"- Game Over 07.wav by LilMati -- https://freesound.org/s/524742/ -- License: Attribution 4.0\n"
			"- Camera Timer.wav by Motion_S -- https ://freesound.org/s/177844/ -- License: Attribution 4.0\n"
			"- Collision by qubodup -- https ://freesound.org/s/812593/ -- License: Creative Commons 0\n"
			"- Clang by qubodup -- https ://freesound.org/s/812592/ -- License: Creative Commons 0\n"
			"- Boiler by qubodup -- https ://freesound.org/s/50590/ -- License: Creative Commons 0\n"
			"- Powerup 05.wav by LilMati -- https ://freesound.org/s/523651/ -- License: Creative Commons 0\n"
			"- Button_Click2 by BaggoNotes -- https ://freesound.org/s/721503/ -- License: Creative Commons 0\n"
			"- Audience applause with cheering.wav by Riancodgamer -- https ://freesound.org/s/414985/ -- License: Creative Commons 0\n"
			"- Party horn.wav by audiosmedia -- https ://freesound.org/s/170583/ -- License: Creative Commons 0\n"
			"- Flutter Laser by adh.dreaming -- https://freesound.org/s/634317/ -- License: Creative Commons 0\n"
			"- Space Explosion with  reverb.wav by morganpurkis -- https://freesound.org/s/394127/ -- License: Creative Commons 0";

		std::string _musicString = "MUSIC\n"
			"- Surrealism(Ambient Mix) by Andrewkn -- https://freesound.org/s/417884/ -- License: Creative Commons 0\n"
			"- Upbeat Japanese Gaming Music by Tomentum + --https ://freesound.org/s/721634/ -- License: Attribution 4.0\n"
			"- ISS conversation with the Earth.mp3 by oae888 -- https ://freesound.org/s/541586/ -- License: Creative Commons 0\n"
			"- S001_Countdown_Signal.wav by Pól -- https ://freesound.org/s/385928/ -- License: Creative Commons 0\n";

		std::string _imagesTexturesString = "IMAGES/TEXTURES\n"
			"- freepik.com\n"
			"- cleanpng.com\n"
			"- Explosion created by Luis Zuno (@ansimuz)";

		std::string _madeWithString = "Made With\n"
			"- C++ | SFML | Photoshop\n";

	private:
		void SetupText();
		void SetupButtons();
		void onMainMenu_ButtonPressed();
	};
}
