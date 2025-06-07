#pragma once
#include <iostream>

namespace MR_Utils
{
	/// <summary>
	/// Clears the console page.
	/// </summary>
	void ClearPage();

	/// <summary>
	/// [NOT RECOMMENDED] Waits for a keypress (user) before continuing.
	/// <para>Not recommended because this is non-portable.</para>
	/// </summary>
	void WaitForKeyPress();

	/// <summary>
	/// Waits for ENTER keypress before continuing.
	/// </summary>
	void WaitForKeyPress_Enter();

	/// <summary>
	/// Add line break(s).
	/// </summary>
	/// <param name="numLineBreaks">Number of line breaks to add.</param>
	void AddLineBreaks(unsigned int numLineBreaks);

#pragma region Color/Coloring
	/*
	NAME            FG  BG
	Black           30  40
	Red             31  41
	Green           32  42
	Yellow          33  43
	Blue            34  44
	Magenta         35  45
	Cyan            36  46
	White           37  47
	Bright Black    90  100
	Bright Red      91  101
	Bright Green    92  102
	Bright Yellow   93  103
	Bright Blue     94  104
	Bright Magenta  95  105
	Bright Cyan     96  106
	Bright White    97  107
	*/

	/// <summary>
	/// Represents different colors.
	/// </summary>
	enum ConsoleColor
	{
		ConsoleColor_Black,
		ConsoleColor_Red,
		ConsoleColor_Green,
		ConsoleColor_Yellow,
		ConsoleColor_Blue,
		ConsoleColor_Magenta,
		ConsoleColor_Cyan,
		ConsoleColor_White,
		ConsoleColor_BrightBlack,
		ConsoleColor_BrightRed,
		ConsoleColor_BrightGreen,
		ConsoleColor_BrightYellow,
		ConsoleColor_BrightBlue,
		ConsoleColor_BrightMagenta,
		ConsoleColor_BrightCyan,
		ConsoleColor_BrightWhite
	};

	/// <summary>
	/// Determines text (foreground) color code, based on passed in 'ConsoleColor' enum.
	/// </summary>
	/// <param name="colorCode">Text (foreground) color code.</param>
	/// <returns></returns>
	std::string Get_TextColorCode(ConsoleColor colorCode);

	/// <summary>
	/// Determines background color code, based on passed in 'ConsoleColor' enum.
	/// </summary>
	/// <param name="colorCode"></param>
	/// <returns></returns>
	std::string Get_BackgroundColorCode(ConsoleColor colorCode);

	/// <summary>
	/// Prints colored text to console.
	/// </summary>
	/// <param name="textString"></param>
	/// <param name="foregroundColor">: Color of the text.</param>
	/// <param name="backgroundColor">: Color of the text's bacground.</param>
	/// <param name="addNewLineAndFlushStreamBuffer">: Should program add new line and flush buffer stream (std::endl).</param>
	void PrintTextWithColor(const char* textString, ConsoleColor foregroundColor, ConsoleColor backgroundColor = ConsoleColor_Black, bool addNewLineAndFlushStreamBuffer = false);

	/// <summary>
	/// Prints colored text to console.
	/// </summary>
	/// <param name="textString"></param>
	/// <param name="foregroundColor">: Color of the text.</param>
	/// <param name="backgroundColor">: Color of the text's bacground.</param>
	/// <param name="addNewLineAndFlushStreamBuffer">: Should program add new line and flush buffer stream (std::endl).</param>
	void PrintTextWithColor(const std::string& textString, ConsoleColor foregroundColor, ConsoleColor backgroundColor = ConsoleColor_Black, bool addNewLineAndFlushStreamBuffer = false);
#pragma endregion

	/// <summary>
	/// Prints bar console.
	/// </summary>
	/// <param name="barWidth">: Width(x) of bar.</param>
	/// <param name="barHeight">: Height(y) of bar.</param>
	/// <param name="barColor">: The bar's color.</param>
	/// <param name="endWithNewLine">: Should programm add new line at the end of bar.</param>
	void PrintBar(unsigned int barWidth, unsigned int barHeight, ConsoleColor barColor, bool endWithNewLine = true);
}