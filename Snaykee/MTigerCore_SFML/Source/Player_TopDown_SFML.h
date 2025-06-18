#pragma once
#include "Player_SFML.h"

namespace MR_SFML
{
	class Player_TopDown_SFML : public Player_SFML
	{
	public:
		/// <summary>
		/// [Default Constructor] No initialization/setup.
		/// </summary>
		Player_TopDown_SFML() {}

		/// <summary>
		/// [Constructor] Setup the class.
		/// </summary>
		/// <param name="texture">The texture resource (image, spritesheet, etc.).</param>
		/// <param name="imageCount">Image count of texture (spritesheet). x = rows, y = columns.</param>
		/// <param name="switchTime">The time it takes to switch between images.</param>
		/// <param name="speed">How fast the player moves.</param>
		Player_TopDown_SFML(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);

		/// <summary>
		/// [Constructor] [Overloaded] Setup the class.
		/// </summary>
		/// <param name="texture">The texture resource (image, spritesheet, etc.).</param>
		/// <param name="imageCount">Image count of texture (spritesheet). x = rows, y = columns.</param>
		/// <param name="switchTime">The time it takes to switch between images.</param>
		/// <param name="speed">How fast the player moves.</param>
		/// <param name="playerSize">Size of the player.</param>
		/// <param name="playerPos">Postition of the player.</param>
		Player_TopDown_SFML(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f playerSize, sf::Vector2f playerPos);

		/// <summary>
		/// [Destructor] Cleans up the class.
		/// </summary>
		~Player_TopDown_SFML();

		/// <summary>
		/// Update the player.
		/// </summary>
		/// <param name="fDeltaTime"></param>
		void Update(float fDeltaTime, int row = 0) override;

	protected:
		/// <summary>
		/// Set classes default values.
		/// </summary>
		//void SetDefaultValues() override;
	};
}
