#include "Explosion.h"

namespace Snaykee
{
	Explosion::Explosion(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
		: _animation(texture, imageCount, switchTime)
	{
		this->Set_Size({ 100.0f, 100.0f });
		this->_body.setTexture(texture);
	}

	Explosion::~Explosion() {
	}

	void Explosion::Init(sf::Vector2f position, sf::Vector2f size, float lifeTime)
	{
		this->Set_Size(size);
		this->_body.setPosition(position);

		this->_lifeTimer = MR_Utils::CountdownTimer(this->_lifeDuration, [this]() {this->OnLifeTimerEnd(); });
		this->_lifeTimer.StartCountdown();
	}

	void Explosion::Update(float fDeltaTime)
	{
		if (this->_isAlive)
		{
			this->_lifeTimer.UpdateTimer(fDeltaTime);
			this->_animation.Update(this->_animationRow, fDeltaTime, this->_animationFaceRight);
			this->_body.setTextureRect(this->_animation.UvTextureRect);
		}
	}

	void Explosion::Draw(sf::RenderWindow& window)
	{
		if (this->_isAlive)
			window.draw(this->_body);
	}

	void Explosion::Setup_Animation(unsigned int animRow, bool _faceRight)
	{
		this->_animationRow = animRow;
		this->_animationFaceRight = _faceRight;
	}

	void Explosion::Set_Size(sf::Vector2f size)
	{
		this->_body.setSize(size);
		this->_body.setOrigin(this->_body.getSize() / 2.0f);
	}

	void Explosion::Set_Position(sf::Vector2f position) { this->_body.setPosition(position); }

	bool Explosion::IsAlive() { return this->_isAlive; }

	void Explosion::OnLifeTimerEnd() { this->_isAlive = false; }
}
