#pragma once
#include "Animation2D_SFML.h"
#include "MTigerCore/CountdownTimer.h"

namespace Snaykee
{
	class Explosion
	{
	public:
		Explosion(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
		~Explosion();

		void Init(sf::Vector2f position, sf::Vector2f size, float lifeTime = 1.0f);
		void Update(float fDeltaTime);
		void Draw(sf::RenderWindow& window);

		/// <summary>
		/// Setup the explosion's animation.
		/// </summary>
		/// <param name="animRow">Animation's row (on spritesheet).</param>
		/// <param name="faceRight">Should animation face the right side fo screen (X).</param>
		void Setup_Animation(unsigned int animRow, bool faceRight);

		void Set_Size(sf::Vector2f size);
		void Set_Position(sf::Vector2f position);
		bool IsAlive();

	private:
		bool _isAlive = true;
		float _lifeDuration = 1.0f;
		MR_Utils::CountdownTimer _lifeTimer;

		sf::RectangleShape _body;
		MR_SFML::Animation2D_SFML _animation;

		unsigned int _animationRow = 0;
		bool _animationFaceRight = false;

	private:
		/// <summary>
		/// Funtionality/logic for when explosion is 'dead' (gone/over).
		/// </summary>
		void OnLifeTimerEnd();
	};
}
