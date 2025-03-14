#pragma once
#include <SFML\Graphics.hpp>

class Collider_SFML
{
public:
	/// <summary>
	/// [Constructor] Setup the class.
	/// </summary>
	/// <param name="body"></param>
	Collider_SFML(sf::RectangleShape& body);

	/// <summary>
	/// [Destructor] Cleans up the class.
	/// </summary>
	~Collider_SFML();

	/// <summary>
	/// Move this collider's body.
	/// </summary>
	/// <param name="deltaX">How much to move in the X direction.</param>
	/// <param name="deltaY">How much to move in the Y direction.</param>
	void Move(float deltaX, float deltaY);

	/// <summary>
	/// Checks collision between this collider and another.
	/// </summary>
	/// <param name="other">The other collider.</param>
	/// <param name="mass">The other collider's mass. The closer to 1.0f = the heavier and harder to move.</param>
	/// <returns></returns>
	bool CheckCollision(Collider_SFML& other, float mass);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="other"></param>
	/// <param name="direction"></param>
	/// <param name="mass"></param>
	/// <returns></returns>

	bool CheckCollision(Collider_SFML& other, sf::Vector2f& direction, float mass);

	/// <summary>
	/// Gets position of this collider's body.
	/// </summary>
	/// <returns>Position of body.</returns>
	sf::Vector2f Get_Position();

	/// <summary>
	/// Gets the body's half size.
	/// </summary>
	/// <returns>Half of body's size.</returns>
	sf::Vector2f Get_HalfSize();

private:
	sf::RectangleShape& _body;
};

