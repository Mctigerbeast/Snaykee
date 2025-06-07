#pragma once
#include "Collider_SFML.h"

class GameObject_Rectangle_SFML
{
public:
	/// <summary>
	/// [Constructor] Sets up the class.
	/// </summary>
	/// <param name="size"></param>
	/// <param name="position"></param>
	/// <param name="texture"></param>
	GameObject_Rectangle_SFML(sf::Vector2f size, sf::Vector2f position, sf::Texture* texture = nullptr, sf::Color color = sf::Color::White);

	/// <summary>
	/// [Destructor] Cleans up the class.
	/// </summary>
	~GameObject_Rectangle_SFML();

	/// <summary>
	/// Draw this border (object) to a window.
	/// </summary>
	/// <param name="window"></param>
	void Draw(sf::RenderWindow& window);

	/// <summary>
	/// To be called every frame.
	/// </summary>
	/// <param name="fDeltaTime"></param>
	/// <param name="row"></param>
	virtual void Update(float fDeltaTime, int row);

	/// <summary>
	/// Get the border's collider.
	/// </summary>
	/// <returns></returns>
	Collider_SFML Get_Collider();

	/// <summary>
	/// Set border's color.
	/// </summary>
	/// <param name="newColor"></param>
	void SetColor(sf::Color newColor);

protected:
	sf::RectangleShape _body;
	sf::Vector2f _velocity;
};

