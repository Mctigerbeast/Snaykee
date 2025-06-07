#pragma once

namespace MR_Math
{
	struct Vector2D_I
	{
		int x, y;
	};

	struct Vector2D_F
	{
		float x, y;
	};

#pragma region Conversions
	/// <summary>
	/// Converts a value/number (int) to a float value.
	/// </summary>
	/// <param name="val"></param>
	/// <returns></returns>
	float Convert_To_Float(int val);

	/// <summary>
	/// Converts a value/number (double) to a float value.
	/// </summary>
	/// <param name="val"></param>
	/// <returns></returns>
	float Convert_To_Float(double val);

	/// <summary>
	/// Converts a value/number (unsigned int) to a float value.
	/// </summary>
	/// <param name="val"></param>
	/// <returns></returns>
	float Convert_To_Float(unsigned int val);

	/// <summary>
	/// Converts an angle from degrees to radians.
	/// </summary>
	/// <param name="angle">The angle (in degrees) to convert.</param>
	/// <returns></returns>
	float Convert_Angle_DegreesToRadians(float angleDegrees);

	/// <summary>
	/// Converts an angle from radians to degrees.
	/// </summary>
	/// <param name="radian">The angle (in radians) to convert.</param>
	/// <returns></returns>
	float Convert_Angle_RadiansToDegrees(float angleRadians);
#pragma endregion

#pragma region Random
	int RandomInt(int max);
	int RandomIntRange(int min, int max);

	float RandomFloat(float max);
	float RandomFloatRange(float min, float max);
#pragma endregion

#pragma region Clamping
	/// <summary>
	/// Adjusts float number/value to be between 0.0f (minimum) and 1.0f (maximum);
	/// </summary>
	/// <param name="valueToAdjust">The value/number (float) to adjust.</param>
	/// <returns>The adjusted value; Adjusted to be within/bewteen 0.0f and 1.0f.</returns>
	float Clamp_Float(float valueToAdjust);

	/// <summary>
	/// Adjusts double number/value to be between 0.0 (minimum) and 1.0 (maximum);
	/// </summary>
	/// <param name="valueToAdjust">The value/number (double) to adjust.</param>
	/// <returns>The adjusted value; Adjusted to be within/bewteen 0.0 and 1.0.</returns>
	double Clamp_Double(double valueToAdjust);

	/// <summary>
	/// Adjust float number/value (passed in), to be within specified bounds.
	/// </summary>
	/// <param name="boundsMin">The minimum floating point value.</param>
	/// <param name="boundsMax">The maximum floating point value.</param>
	/// <param name="valueToAdjust">The floating point value to adjust.</param>
	/// <returns>The adjusted value; Adjusted to be within the specified bounds (min and max).</returns>
	float  Clamp_Float(float boundsMin, float boundsMax, float valueToAdjust);

	/// <summary>
	/// Adjust int number/value (passed in), to be within specified bounds.
	/// </summary>
	/// <param name="boundsMin">The minimum int (integer) value.</param>
	/// <param name="boundsMax">The maximum int (integer) value.</param>
	/// <param name="valueToAdjust">The int (integer) value to adjust.</param>
	/// <returns>The adjusted value; Adjusted to be within the specified bounds (min and max).</returns>
	int Clamp_Int(int boundsMin, int boundsMax, int valueToAdjust);

	/// <summary>
	/// Adjust double number/value (passed in), to be within specified bounds.
	/// </summary>
	/// <param name="boundsMin">The minimum double value.</param>
	/// <param name="boundsMax">The maximum double value.</param>
	/// <param name="valueToAdjust">The double value to adjust.</param>
	/// <returns>The adjusted value; Adjusted to be within the specified bounds (min and max).</returns>
	double Clamp_Double(double boundsMin, double boundsMax, double valueToAdjust);

	/// <summary>
	/// Adjust long number/value (passed in), to be within specified bounds.
	/// </summary>
	/// <param name="boundsMin">The minimum long value.</param>
	/// <param name="boundsMax">The maximum long value.</param>
	/// <param name="valueToAdjust">The long value to adjust.</param>
	/// <returns>The adjusted value; Adjusted to be within the specified bounds (min and max).</returns>
	long Clamp_Long(long boundsMin, long boundsMax, long valueToAdjust);

	/// <summary>
	/// Clamps an angle between -0 and 360.
	/// </summary>
	/// <param name="angle">The angle to clamp.</param>
	/// <returns></returns>
	float ClampAngle_Degrees(float angleDegrees);
#pragma endregion

#pragma region Lerping
	/// <summary>
	/// Lerps between two given values.
	/// </summary>
	/// <param name="startVal">Starting value; Value 1.</param>
	/// <param name="endVal">Ending value; Value 2.</param>
	/// <param name="percentage">How much to lerp by (0.0 = 0% and 1.0 = 100%).</param>
	/// <returns></returns>
	float Lerp(float startVal, float endVal, float percentage);

	/// <summary>
	/// Lerps between two given values. Clamps the lerp percentace/fraction (passed-in), between 0.0 and 1.0.
	/// </summary>
	/// <param name="startVal">Starting value; Value 1.</param>
	/// <param name="endVal">Ending value; Value 2.</param>
	/// <param name="percentage">How much to lerp by (0.0 = 0% and 1.0 = 100%).</param>
	/// <param name="clampPercentage">Should lerp percentage be clamped (0.0 = min and 1.0 = max). </param>
	/// <returns></returns>
	float LerpClamped_01(float startVal, float endVal, float percentage);

	/// <summary>
	/// Lerps between two given values. Clamps the lerp percentace/fraction (passed-in), between specified range (min and max).
	/// </summary>
	/// <param name="startVal">Starting value; Value 1.</param>
	/// <param name="endVal">Ending value; Value 2.</param>
	/// <param name="percentage">How much to lerp by (0.0 = 0% and 1.0 = 100%).</param>
	/// <param name="percentageMin">Minimum value of lerp percentage.</param>
	/// <param name="percentageMax">Maximum value of lerp percentage.</param>
	/// <returns></returns>
	float LerpClamped(float startVal, float endVal, float percentage, float percentageMin, float percentageMax);
#pragma endregion

}
