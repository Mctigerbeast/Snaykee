#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace MR_SFML
{
	class AssetManager_SFML
	{
	public:
		AssetManager_SFML() = default;
		~AssetManager_SFML() = default;

		void LoadTexture(const std::string& name, const std::string& fileName);
		sf::Texture& Get_Texture(const std::string& name);
		sf::Texture& GetLoad_Texture(const std::string& name, const std::string& fileName);

		void LoadFont(const std::string& name, const std::string& fileName);
		sf::Font& Get_Font(const std::string& name);
		sf::Font& GetLoad_Font(const std::string& name, const std::string& fileName);

	private:
		std::unordered_map<std::string, sf::Texture> _texturesMap;
		std::unordered_map<std::string, sf::Font> _fontsMap;
	};
}
