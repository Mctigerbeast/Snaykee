#include "Collider_SFML.h"

namespace MR_SFML
{
	Collider_SFML::Collider_SFML(sf::RectangleShape& body)
		: _body(body) {
	}

	Collider_SFML::~Collider_SFML() {}

	void Collider_SFML::Move(float deltaX, float deltaY)
	{
		this->_body.move({ deltaX, deltaY });
	}

	bool Collider_SFML::CheckCollision(Collider_SFML& other, float mass)
	{
		sf::Vector2f otherPosition = other.Get_Position();
		sf::Vector2f otherHalfSize = other.Get_HalfSize();

		sf::Vector2f selfPosition = this->Get_Position();
		sf::Vector2f selfHalfSize = this->Get_HalfSize();

		// Get difference (distance) bewteen bodies (center/middle of body).
		float deltaX = otherPosition.x - selfPosition.x;
		float deltaY = otherPosition.y - selfPosition.y;

		// Calculate intersection
		float intersectX = std::abs(deltaX) - (otherHalfSize.x + selfHalfSize.x);
		float intersectY = std::abs(deltaY) - (otherHalfSize.y + selfHalfSize.y);

		// Check if colliding
		if (intersectX < 0.0f && intersectY < 0.0f) // Colliding!!!
		{
			mass = std::min(std::max(mass, 0.0f), 1.0f);

			// Decide which way (direction) to push.
			if (intersectX > intersectY) // Push out in X axis.
			{
				if (deltaX > 0.0f)
				{
					this->Move(intersectX * (1.0f - mass), 0.0f); // Push this object.
					other.Move(-intersectX * mass, 0.0f); // Push other object in opposite direction.
				}
				else
				{
					this->Move(-intersectX * (1.0f - mass), 0.0f); // Push this object.
					other.Move(intersectX * mass, 0.0f); // Push other object in opposite direction.
				}
			}
			else // Push out in Y axis
			{
				if (deltaY > 0.0f)
				{
					this->Move(0.0f, intersectY * (1.0f - mass)); // Push this object.
					other.Move(0.0f, -intersectY * mass); // Push other object in opposite direction.
				}
				else
				{
					this->Move(0.0f, -intersectY * (1.0f - mass)); // Push this object.
					other.Move(0.0f, intersectY * mass); // Push other object in opposite direction.
				}
			}

			return true;
		}

		return false;
	}

	bool Collider_SFML::CheckCollision(Collider_SFML& other, sf::Vector2f& direction, float mass)
	{
		sf::Vector2f otherPosition = other.Get_Position();
		sf::Vector2f otherHalfSize = other.Get_HalfSize();

		sf::Vector2f selfPosition = this->Get_Position();
		sf::Vector2f selfHalfSize = this->Get_HalfSize();

		// Get difference (distance) bewteen bodies (center/middle of body).
		float deltaX = otherPosition.x - selfPosition.x;
		float deltaY = otherPosition.y - selfPosition.y;

		// Calculate intersection
		float intersectX = std::abs(deltaX) - (otherHalfSize.x + selfHalfSize.x);
		float intersectY = std::abs(deltaY) - (otherHalfSize.y + selfHalfSize.y);

		// Check if colliding
		if (intersectX < 0.0f && intersectY < 0.0f) // Colliding!!!
		{
			mass = std::min(std::max(mass, 0.0f), 1.0f);

			// Decide which way (direction) to push.
			if (intersectX > intersectY) // Push out in X axis.
			{
				if (deltaX > 0.0f)
				{
					this->Move(intersectX * (1.0f - mass), 0.0f); // Push this object.
					other.Move(-intersectX * mass, 0.0f); // Push other object in opposite direction.

					direction.x = 1.0f; // We're colliding with something on the right.
					direction.y = 0.0f;
				}
				else
				{
					this->Move(-intersectX * (1.0f - mass), 0.0f); // Push this object.
					other.Move(intersectX * mass, 0.0f); // Push other object in opposite direction.

					direction.x = -1.0f; // We're colliding with something on the left.
					direction.y = 0.0f;
				}
			}
			else // Push out in Y axis
			{
				if (deltaY > 0.0f)
				{
					this->Move(0.0f, intersectY * (1.0f - mass)); // Push this object.
					other.Move(0.0f, -intersectY * mass); // Push other object in opposite direction.

					direction.x = 0.0f; // We're colliding with something on the underneath.
					direction.y = 1.0f;
				}
				else
				{
					this->Move(0.0f, -intersectY * (1.0f - mass)); // Push this object.
					other.Move(0.0f, intersectY * mass); // Push other object in opposite direction.

					direction.x = 0.0f; // We're colliding with something on the above.
					direction.y = -1.0f;
				}
			}

			return true;
		}

		return false;
	}

	// Getters (Accessors)
	sf::Vector2f Collider_SFML::Get_Position() { return this->_body.getPosition(); }
	sf::Vector2f Collider_SFML::Get_HalfSize() { { return this->_body.getSize() / 2.0f; } }
}
