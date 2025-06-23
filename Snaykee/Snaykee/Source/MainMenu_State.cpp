#include "MainMenu_State.h"

MainMenu_State::MainMenu_State(GameContext& gameContext)
	: _gameContext(gameContext), _playButton(gameContext.AssetManager)
{
}

MainMenu_State::~MainMenu_State() {}

void MainMenu_State::Initialize()
{
	float midScreenPosX = static_cast<float>(this->_gameContext.window->getSize().x) / 2.0f;
	float midScreenPosY = static_cast<float>(this->_gameContext.window->getSize().y) / 2.0f;

	this->_gameContext.AssetManager.LoadFont("mainFont", "Resources/font_playful_time_star.ttf");

	this->_playButton.Set_ButtonPosition(midScreenPosX, midScreenPosY);
	this->_playButton.MutiplyButtonSize(3.0f);
	this->_playButton.Set_ButtonText("PLAY");
	this->_playButton.Set_ButtonTextFont(this->_gameContext.AssetManager.Get_Font("mainFont"));
	this->_playButton.Set_ButtonColor_Hover(sf::Color(170.0f, 170.0f, 170.0f));
}

void MainMenu_State::HandleInput()
{
	while (const std::optional event = this->_gameContext.window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			this->_gameContext.window->close();
	}
}

void MainMenu_State::Update(float fDeltaTime)
{
	this->HandleInput();
	this->_playButton.Update(this->_gameContext.CurrentMousePositionView());
}

void MainMenu_State::Draw(sf::RenderWindow& window)
{
	window.clear();
	this->_playButton.Draw(window);
}


void MainMenu_State::PauseState()
{

}

void MainMenu_State::StartState()
{

}
