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

		/// <summary>
		/// Loads a texture and adds it to the textures map.
		/// </summary>
		/// <param name="name">Name/alias to give the texture.</param>
		/// <param name="fileName">Name (filepath) of the texture file.</param>
		void LoadTexture(const std::string& name, const std::string& fileName);

		/// <summary>
		/// Retrieves a texture, if it has already been loaded and added to the textures map.
		/// </summary>
		/// <param name="name">Name/alias of the texture to retrieve.</param>
		/// <returns>Reference to the texture.</returns>
		sf::Texture& Get_Texture(const std::string& name);

		/// <summary>
		/// Retrieves a texture from the textures map.
		/// If the texture is not already in the map, attemp to load and add the texture to the map.
		/// </summary>
		/// <param name="name">Name/alias of the texture to retrieve.</param>
		/// <param name="fileName">Reference to the texture.</param>
		/// <returns></returns>
		sf::Texture& GetLoad_Texture(const std::string& name, const std::string& fileName);

		/// <summary>
		/// Loads a font and adds it to the fonts map.
		/// </summary>
		/// <param name="name">Name/alias to give the font.</param>
		/// <param name="fileName">Name (filepath) of the font file.</param>
		void LoadFont(const std::string& name, const std::string& fileName);

		/// <summary>
		/// Retrieves a font, if it has already been loaded and added to the fonts map.
		/// </summary>
		/// <param name="name">Name/alias of the font to retrieve.</param>
		/// <returns>Reference to the font.</returns>
		sf::Font& Get_Font(const std::string& name);

		/// <summary>
		/// Retrieves a font from the fonts map.
		/// If the font is not already in the map, attemp to load and add the font to the map.
		/// </summary>
		/// <param name="name">Name/alias of the font to retrieve.</param>
		/// <param name="fileName">Reference to the font.</param>
		/// <returns></returns>
		sf::Font& GetLoad_Font(const std::string& name, const std::string& fileName);

	private:
		/// <summary>
		/// Contains textures which have been loaded.
		/// </summary>
		std::unordered_map<std::string, sf::Texture> _texturesMap;

		/// <summary>
		/// Contains fonts which have been loaded.
		/// </summary>
		std::unordered_map<std::string, sf::Font> _fontsMap;
	};
}
