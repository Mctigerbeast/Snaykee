#pragma once
#include "MTigerCore_SFML/GameObject_Rectangle.h"

class StarEnergy
{
public:
	/// <summary>
	/// [Constructor] Sets up the class.
	/// </summary>
	/// <param name="size"></param>
	/// <param name="position"></param>
	/// <param name="texture"></param>
	StarEnergy(unsigned int energyPwr, sf::Vector2f position, sf::Texture* texture = nullptr, sf::Color color = sf::Color::White);

	/// <summary>
	/// [Destructor] Cleans up the class.
	/// </summary>
	~StarEnergy();

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

private:
	sf::RectangleShape _body;
	unsigned int _energyPower;
};

