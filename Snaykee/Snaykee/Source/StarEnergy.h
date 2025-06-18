#pragma once
#include "GameObject_Rectangle_SFML.h"

using namespace MR_SFML;

class StarEnergy
{
public:
	/// <summary>
	/// [Constructor] Sets up the class.
	/// </summary>
	/// <param name="size"></param>
	/// <param name="position"></param>
	/// <param name="texture"></param>
	StarEnergy(sf::Vector2f position, sf::Texture* texture = nullptr, sf::Color color = sf::Color::White);

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
	/// Get the border's collider.
	/// </summary>
	/// <returns></returns>
	Collider_SFML Get_Collider();

	/// <summary>
	/// To be called every frame.
	/// </summary>
	/// <param name="fDeltaTime"></param>
	/// <param name="row"></param>
	virtual void Update(float fDeltaTime, int row);

	/// <summary>
	/// Star's energy power.
	/// </summary>
	/// <returns>The star's energy power value/ammount.</returns>
	unsigned int Get_EnergyPower();

private:
	sf::RectangleShape _body;
	unsigned int _energyPower;
};

