#include "AssetManager_SFML.h"

namespace MR_SFML
{
	// Textures
	void AssetManager_SFML::LoadTexture(const std::string& name, const std::string& fileName)
	{
		sf::Texture textureInst;

		if (textureInst.loadFromFile(fileName))
			this->_texturesMap[name] = textureInst;
		else
		{
			printf("Ttexture '%s' was not found/loaded.\n", fileName.c_str());
		}
	}

	sf::Texture& AssetManager_SFML::Get_Texture(const std::string& name)
	{
		return this->_texturesMap.at(name);
	}

	sf::Texture& AssetManager_SFML::GetLoad_Texture(const std::string& name, const std::string& fileName)
	{
		// Check if value already exists in map. Return it, if so.
		auto itr = this->_texturesMap.find(name);
		if (itr != this->_texturesMap.end())
			return itr->second;

		// If value does not exist in map.
		// Try to load value (based on given file path), add it to the map, and retun it.
		this->LoadTexture(name, fileName);
		return this->Get_Texture(name);
	}

	// Fonts
	void AssetManager_SFML::LoadFont(const std::string& name, const std::string& fileName)
	{
		sf::Font fontInst;

		if (fontInst.openFromFile(fileName))
			this->_fontsMap[name] = fontInst;
		else
		{
			printf("Font '%s'  was not found loaded.\n", fileName.c_str());
		}
	}

	sf::Font& AssetManager_SFML::Get_Font(const std::string& name)
	{
		return this->_fontsMap.at(name);
	}

	sf::Font& AssetManager_SFML::GetLoad_Font(const std::string& name, const std::string& fileName)
	{
		// Check if value already exists in map. Return it, if so.
		auto itr = this->_fontsMap.find(name);
		if (itr != this->_fontsMap.end())
			return itr->second;

		// If value does not exist in map.
		// Try to load value (based on given file path), add it to the map, and retun it.
		this->LoadFont(name, fileName);
		return this->Get_Font(name);
	}

	// Audio
	void AssetManager_SFML::LoadAudio(const std::string& name, const std::string& fileName)
	{
		sf::SoundBuffer audioInst;

		if (audioInst.loadFromFile(fileName))
			this->_audioMap[name] = audioInst;
		else
		{
			printf("Audio '%s' was not found/loaded.\n", fileName.c_str());
		}
	}

	sf::SoundBuffer& AssetManager_SFML::Get_Audio(const std::string& name)
	{
		return this->_audioMap.at(name);
	}

	sf::SoundBuffer& AssetManager_SFML::GetLoad_Audio(const std::string& name, const std::string& fileName)
	{
		// Check if value already exists in map. Return it, if so.
		auto itr = this->_audioMap.find(name);
		if (itr != this->_audioMap.end())
			return itr->second;

		// If value does not exist in map.
		// Try to load value (based on given file path), add it to the map, and retun it.
		this->LoadAudio(name, fileName);
		return this->Get_Audio(name);
	}
}
