#pragma once
class MR_Math
{
public: // Objects
	struct Vector2D_I
	{
		int x, y;
	};

	struct Vector2D_F
	{
		float x, y;
	};

public: // Functions
	static float Convert_To_Float(int val);
	static float Convert_To_Float(double val);
	static float Convert_To_Float(unsigned int val);

	static int RandomInt(int maxInclusive);
	static int RandomIntRange(int min, int max);
	static float RandomFloat(int max);
	static float RandomFloatRange(int min, int max);
};

