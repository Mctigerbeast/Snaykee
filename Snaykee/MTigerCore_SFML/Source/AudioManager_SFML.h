#pragma once
#include "AssetManager_SFML.h"

namespace MR_SFML
{
	class AudioManager_SFML
	{
	public:
		const unsigned int SOUND_POOL_SIZE = 20;

		AudioManager_SFML() = default;
		~AudioManager_SFML() = default;

		/// <summary>
		/// Perform setup logic.
		/// </summary>
		void Initialize();

		/// <summary>
		/// [Overloaded] Performs setup logic.
		/// </summary>
		/// <param name="tempBuffer">Default sound buffer for initializing the Sounds pool.</param>
		void Initialize(const sf::SoundBuffer& tempBuffer);

		/// <summary>
		/// Plays a sound.
		/// </summary>
		/// <param name="buffer">The sound buffer to play.</param>
		/// <param name="volume">The volume of the sound buffer to play.</param>
		void PlaySound(const sf::SoundBuffer& buffer, float volume = 100.0f, float pitch = 1.0f);

		/// <summary>
		/// [Overloaded] Plays a sound.
		/// </summary>
		/// <param name="name">Name/alias of the sound to play.</param>
		/// <param name="assetManager">The asset manager where the sound is located. This assumes the sound has already been loaded and is present in the asset manager.</param>
		/// <param name="volume">The volume of the sound buffer to play.</param>
		void PlaySound(const std::string& name, AssetManager_SFML& assetManager, float volume = 100.0f, float pitch = 1.0f);

		/// <summary>
		/// Plays music.
		/// </summary>
		/// <param name="filePath">Name (filepath) of the audio (music) file.</param>
		void PlayMusic(const std::string& fileName);

		/// <summary>
		/// Pause the music that is currently playing.
		/// </summary>
		void PauseMusic();

		/// <summary>
		/// Resume the music that is currently playing (paused).
		/// </summary>
		void ResumeMusic();

		/// <summary>
		/// Stop the music that is currently playing.
		/// </summary>
		void StopMusic();

	private:
		std::vector<sf::Sound> _soundsPool;
		sf::SoundBuffer _dummyBuffer;
		sf::Music _music;
	};
}
