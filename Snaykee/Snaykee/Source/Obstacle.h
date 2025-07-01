#pragma once
#include "GameObject_Rectangle_SFML.h"

using namespace MR_SFML;

class Obstacle : public GameObject_Rectangle_SFML
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

private:
	float _movementSpeed = 0.0f;
};

struct Obstacle_PooledObject
{
	bool IsInUse = false;
	Obstacle ObstacleObj;
};