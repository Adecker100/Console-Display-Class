#pragma once

#include <Windows.h>
#include <vector>
#include <string>

using namespace std;

class ConsoleDisplay {
public:
	ConsoleDisplay();
	ConsoleDisplay(int newScreenWidth, int newScreenHeight);
	void addGraphic(int graphicX, int graphicY, string fileName, int graphicForegroundColor, int graphicBackgroundColor);
	void addString(int stringX, int stringY, string inputString, int stringForegroundColor, int stringBackgroundColor);
	void drawScreen();
	void addBorder(char borderChar, int borderForegroundColor, int borderBackgroundColor);
	void clearScreen();
	void clearScreenBuffer();
	void setConCurPosition(int conX, int conY, int conForegroundColor, int conBackgroundColor);
	void addRect(int cornerX, int cornerY, int rectWidth, int rectHeight, bool solid, char rectChar, int rectForegroundColor, int rectBackgroundColor);
	void addLine(int x1, int y1, int x2, int y2, char lineChar, int lineForegroundColor, int lineBackgroundColor);
private:
	int screenWidth;
	int screenHeight;
	int bufferSize;
	CHAR_INFO* screenBuffer = nullptr;
	CHAR_INFO* previousFrame = nullptr;
};

