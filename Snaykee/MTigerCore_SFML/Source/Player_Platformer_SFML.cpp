#include "Player_Platformer_SFML.h"

Player_Platformer_SFML::Player_Platformer_SFML(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight)
	: Player_SFML(texture, imageCount, switchTime, speed),
	_jumpHeight(jumpHeight) {}

Player_Platformer_SFML::Player_Platformer_SFML(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight, sf::Vector2f playerSize, sf::Vector2f playerPos)
	: Player_SFML(texture, imageCount, switchTime, speed, playerSize, playerPos),
	_jumpHeight(jumpHeight) {}

Player_Platformer_SFML::~Player_Platformer_SFML() {}

void Player_Platformer_SFML::Update(float fDeltaTime, int row)
{
	// Player movement
	//this->_velocity.x = 0.0f; // Stops moving when keys are not pressed;
	this->_velocity.x *= 0.5f; // Halves velocity every frame, when keys are not pressed. This gives the effect of the player slowing down to a stop.

	// Get movement input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		this->_velocity.x -= 1.0f * this->_speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		this->_velocity.x += 1.0f * this->_speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		this->Handle_PlayerJump();

	// Apply gravity
	this->_velocity.y += (9.81f * 100.0f) * fDeltaTime;

	if ((this->_velocity.x == 0.0f && this->_velocity.y == 0.0f) && this->_hasIdleAnimation)
	{
		// Iddle Row
		this->_row = this->_idleRow;
	}
	else
	{
		// Moving on X axis
		if (this->_velocity.x > 0.0f)
		{
			this->_row = this->_moveRightRow; // spritesheet texture row for images (moving/facing to the right)
			this->_faceRight = true;
		}
		else if (this->_velocity.x < 0.0f)
		{
			this->_row = this->_moveLeftRow; // spritesheet texture row for images (moving/facing to the left)
			this->_faceRight = false;
		}
	}

	this->_animation.Update(this->_row, fDeltaTime, this->_faceRight);
	this->_playerBody.setTextureRect(this->_animation.UvTextureRect);
	this->_playerBody.move(this->_velocity * fDeltaTime);
}

void Player_Platformer_SFML::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f) // Collision on the left side. (Maybe we are hitting a wall).
	{
		this->_velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f) // Collision on the right side. (Maybe we are hitting a wall).
	{
		this->_velocity.x = 0.0f;
	}

	if (direction.y < 0.0f) // Collision on the bottom. (Maybe we are standing on the floor).
	{
		this->_velocity.y = 0.0f;
		this->_canJump = true;
	}
	else if (direction.y > 0.0f) // Collision on the top. (Maybe we are hitting the ceilling).
	{
		this->_velocity.y = 0.0f;
	}
}

void Player_Platformer_SFML::Handle_PlayerJump()
{
	if (this->_canJump)
	{
		this->_canJump = false;

		// Add impulse to velocity.y to make player jump.
		// Square root (2.0f * gravity * jumppHeight).
		this->_velocity.y = -std::sqrtf(2.0f * (9.81f * 100.0f) * this->_jumpHeight); // Add minus in front of equation, because of sfml's coordinate space (top left of window is posittion(0, 0)).
	}
}