#include "ConsoleDisplay.h"

#include <iostream>
#include <Windows.h>
#include <fstream>

using namespace std;

ConsoleDisplay::ConsoleDisplay() {
	screenWidth = 150;
	screenHeight = 50;
	bufferSize = screenWidth * screenHeight;
	screenBuffer = new CHAR_INFO[bufferSize];
	previousFrame = new CHAR_INFO[bufferSize];


	for (int i = 0; i < bufferSize; i++) {
		screenBuffer[i].Char.UnicodeChar = '+';
		screenBuffer[i].Attributes = (0 << 4 | 15);
		previousFrame[i].Char.UnicodeChar = '+';
		previousFrame[i].Attributes = (0 << 4 | 15);
	}
}

ConsoleDisplay::ConsoleDisplay(int newScreenWidth, int newScreenHeight) {
	screenWidth = newScreenWidth;
	screenHeight = newScreenHeight;
	bufferSize = screenWidth * screenHeight;
	screenBuffer = new CHAR_INFO[bufferSize];
	previousFrame = new CHAR_INFO[bufferSize];

	for (int i = 0; i < bufferSize; i++) {
		screenBuffer[i].Char.UnicodeChar = '+';
		screenBuffer[i].Attributes = (0 << 4 | 15);
		previousFrame[i].Char.UnicodeChar = '+';
		previousFrame[i].Attributes = (0 << 4 | 15);
	}
}

void ConsoleDisplay::addGraphic(int graphicX, int graphicY, string fileName, int graphicForegroundColor, int graphicBackgroundColor) {

	if (!(graphicX >= 0 && graphicY >= 0)) {
		throw runtime_error("addGraphic command incorrect, graphicX: " + to_string(graphicX) + " graphicY: " + to_string(graphicY));
	}

	int graphicWidth;
	int graphicHeight;

	ifstream fileInput;

	fileInput.open(fileName);

	if (!fileInput.is_open()) {
		throw runtime_error("Graphic file not found: " + fileName);
	}

	fileInput >> graphicWidth >> graphicHeight;

	if (!(graphicWidth > 0 && graphicHeight > 0)) {
		throw runtime_error("Graphic file header incorrect, graphicWidth: " + to_string(graphicWidth) + " graphicHeight: " + to_string(graphicHeight));
	}

	char tempChar;

	for (int y = graphicY; y < (graphicY + graphicHeight); y++) {
		for (int x = graphicX; x < (graphicX + graphicWidth); x++) {
			tempChar = fileInput.get();
			if (tempChar == '\n') {
				tempChar = fileInput.get();
			}
			if (tempChar != ' ') {
				screenBuffer[y * screenWidth + x].Char.UnicodeChar = tempChar;
				screenBuffer[y * screenWidth + x].Attributes = (graphicBackgroundColor << 4 | graphicForegroundColor);
			}
		}
	}
}

void ConsoleDisplay::addString(int stringX, int stringY, string inputString, int stringForegroundColor, int stringBackgroundColor) {
	for (int x = 0; x < inputString.size(); x++) {
		screenBuffer[stringY * screenWidth + (stringX + x)].Char.UnicodeChar = inputString[x];
		screenBuffer[stringY * screenWidth + (stringX + x)].Attributes = (stringBackgroundColor << 4 | stringForegroundColor);
	}
}

void ConsoleDisplay::drawScreen() {
	
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	if (console == INVALID_HANDLE_VALUE || console == NULL) {
		throw runtime_error("Console handle is invalid!");
	}

	CHAR_INFO* screenBufferPtr = screenBuffer;
	COORD screenSize{ screenWidth, screenHeight };
	SMALL_RECT* screenRect = new SMALL_RECT{ 0,0,SHORT(screenWidth - 1),SHORT(screenHeight - 1) };

	WriteConsoleOutputW(console, screenBufferPtr, screenSize, { 0,0 }, screenRect);

	for (int i = 0; i < bufferSize; i++) {
		previousFrame[i] = screenBuffer[i];
	}
}

void ConsoleDisplay::addBorder(char borderChar, int borderForegroundColor, int borderBackgroundColor) {
	for (int y = 0; y < screenHeight; y++) {
		for (int x = 0; x < screenWidth; x++) {
			if (y == 0 || y == (screenHeight - 1)) {
				screenBuffer[y * screenWidth + x].Char.UnicodeChar = borderChar;
				screenBuffer[y * screenWidth + x].Attributes = (borderBackgroundColor << 4 | borderForegroundColor);
			}
			if (x == 0 || x == (screenWidth - 1)) {
				screenBuffer[y * screenWidth + x].Char.UnicodeChar = borderChar;
				screenBuffer[y * screenWidth + x].Attributes = (borderBackgroundColor << 4 | borderForegroundColor);
			}
		}
	}
}

void ConsoleDisplay::clearScreen() {
	clearScreenBuffer();
	drawScreen();
}

void ConsoleDisplay::clearScreenBuffer() {
	for (int i = 0; i < bufferSize; i++) {
		screenBuffer[i].Char.UnicodeChar = ' ';
		screenBuffer[i].Attributes = (0 << 4 | 15);
	}
}

void ConsoleDisplay::setConCurPosition(int conX, int conY, int conForegroundColor, int conBackgroundColor) {
	if (!(conX >= 0 && conY >= 0 && conX < screenWidth && conY < screenHeight)) {
		throw runtime_error("Console cursor position out of range, x:" + to_string(conX) + " y:" + to_string(conY));
	}

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	if (console == INVALID_HANDLE_VALUE || console == NULL) {
		throw runtime_error("Console handle is invalid!");
	}

	COORD conCoords = { static_cast<SHORT>(conX), static_cast<SHORT>(conY) };
	SetConsoleTextAttribute(console, conForegroundColor);
	SetConsoleCursorPosition(console, conCoords);
}

void ConsoleDisplay::addRect(int cornerX, int cornerY, int rectWidth, int rectHeight, bool solid, char rectChar, int rectForegroundColor, int rectBackgroundColor) {
	
	if ((cornerX < 0 || cornerX > screenWidth) || (cornerY < 0 || cornerX > screenHeight)) {
		throw runtime_error("Rectangle origin not in bounds! (" + to_string(cornerX) + ", " + to_string(cornerY) + ")");
	}
	if (((cornerX + rectWidth) > screenWidth) || ((cornerY + rectHeight) > screenHeight)) {
		throw runtime_error("Rectangle is too large for screen! Width: " + to_string(rectWidth) + " Height: " + to_string(rectHeight) + " Corner at (" + to_string(cornerX) + ", " + to_string(cornerY) + ")");
	}

	if (solid) {
		for (int y = cornerY; y < (cornerY + rectHeight); y++) {
			for (int x = cornerX; x < (cornerX + rectWidth); x++) {
				screenBuffer[y * screenWidth + x].Char.UnicodeChar = rectChar;
				screenBuffer[y * screenWidth + x].Attributes = (rectBackgroundColor << 4 | rectForegroundColor);
			}
		}
	}
	else {
		for (int y = cornerY; y < (cornerY + rectHeight); y++) {
			for (int x = cornerX; x < (cornerX + rectWidth); x++) {
				if (y == cornerY || y == (cornerY + rectHeight - 1)) {
					screenBuffer[y * screenWidth + x].Char.UnicodeChar = rectChar;
					screenBuffer[y * screenWidth + x].Attributes = (rectBackgroundColor << 4 | rectForegroundColor);
				}
				if (x == cornerX || x == (cornerX + rectWidth - 1)) {
					screenBuffer[y * screenWidth + x].Char.UnicodeChar = rectChar;
					screenBuffer[y * screenWidth + x].Attributes = (rectBackgroundColor << 4 | rectForegroundColor);
				}
			}
		}
	}
}

void ConsoleDisplay::addLine(int x1, int y1, int x2, int y2, char lineChar, int lineForegroundColor, int lineBackgroundColor) {

	if (x1 < 0 || x1 > (screenWidth - 1) || y1 < 0 || y1 > (screenHeight - 1) || x2 < 0 || x2 > (screenWidth - 1) || y2 < 0 || y2 > (screenHeight - 1)) {
		throw runtime_error("Line is out of bounds! Point 1: (" + to_string(x1) + +", " + to_string(y1) + ") Point 2: " + to_string(x2) + +", " + to_string(y2) + ")");
	}

	int diffX = abs(x2 - x1);
	int diffY = -abs(y2 - y1);
	int error = diffY + diffX;

	int stepX, stepY;
	if (x1 < x2) { stepX = 1; }
	else { stepX = -1; }

	if (y1 < y2) { stepY = 1; }
	else { stepY = -1; }

	while (!(x1 == x2 && y1 == y2)) {
		screenBuffer[y1 * screenWidth + x1].Char.UnicodeChar = lineChar;
		screenBuffer[y1 * screenWidth + x1].Attributes = (lineBackgroundColor << 4 | lineForegroundColor);
		if ((2 * error) >= diffY) {
			if (x1 != x2) {
				error += diffY;
				x1 += stepX;
			}
		}
		if ((2 * error) <= diffX) {
			if (y1 != y2) {
				error += diffX;
				y1 += stepY;
			}
		}
	}
}