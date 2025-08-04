#include "SaveLoadSystem.h"

std::string GetLocalAppData_Safe()
{
	char* buffer = nullptr;
	size_t size = 0;

	if (_dupenv_s(&buffer, &size, "LOCALAPPDATA") != 0 || buffer == nullptr)
		throw std::runtime_error("Failed to get LOCALAPPDATA.");

	std::unique_ptr<char[], decltype(&free)> localAppData(buffer, free);
	return std::string(localAppData.get());
}

void SaveLoadSystem::SavePlayerData()
{
	std::ofstream outFile;
	if (IS_IN_DEBUG)
		outFile = std::ofstream("playerData.save", std::ios::binary);
	else
	{
		std::filesystem::path saveDir = std::filesystem::path(GetLocalAppData_Safe()) / "SNAYKEE";

		// Create folder if it does not already exist.
		if (!std::filesystem::exists(saveDir))
		{
			std::filesystem::create_directories(saveDir);
			std::cout << "Creating save file directory...\n";
		}

		std::filesystem::path filePath(saveDir / "playerData.save");
		outFile = std::ofstream(filePath, std::ios::binary);
	}

	if (!outFile)
	{
		std::cerr << "Error opening save file for writing.\n";
		return;
	}

	// Write data (binary) to file
	outFile.write(reinterpret_cast<const char*>(&this->_playerData.HighScore), sizeof(this->_playerData.HighScore));
	outFile.write(reinterpret_cast<const char*>(&this->_playerData.SelectedShip), sizeof(this->_playerData.SelectedShip));
	outFile.write(reinterpret_cast<const char*>(&this->_playerData.ShowPlayerHitbox), sizeof(this->_playerData.ShowPlayerHitbox));
	outFile.close();
}

void SaveLoadSystem::LoadPlayerData()
{
	std::ifstream inFile;
	if (IS_IN_DEBUG)
		inFile = std::ifstream("playerData.save", std::ios::binary);
	else
	{
		std::filesystem::path saveDir = std::filesystem::path(GetLocalAppData_Safe()) / "SNAYKEE";
		std::filesystem::path filePath(saveDir / "playerData.save");
		inFile = std::ifstream(filePath, std::ios::binary);
	}

	if (!inFile)
	{
		std::cerr << "Error opening save file for reading.\n";
		return;
	}

	// Read data (binary) from file
	inFile.read(reinterpret_cast<char*>(&this->_playerData.HighScore), sizeof(this->_playerData.HighScore));
	inFile.read(reinterpret_cast<char*>(&this->_playerData.SelectedShip), sizeof(this->_playerData.SelectedShip));
	inFile.read(reinterpret_cast<char*>(&this->_playerData.ShowPlayerHitbox), sizeof(this->_playerData.ShowPlayerHitbox));
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

void SaveLoadSystem::SavePlayer_ShowPlayerHitbox(bool newState)
{
	this->_playerData.ShowPlayerHitbox = newState;
	this->SavePlayerData();
}

bool SaveLoadSystem::DoesSaveFileExist()
{
	std::ifstream inFile;
	if (IS_IN_DEBUG)
		inFile = std::ifstream("playerData.save", std::ios::binary);
	else
	{
		std::filesystem::path saveDir = std::filesystem::path(GetLocalAppData_Safe()) / "SNAYKEE";
		std::filesystem::path filePath(saveDir / "playerData.save");
		inFile = std::ifstream(filePath, std::ios::binary);
	}

	if (inFile.is_open())
	{
		inFile.close();
		return true;
	}
	else
		return false;
}
