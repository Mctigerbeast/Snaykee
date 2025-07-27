#include "Player_SFML.h"

namespace MR_SFML
{
	Player_SFML::Player_SFML(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed)
		: _animation(texture, imageCount, switchTime)
	{
		this->_speed = speed;
		this->_row = 0;
		this->_faceRight = true;

		this->_playerBody.setSize({ 100.0f, 100.0f });
		this->_playerBody.setOrigin(this->_playerBody.getSize() / 2.0f);
		this->_playerBody.setPosition({ 100.0f, 100.0f });
		this->_playerBody.setTexture(texture);

		this->SetDefaultValues();

		// TODO: Testing purposes only!!! Shows collider (outline) of object.
		//this->_playerBody.setOutlineColor(sf::Color::Yellow);
		//this->_playerBody.setOutlineThickness(3.0f);
	}

	Player_SFML::Player_SFML(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f playerSize, sf::Vector2f playerPos)
		: _animation(texture, imageCount, switchTime)
	{
		this->_speed = speed;
		this->_row = 0;
		this->_faceRight = true;

		this->_playerBody.setSize(playerSize);
		this->_playerBody.setOrigin(this->_playerBody.getSize() / 2.0f);
		this->_playerBody.setPosition(playerPos);
		this->_playerBody.setTexture(texture);

		this->SetDefaultValues();
	}

	Player_SFML::~Player_SFML() {}

	void Player_SFML::Update(float fDeltaTime, int row)
	{
		// Player movement
		sf::Vector2f movement({ 0.0f, 0.0f });

		// Get movement input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			movement.x -= 1.0f * this->_speed * fDeltaTime;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			movement.x += 1.0f * this->_speed * fDeltaTime;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			movement.y -= 1.0f * this->_speed * fDeltaTime;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
			movement.y += 1.0f * this->_speed * fDeltaTime;

		// Clamp movement speed
		if (movement.x != 0.0f || movement.y != 0.0f)
			movement = movement / std::sqrt(2.0f);

		if ((movement.x == 0.0f && movement.y == 0.0f) && this->_hasIdleAnimation)
		{
			// Iddle Row
			this->_row = this->_idleRow;
		}
		else
		{
			// Moving on X axis
			if (movement.x > 0.0f)
			{
				this->_row = this->_moveRightRow; // spritesheet texture row for images (moving/facing to the right)
				this->_faceRight = true;
			}
			else if (movement.x < 0.0f)
			{
				this->_row = this->_moveLeftRow; // spritesheet texture row for images (moving/facing to the left)
				this->_faceRight = false;
			}

			// Moving on Y axis
			if (movement.y > 0.0f)
			{
				this->_row = this->_moveDownRow; // spritesheet texture row for images (movin/facing down)
				this->_faceRight = false;
			}
			else if (movement.y < 0.0f)
			{
				this->_row = this->_moveUpRow; // spritesheet texture row for images (movin/facing up)
				this->_faceRight = false;
			}
		}

		this->_animation.Update(this->_row, fDeltaTime);
		this->_playerBody.setTextureRect(this->_animation.UvTextureRect);
		this->_playerBody.move(movement);
	}

	void Player_SFML::Draw(sf::RenderWindow& window)
	{
		window.draw(this->_playerBody);
	}

#pragma region Setters/Mutators
	void Player_SFML::Set_PlayerSize(sf::Vector2f playerSize)
	{
		this->_playerBody.setSize(playerSize);
		this->_playerBody.setOrigin(this->_playerBody.getSize() / 2.0f);
	}

	void Player_SFML::Set_PlayerPostition(sf::Vector2f playerPosition)
	{
		this->_playerBody.setPosition(playerPosition);
	}

	void Player_SFML::SetupAnimation(int moveLeftRow, int moveRightRow, int moveUpRow, int moveDownRow, int idleRow)
	{
		this->_moveLeftRow = moveLeftRow;
		this->_moveRightRow = moveRightRow;
		this->_moveUpRow = moveUpRow;
		this->_moveDownRow = moveDownRow;
	}

	void Player_SFML::SetDefaultValues()
	{
		this->_moveLeftRow = 0;
		this->_moveRightRow = 0;
		this->_moveUpRow = 0;
		this->_moveDownRow = 0;

		this->_hasIdleAnimation = false;
		this->_idleRow = 0;
	}
#pragma endregion

#pragma region Getters/Accessors
	sf::Vector2f Player_SFML::Get_PlayerPosition() { return this->_playerBody.getPosition(); }
	Collider_SFML Player_SFML::Get_Gollider() { return Collider_SFML(this->_playerBody); }
#pragma endregion


	// Clamp speed to a specific maximum
	/*if (movement.x != 0.0f || movement.y != 0.0f) {
		float magnitude = std::sqrt(movement.x * movement.x + movement.y * movement.y);
		if (magnitude > this->_speed) {
			movement = movement / magnitude * this->_speed;
		}
	}*/
}
