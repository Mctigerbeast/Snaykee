#pragma once
#include "MTigerCore_SFML/GameObject_Rectangle.h"

class Obstacle : public GameObject_Rectangle
{
public:
	Obstacle(sf::Vector2f size, sf::Vector2f position, float moveSpeed, sf::Texture* texture = nullptr, sf::Color color = sf::Color::White);
	~Obstacle();
	void Update(float fDeltaTime, int row = 0) override;
	void Set_MovementSpeed(float newSpeed);

private:
	float _movementSpeed = 0.0f;
};

