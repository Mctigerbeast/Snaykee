#pragma once

// Common includes
#include <iostream>
#include <memory>

namespace MR_Utils
{
	// Constants
	inline constexpr float G_PI = 3.14159265359f;
	inline constexpr float G_GRAVITY = 9.81f;

	// Types
	using VoidFunctionPointer = void(*)();

	// Defines
#define LOG_Megssage(msg) std::cout << "[LOG] " << msg << "\n";
#define LOG_Error(msg) std::cout << "[ERROR] " << msg << "\n";
}

// TODO: Update Ouput and Intermediates directory for all projects.
// 
// TODO: Maybe move global header file to root directory.
// TODO: Maybe move global header file for each projec.
// TODO: (WINNER WINNER) Create a shared folder and add global header file in there. Then make sure each projects has that folder as an include directory.