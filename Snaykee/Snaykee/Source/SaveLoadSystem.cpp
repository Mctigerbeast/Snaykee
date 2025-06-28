#include "SaveLoadSystem.h"

SaveLoadSystem::SaveLoadSystem()
{
	this->_playerData = { 0.0f, 1 };
}

void SaveLoadSystem::SavePlayerData()
{
	std::ofstream outFile("playerData.save", std::ios::binary);

	if (!outFile)
	{
		std::cerr << "Error opening save file for writing.\n";
		return;
	}

	// Write data (binary) to file
	outFile.write(reinterpret_cast<const char*>(&this->_playerData.HighScore), sizeof(this->_playerData.HighScore));
	outFile.write(reinterpret_cast<const char*>(&this->_playerData.SelectedShip), sizeof(this->_playerData.SelectedShip));
	outFile.close();
}

void SaveLoadSystem::LoadPlayerData()
{
	std::ifstream inFile("playerData.save", std::ios::binary);

	if (!inFile)
	{
		std::cerr << "Error opening save file for reading.\n";
		return;
	}

	// Read data (binary) from file
	inFile.read(reinterpret_cast<char*>(&this->_playerData.HighScore), sizeof(this->_playerData.HighScore));
	inFile.read(reinterpret_cast<char*>(&this->_playerData.SelectedShip), sizeof(this->_playerData.SelectedShip));
	inFile.close();
}

const SaveLoadSystem::PlayerData& SaveLoadSystem::Get_PlayerData() const
{
	return this->_playerData;
}

void SaveLoadSystem::SavePlayer_HighScore(float newHighsScore)
{
	this->_playerData.HighScore = newHighsScore;
	this->SavePlayerData();
}

void SaveLoadSystem::SavePlayer_SelectedShip(unsigned int newSelShip)
{
	this->_playerData.SelectedShip = newSelShip;
	this->SavePlayerData();
}

bool SaveLoadSystem::DoesSaveFileExist()
{
	std::ifstream inFile("playerData.save", std::ios::binary);

	if (inFile.is_open())
	{
		inFile.close();
		return true;
	}
	else
		return false;
}
