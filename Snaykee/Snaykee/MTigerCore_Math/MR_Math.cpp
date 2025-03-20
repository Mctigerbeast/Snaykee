#include "MR_Math.h"
#include <iostream>

float MR_Math::Convert_To_Float(int val) { return static_cast<float>(val); }
float MR_Math::Convert_To_Float(double val) { return static_cast<float>(val); }
float MR_Math::Convert_To_Float(unsigned int val) { return static_cast<float>(val); }

int MR_Math::RandomInt(int maxInclusive)
{
	return (std::rand() % (maxInclusive + 1));
}

int MR_Math::RandomIntRange(int min, int max)
{
	return (min + std::rand() % ((max + 1) - min));
}

float MR_Math::RandomFloat(int max)
{
	return RandomFloatRange(0, max);
}

float MR_Math::RandomFloatRange(int min, int max)
{
	return (static_cast<float>(std::rand()) / RAND_MAX * (max - min) + min);
}

