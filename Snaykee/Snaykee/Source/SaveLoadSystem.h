#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>

#ifdef  _DEBUG
const bool IS_IN_DEBUG = true;
//  _DEBUG
#else
const bool IS_IN_DEBUG = false;
#endif

class SaveLoadSystem
{
private:
	struct PlayerData
	{
		float HighScore = 0.0f;
		unsigned int SelectedShip = 1;
		bool ShowPlayerHitbox = false;
	};

public:
	SaveLoadSystem() = default;
	~SaveLoadSystem() = default;

	/// <summary>
	/// Save player data to file.
	/// </summary>
	void SavePlayerData();

	/// <summary>
	/// Load player data from file.
	/// </summary>
	void LoadPlayerData();

	/// <summary>
	/// Returns the player's save data.
	/// </summary>
	/// <returns></returns>
	const PlayerData& Get_PlayerData() const;

	/// <summary>
	/// Saves player highscore to file.
	/// </summary>
	/// <param name="newHighsScore"></param>
	void SavePlayer_HighScore(float newHighsScore);

	/// <summary>
	/// Saves player selected ship to file
	/// </summary>
	/// <param name="newSelShip"></param>
	void SavePlayer_SelectedShip(unsigned int newSelShip);

	/// <summary>
	/// Saves players option for enabling/showing hitbox.
	/// </summary>
	/// <param name="newState"></param>
	void SavePlayer_ShowPlayerHitbox(bool newState);

	/// <summary>
	/// Checks to see if a save file exists ("playerData").
	/// </summary>
	/// <returns></returns>
	bool DoesSaveFileExist();

private:
	PlayerData _playerData;
};
