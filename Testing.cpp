#include "ConsoleDisplay.h"
#include "Windows.h"
#include <iostream>
#include <vector>

int main() {
	const int8_t screenWidth = 100;
	const int8_t screenHeight = 100;
	CHAR_INFO screenBuffer[screenWidth * screenHeight];

	for (int y = 0; y < screenHeight; y++) {
		for (int x = 0; x < screenWidth; x++) {
			screenBuffer[y * screenWidth + x].Char.UnicodeChar = 'x';
			screenBuffer[y * screenWidth + x].Attributes = (10 << 4 | 15);
		}
	}

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CHAR_INFO* screenBufferPtr = screenBuffer;
	COORD screenSize{ screenWidth, screenHeight };
	SMALL_RECT* screenRect = new SMALL_RECT{ 0,0,(screenWidth - 1),(screenHeight -1) };

	WriteConsoleOutputW(console, screenBufferPtr, screenSize, { 0,0 }, screenRect);

}