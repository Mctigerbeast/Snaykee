#pragma once
#include <iostream>
#include "fstream"

class SaveLoadSystem
{
private:
	struct PlayerData
	{
		float HighScore;
		unsigned int SelectedShip;
	};

public:
	SaveLoadSystem();
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
	/// Checks to see if a save file exists ("playerData").
	/// </summary>
	/// <returns></returns>
	bool DoesSaveFileExist();

private:
	PlayerData _playerData;
};
