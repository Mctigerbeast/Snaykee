#include "AudioManager_SFML.h"

namespace MR_SFML
{
	AudioManager_SFML::AudioManager_SFML(AssetManager_SFML& assetManager)
	: _assetManager(assetManager){
	}

	AudioManager_SFML::~AudioManager_SFML() {
	}

	void AudioManager_SFML::SetAssetManager(AssetManager_SFML& assetManager)
	{
		this->_assetManager = assetManager;
	}

	/*const sf::Sound& AudioManager_SFML::Get_SoundPlayer_SFX() const
	{

	}

	const sf::Sound& AudioManager_SFML::Get_SoundPlayer_Music() const
	{

	}*/

	void AudioManager_SFML::PlaySound(const std::string& name)
	{
		/*this->_sfxSoundPlayer_1.setBuffer(this->_assetManager.Get_Audio(name));
		this->_sfxSoundPlayer_1.play();*/
	}
}