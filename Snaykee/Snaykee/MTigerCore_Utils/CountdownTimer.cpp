#include "CountdownTimer.h"
#include <iostream>

CountdownTimer::CountdownTimer(float timerDuration, VoidFunctionPointer timerEndFunction)
	: _timerDuration(timerDuration), _countdownTimerEndFunction(timerEndFunction)
{
	this->ResetTimer();
}

CountdownTimer::~CountdownTimer() {}

void CountdownTimer::UpdateTimer(float fDeltaTime)
{
	if (this->_isCountingDown)
		this->Countdown(fDeltaTime);
}

void CountdownTimer::StartCountdown()
{
	if (!this->_isCountingDown)
		this->_isCountingDown = true;
}

void CountdownTimer::StopCountdown()
{
	this->ResetTimer();
}

void CountdownTimer::Countdown(float fDeltaTime)
{
	this->_timeRemaining -= fDeltaTime;

	if (this->_timeRemaining <= 0.0f)
	{
		this->StopCountdown();

		// Call countdown timer end function (if it exists).
		if (this->_countdownTimerEndFunction != nullptr)
			this->_countdownTimerEndFunction();
	}
}

void CountdownTimer::ResetTimer()
{
	this->_isCountingDown = false;
	this->_timeRemaining = this->_timerDuration;
}

void CountdownTimer::Set_TimerEndFunction(VoidFunctionPointer newFunction)
{
	this->_countdownTimerEndFunction = newFunction;
}

void CountdownTimer::Set_TimerDuration(float newDuration)
{
	if (this->_isCountingDown)
	{
		std::cout << "Trying to change the timer's duration, while it is actively counting down. This is NOT allowed!" << "\n";
		return;
	}

	this->_timerDuration = newDuration;
	this->_timeRemaining = this->_timerDuration;
}

float CountdownTimer::Get_TimerDuration() { return this->_timerDuration; }
float CountdownTimer::Get_TimeRemaining() { return this->_timeRemaining; }
bool CountdownTimer::IsCountingDown() { return this->_isCountingDown; }
