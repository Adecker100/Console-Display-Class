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
				screenBuffer[y * screenWidth + x].Attributes = (0 << 4 | 15);
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
				screenBuffer[y * screenWidth + x].Attributes = (0 << 4 | 15);
			}
			if (x == 0 || x == (screenWidth - 1)) {
				screenBuffer[y * screenWidth + x].Char.UnicodeChar = borderChar;
				screenBuffer[y * screenWidth + x].Attributes = (0 << 4 | 15);
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
