#pragma once
#include "GameObject_Rectangle_SFML.h"
#include "MTigerCore/MR_Math.h"

namespace Snaykee
{
	class Obstacle : public MR_SFML::GameObject_Rectangle_SFML
	{
	public:
		Obstacle(sf::Vector2f size, sf::Vector2f position, float moveSpeed, sf::Texture* texture = nullptr, sf::Color color = sf::Color::White);
		~Obstacle();
		void Update(float fDeltaTime, int row = 0) override;
		void Set_MovementSpeed(float newSpeed);

		/// <summary>
		/// Reset object's properties.
		/// </summary>
		/// <param name="size"></param>
		/// <param name="position"></param>
		/// <param name="moveSpeed"></param>
		/// <param name="texture"></param>
		void Reset(sf::Vector2f size, sf::Vector2f position, float moveSpeed, sf::Texture* texture, sf::Color color = sf::Color::White);

		sf::Vector2f Get_Size();
		sf::Vector2f Get_Position();

	private:
		float _movementSpeed = 0.0f;
		sf::Angle _rotationAngle = sf::Angle::Zero;
	};

	struct Obstacle_PooledObject
	{
		bool IsInUse = false;
		Obstacle ObstacleObj;
	};
}
