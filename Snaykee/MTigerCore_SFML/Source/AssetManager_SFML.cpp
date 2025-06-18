#include "AssetManager_SFML.h"

namespace MR_SFML
{
	void AssetManager_SFML::LoadTexture(const std::string& name, const std::string& fileName)
	{
		sf::Texture textureInst;

		if (textureInst.loadFromFile(fileName))
			this->_texturesMap[name] = textureInst;
		else
		{
			printf("Button texture '%s' was not found/loaded.\n", fileName.c_str());
		}
	}

	sf::Texture& AssetManager_SFML::Get_Texture(const std::string& name)
	{
		return this->_texturesMap.at(name);
	}

	void AssetManager_SFML::LoadFont(const std::string& name, const std::string& fileName)
	{
		sf::Font fontInst;

		if (fontInst.openFromFile(fileName))
			this->_fontsMap[name] = fontInst;
		else
		{
			printf("Button font '%s'  was not found loaded.\n", fileName.c_str());
		}
	}

	sf::Font& AssetManager_SFML::Get_Font(const std::string& name)
	{
		return this->_fontsMap.at(name);
	}
}
