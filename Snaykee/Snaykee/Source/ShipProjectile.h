#pragma once
#include "GameObject_Rectangle_SFML.h"
#include "MTigerCore/MR_Math.h"

namespace Snaykee
{
	class ShipProjectile : public MR_SFML::GameObject_Rectangle_SFML
	{
	public:
		ShipProjectile(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture = nullptr, sf::Color color = sf::Color::White);
		~ShipProjectile();
		void Update(float fDeltaTime, int row = 0) override;
		void Set_MovementSpeed(float newSpeed);

		/// <summary>
		/// Reset object's properties.
		/// </summary>
		/// <param name="size"></param>
		/// <param name="position"></param>
		/// <param name="moveSpeed"></param>
		/// <param name="texture"></param>
		void Reset(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture, sf::Color color = sf::Color::White);

	private:
		float _movementSpeed = 700.0f;
	};

	struct ShipProjectile_PooledObject
	{
		bool IsInUse = false;
		ShipProjectile ShipProjectileObj;
	};
}
