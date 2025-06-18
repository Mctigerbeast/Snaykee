#pragma once
#include <SFML\Graphics.hpp>

namespace MR_SFML
{
	class Animation2D_SFML
	{
	public: // Functions
		/// <summary>
		/// [Default Constructor] No initialization/setup.
		/// </summary>
		Animation2D_SFML() {}

		/// <summary>
		/// [Constructor] Setup the class.
		/// </summary>
		/// <param name="texture">The texture resource (image, spritesheet, etc.).</param>
		/// <param name="imageCount">Image count of texture (spritesheet). x = rows, y = columns.</param>
		/// <param name="switchTime">The time it takes to switch between images.</param>
		Animation2D_SFML(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

		/// <summary>
		/// [Destructor] Cleans up the class.
		/// </summary>
		~Animation2D_SFML();

		/// <summary>
		/// Update the animation by changing texture images.
		/// To be called every frame.
		/// </summary>
		/// <param name="imageRow">The row of the animation's texture (spritesheet)</param>
		/// <param name="fDeltaTime"></param>
		void Update(int imageRow, float fDeltaTime);

		/// <summary>
		/// Update the animation by changing texture images.
		/// To be called every frame.
		/// </summary>
		/// <param name="imageRow">The row of the animation's texture (spritesheet)</param>
		/// <param name="fDeltaTime"></param>
		/// <param name="faceRight">If image/texture is facing right.</param>
		void Update(int imageRow, float fDeltaTime, bool faceRight);

	private: // Functions


	public: // Variables
		sf::IntRect UvTextureRect;

	private: // Variables
		sf::Vector2u _imageCount;
		sf::Vector2u _currentImage;

		float _totalTime;
		float _switchImageTime;
	};
}
