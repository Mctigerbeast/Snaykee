#pragma once

class CountdownTimer
{
public:
	typedef void(*VoidFunctionPointer)();

	/// <summary>
	/// [Constructor] Initializes class (variables, events, etc.).
	/// </summary>
	/// <param name="duration"></param>
	CountdownTimer(float timerDuration = 3.0f, VoidFunctionPointer timerEndFunction = nullptr);

	/// <summary>
	/// [Destructor] Cleans up the class.
	/// </summary>
	/// <param name="duration"></param>
	~CountdownTimer();

	/// <summary>
	/// Updates the countdown timer. Needs to be called every frame.
	/// </summary>
	void UpdateTimer(float fDeltaTime = 0.0f);

	/// <summary>
	/// Functionality for starting the countdown timer.
	/// </summary>
	void StartCountdown();

	/// <summary>
	/// Functionality for stopping the countdown timer.
	/// </summary>
	void StopCountdown();

	/// <summary>
	/// Changes/updates the countdown timer's duration.
	/// </summary>
	/// <param name="newDuration"></param>
	void Set_TimerDuration(float newDuration);

	/// <summary>
	/// Changes/updates the timer's 'countdown end function'.
	/// </summary>
	void Set_TimerEndFunction(VoidFunctionPointer newFunction);

	/// <summary>
	/// </summary>
	/// <returns>The duration of the countdown timer.</returns>
	float Get_TimerDuration();

	/// <summary>
	/// </summary>
	/// <returns>Remaining time left on countdown.</returns>
	float Get_TimeRemaining();

	/// <summary>
	/// </summary>
	/// <returns>(True) if timer is in the process of counting down.</returns>
	bool IsCountingDown();

private:
	/// <summary>
	/// Logic for timer counting down.
	/// </summary>
	void Countdown(float fDeltaTime);

	/// <summary>
	/// Resets the countdown timer.
	/// </summary>
	void ResetTimer();

private:
	float _timerDuration = 3.0f;
	float _timeRemaining;
	bool _isCountingDown;
	VoidFunctionPointer _countdownTimerEndFunction;
};

