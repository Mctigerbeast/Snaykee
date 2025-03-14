#include "Player_TopDown_SFML.h"

Player_TopDown_SFML::Player_TopDown_SFML(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed)
	: Player_SFML(texture, imageCount, switchTime, speed) {}

Player_TopDown_SFML::Player_TopDown_SFML(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f playerSize, sf::Vector2f playerPos)
	: Player_SFML(texture, imageCount, switchTime, speed, playerSize, playerPos) {}

Player_TopDown_SFML::~Player_TopDown_SFML() {}

void Player_TopDown_SFML::Update(float fDeltaTime, int row)
{
	Player_SFML::Update(fDeltaTime, row);
}