#pragma once
#include <SFML\Graphics.hpp>
#include "Collider_SFML.h"

namespace Snaykee
{
	class Border
	{
	public:
		/// <summary>
		/// [Constructor] Sets up the class.
		/// </summary>
		/// <param name="size"></param>
		/// <param name="position"></param>
		/// <param name="texture"></param>
		Border(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture = nullptr, sf::Color color = sf::Color::White);

		/// <summary>
		/// [Destructor] Cleans up the class.
		/// </summary>
		~Border();

		/// <summary>
		/// Draw this border (object) to a window.
		/// </summary>
		/// <param name="window"></param>
		void Draw(sf::RenderWindow& window);

		/// <summary>
		/// Get the border's collider.
		/// </summary>
		/// <returns></returns>
		MR_SFML::Collider_SFML Get_Collider();

		/// <summary>
		/// Set border's color.
		/// </summary>
		/// <param name="newColor"></param>
		void SetColor(sf::Color newColor);

	private:
		sf::RectangleShape _body;
	};
}
