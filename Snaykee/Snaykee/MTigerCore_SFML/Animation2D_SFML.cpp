#include "Animation2D_SFML.h"

Animation2D_SFML::Animation2D_SFML(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
	: _imageCount(imageCount), _switchImageTime(switchTime)
{
	/*this->_imageCount = imageCount;
	this->_switchImageTime = switchTime;*/
	this->_totalTime = 0.0f;
	this->_currentImage.x - 0;

	// Calculate width and heigh of each image (in texture)
	UvTextureRect.size.x = texture->getSize().x / static_cast<float>(imageCount.x);
	UvTextureRect.size.y = texture->getSize().y / static_cast<float>(imageCount.y);
}

Animation2D_SFML::~Animation2D_SFML() {}

void Animation2D_SFML::Update(int imageRow, float fDeltaTime)
{
	this->_currentImage.y = imageRow;
	this->_totalTime += fDeltaTime;

	if (this->_totalTime >= this->_switchImageTime)
	{
		this->_totalTime -= _switchImageTime;
		_currentImage.x++;

		// If current index of texture is equal/bigger than total amount of textures, reset it.
		if (this->_currentImage.x >= _imageCount.x)
		{
			this->_currentImage.x = 0;
		}

		// Left and top offset of uv rect.
		UvTextureRect.position.x = this->_currentImage.x * UvTextureRect.size.x;
		//UvTextureRect.size.x = std::abs(UvTextureRect.size.x);
		UvTextureRect.position.y = this->_currentImage.y * UvTextureRect.size.y;
	}
}

void Animation2D_SFML::Update(int imageRow, float fDeltaTime, bool faceRight)
{
	this->_currentImage.y = imageRow;
	this->_totalTime += fDeltaTime;

	if (this->_totalTime >= this->_switchImageTime)
	{
		this->_totalTime -= _switchImageTime;
		_currentImage.x++;

		// If current index of texture is equal/bigger than total amount of textures, reset it.
		if (this->_currentImage.x >= _imageCount.x)
		{
			this->_currentImage.x = 0;
		}

		// Left and top offset of uv rect.
		if (faceRight)
		{
			UvTextureRect.position.x = this->_currentImage.x * UvTextureRect.size.x;
			UvTextureRect.size.x = std::abs(UvTextureRect.size.x);
		}
		else
		{
			// Adding 1 changes the width of the image to the negative version of it.
			// Thus flipping it (making it face the other way)
			UvTextureRect.position.x = (this->_currentImage.x + 1) * std::abs(UvTextureRect.size.x);
			UvTextureRect.size.x = -std::abs(UvTextureRect.size.x); // Prevents from constantly inverting (positive;negative) image every frame.
		}

		UvTextureRect.position.y = this->_currentImage.y * UvTextureRect.size.y;
	}
}
