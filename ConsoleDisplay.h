#pragma once

#include <vector>
#include <string>

using namespace std;

struct Pixel {
	char character;
	uint8_t backgroundColor;
	uint8_t foregroundColor;
};

class ConsoleDisplay {
public:
	ConsoleDisplay();
	ConsoleDisplay(int, int);
	void addGraphic(int, int, string, int);
	void addString(int, int, string, int, int);
	void drawScreen();
	void addBorder(char, int, int);
	void clearScreen();
	void clearScreenBuffer();
private:
	int screenWidth;
	int screenHeight;
	vector<vector<Pixel>> screenBuffer;
	vector<vector<Pixel>> previousFrame;
	void setConCurPosition(int, int, int, int);
};

