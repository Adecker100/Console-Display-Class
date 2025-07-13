#include "ConsoleDisplay.h"

#include <iostream>
#include <Windows.h>
#include <fstream>

using namespace std;

ConsoleDisplay::ConsoleDisplay() {
	screenWidth = 150;
	screenHeight = 50;
	screenBuffer.resize(screenWidth);
	previousFrame.resize(screenWidth);


	for (int x = 0; x < screenBuffer.size(); x++) {
		screenBuffer.at(x).resize(screenHeight, Pixel{ '+', 15 });
		previousFrame.at(x).resize(screenHeight, Pixel{ ' ', 15 });
	}
}

ConsoleDisplay::ConsoleDisplay(int newScreenWidth, int newScreenHeight) {
	screenWidth = newScreenWidth;
	screenHeight = newScreenHeight;
	screenBuffer.resize(screenWidth);
	previousFrame.resize(screenWidth);

	for (int x = 0; x < screenBuffer.size(); x++) {
		screenBuffer.at(x).resize(screenHeight, Pixel{ '+', 15 });
		previousFrame.at(x).resize(screenHeight, Pixel{ ' ', 15 });
	}
}

void ConsoleDisplay::addGraphic(int graphicX, int graphicY, string fileName, int graphicColor) {

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
				screenBuffer.at(x).at(y).character = tempChar;
				screenBuffer.at(x).at(y).foregroundColor = graphicColor;
			}
		}
	}
}

void ConsoleDisplay::addString(int stringX, int stringY, string inputString, int stringBackgroundColor, int stringForegroundColor) {
	for (int x = 0; x < inputString.size(); x++) {
		screenBuffer.at(stringX + x).at(stringY).character = inputString[x];
		screenBuffer.at(stringX + x).at(stringY).foregroundColor = stringForegroundColor;
		screenBuffer.at(stringX + x).at(stringY).foregroundColor = stringBackgroundColor;
	}
}

void ConsoleDisplay::drawScreen() {
	for (int y = 0; y < screenHeight; y++) {
		for (int x = 0; x < screenWidth; x++) {
			if (screenBuffer.at(x).at(y).character != previousFrame.at(x).at(y).character || screenBuffer.at(x).at(y).foregroundColor != previousFrame.at(x).at(y).foregroundColor) {
				setConCurPosition(x, y, screenBuffer.at(x).at(y).foregroundColor, 69);
				cout << screenBuffer.at(x).at(y).character;
			}
		}
	}
	for (int y = 0; y < screenHeight; y++) {
		for (int x = 0; x < screenWidth; x++) {
			previousFrame.at(x).at(y) = screenBuffer.at(x).at(y);
		}
	}
}

void ConsoleDisplay::addBorder(char borderChar, int borderForegroundColor, int borderBackgroundColor) {
	for (int y = 0; y < screenHeight; y++) {
		for (int x = 0; x < screenWidth; x++) {
			if (y == 0 || y == (screenHeight - 1)) {
				screenBuffer.at(x).at(y).character = borderChar;
				screenBuffer.at(x).at(y).foregroundColor = borderForegroundColor;
			}
			if (x == 0 || x == (screenWidth - 1)) {
				screenBuffer.at(x).at(y).character = borderChar;
				screenBuffer.at(x).at(y).foregroundColor = borderForegroundColor;
			}
		}
	}
}

void ConsoleDisplay::clearScreen() {
	clearScreenBuffer();
	drawScreen();
}

void ConsoleDisplay::clearScreenBuffer() {
	for (int x = 0; x < screenBuffer.size(); x++) {
		for (int y = 0; y < screenBuffer.at(x).size(); y++) {
			screenBuffer.at(x).at(y) = Pixel{ ' ', 15 };
		}
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
