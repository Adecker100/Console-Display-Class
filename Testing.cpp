#include "ConsoleDisplay.h"
#include "Windows.h"
#include <iostream>
#include <random>
#include <vector>
#include <chrono>

int main() {

	ConsoleDisplay screen1(150, 50);

	random_device seed;
	mt19937 gen(seed());
	uniform_int_distribution<int> characterRange(65, 120);
	uniform_int_distribution<int> colorRange(0, 15);

	std::chrono::time_point<std::chrono::steady_clock> lastFrameTime = std::chrono::steady_clock::now();

	int framesPerSecond = 0;
	int frames = 0;
	while (true) {
		/*
		for (int y = 0; y < 50; y++) {
			for (int x = 0; x < 150; x++) {
				char tempChar = characterRange(gen);
				string tempStr = tempChar + "";
				screen1.addString(x, y, tempStr, 15, 0);
			}
		}
		*/
		screen1.addString(20, 10, "FPS:" + to_string(framesPerSecond), 0, 15);
		screen1.drawScreen();
		frames++;
		if (std::chrono::steady_clock::now() - lastFrameTime >= std::chrono::duration<int>(1)) {
			framesPerSecond = frames;
			frames = 0;
			lastFrameTime = std::chrono::steady_clock::now();
		}
	}
}