#pragma once
#include "AssetManager_SFML.h"

namespace MR_SFML
{
	class AudioManager_SFML
	{
	public:
		AudioManager_SFML() = default;
		AudioManager_SFML(AssetManager_SFML& assetManager);
		~AudioManager_SFML();

		void SetAssetManager(AssetManager_SFML& assetManager);

		const sf::Sound& Get_SoundPlayer_SFX() const;
		const sf::Sound& Get_SoundPlayer_Music() const;

		void PlaySound(const std::string& name);
		void PlaySound(const sf::SoundBuffer& name);

	private:
		AssetManager_SFML& _assetManager;

		/*sf::Sound _sfxSoundPlayer_2;
		sf::Sound _musicSoundPlayer;*/

		/*sf::SoundBuffer* buffer = nullptr;
		sf::Sound _sfxSoundPlayer_1 = sf::Sound(*buffer);*/
	};
}
