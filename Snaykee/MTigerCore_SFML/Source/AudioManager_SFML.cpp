#include "AudioManager_SFML.h"

namespace MR_SFML
{
	void AudioManager_SFML::Initialize()
	{
		this->_dummyBuffer = sf::SoundBuffer("Resources/sfx_button_click.wav");

		for (int i = 0; i < SOUND_POOL_SIZE; ++i)
			this->_soundsPool.push_back(sf::Sound(_dummyBuffer));
	}

	void AudioManager_SFML::Initialize(const sf::SoundBuffer& tempBuffer)
	{
		for (int i = 0; i < SOUND_POOL_SIZE; ++i)
			this->_soundsPool.push_back(sf::Sound(tempBuffer));
	}

	void AudioManager_SFML::PlaySound(const std::string& name, AssetManager_SFML& assetManager)
	{
		for (sf::Sound& sound : this->_soundsPool)
		{
			if (sound.getStatus() == sf::SoundSource::Status::Stopped)
			{
				sound.setBuffer(assetManager.Get_SoundBuffer(name));
				sound.play();
				break;
			}
		}
	}

	void AudioManager_SFML::PlaySound(const sf::SoundBuffer& buffer)
	{
		for (sf::Sound& sound : this->_soundsPool)
		{
			if (sound.getStatus() == sf::SoundSource::Status::Stopped)
			{
				sound.setBuffer(buffer);
				sound.play();
				break;
			}
		}
	}

	void AudioManager_SFML::PlayMusic(const std::string& fileName)
	{
		this->_music = sf::Music(fileName);
		this->_music.setLooping(true);
		this->_music.play();
	}
}