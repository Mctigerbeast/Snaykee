#pragma once
#include <SFML\Graphics.hpp>
#include "Animation2D_SFML.h"
#include "Collider_SFML.h"

namespace MR_SFML
{
	class Player_SFML
	{
	public:
		/// <summary>
		/// [Default Constructor] No initialization/setup.
		/// </summary>
		Player_SFML() {}

		/// <summary>
		/// [Constructor] Setup the class.
		/// </summary>
		/// <param name="texture">The texture resource (image, spritesheet, etc.).</param>
		/// <param name="imageCount">Image count of texture (spritesheet). x = rows, y = columns.</param>
		/// <param name="switchTime">The time it takes to switch between images.</param>
		/// <param name="speed">How fast the player moves.</param>
		Player_SFML(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);

		/// <summary>
		/// [Constructor] [Overloaded] Setup the class.
		/// </summary>
		/// <param name="texture">The texture resource (image, spritesheet, etc.).</param>
		/// <param name="imageCount">Image count of texture (spritesheet). x = rows, y = columns.</param>
		/// <param name="switchTime">The time it takes to switch between images.</param>
		/// <param name="speed">How fast the player moves.</param>
		/// <param name="playerSize">Size of the player.</param>
		/// <param name="playerPos">Postition of the player.</param>
		Player_SFML(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f playerSize, sf::Vector2f playerPos);

		/// <summary>
		/// [Destructor] Cleans up the class.
		/// </summary>
		~Player_SFML();

		/// <summary>
		/// Update the player.
		/// </summary>
		/// <param name="fDeltaTime"></param>
		virtual void Update(float fDeltaTime, int row = 0);

		/// <summary>
		/// Draw the player to the screen.
		/// </summary>
		/// <param name="window"></param>
		void Draw(sf::RenderWindow& window);

		/// <summary>
		/// Sets the player's size.
		/// </summary>
		/// <param name="playerSize">Size of player.</param>
		void Set_PlayerSize(sf::Vector2f playerSize);

		/// <summary>
		/// Sets the player's position.
		/// </summary>
		/// <param name="playerPos">Position of player.</param>
		void Set_PlayerPostition(sf::Vector2f playerPos);

		/// <summary>
		/// Gets the player's position.
		/// </summary>
		/// <returns>The player's position.</returns>
		sf::Vector2f Get_PlayerPosition();

		/// <summary>
		/// Gets player's collider object.
		/// </summary>
		/// <returns>Player's collider object.</returns>
		Collider_SFML Get_Gollider();

		/// <summary>
		/// Setup animation. Set rows for spritesheet/texture image. This assumes all rows have the same number of images/textures.
		/// </summary>
		/// <param name="[moveLeftRow]">Spritesheet row (move left) for images/textures/animation. (Starts at index 0).</param>
		/// <param name="[moveRightRow]">Spritesheet row for (move right) images/textures/animation. (Starts at index 0).</param>
		/// <param name="[moveUpRow]">Spritesheet row for (move up) images/textures/animation. (Starts at index 0).</param>
		/// <param name="[moveDownRow]">Spritesheet row for (move down) images/textures/animation. (Starts at index 0).</param>
		void SetupAnimation(int moveLeftRow, int moveRightRow, int moveUpRow, int moveDownRow, int idleRow = 0);

	protected:
		/// <summary>
		/// Set class' default values.
		/// </summary>
		virtual void SetDefaultValues();

	protected:
		sf::RectangleShape _playerBody;
		unsigned int _row; // unsigned int will never be less than 0
		float _speed;
		bool _faceRight;

		// Animation
		Animation2D_SFML _animation;
		unsigned int _moveLeftRow;
		unsigned int _moveRightRow;
		unsigned int _moveUpRow;
		unsigned int _moveDownRow;

		int _idleRow;
		bool _hasIdleAnimation;
	};
}
