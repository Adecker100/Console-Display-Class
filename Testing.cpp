#include "ConsoleDisplay.h"
#include "Windows.h"
#include <iostream>
#include <random>
#include <vector>
#include <chrono>

int main() {
	try {
		ConsoleDisplay screen1(150, 50);

		random_device seed;
		mt19937 gen(seed());
		uniform_int_distribution<int> characterRange(65, 120);
		uniform_int_distribution<int> coordXRange(0, 149);
		uniform_int_distribution<int> coordYRange(0, 49);
		uniform_int_distribution<int> colorRange(0, 15);

		std::chrono::time_point<std::chrono::steady_clock> lastFrameTime = std::chrono::steady_clock::now();

		int framesPerSecond = 0;
		int frames = 0;
		int ghy;
		std::cin >> ghy;
		screen1.clearScreenBuffer();
		while (true) {
			/*
			for (int y = 0; y < 50; y++) {
				for (int x = 0; x < 150; x++) {
					char tempChar = characterRange(gen);
					string tempStr = tempChar + "";
					screen1.addString(x, y, tempStr, colorRange(gen), colorRange(gen));
					screen1.drawScreen();

				}
			}
			*/

			screen1.addLine(coordXRange(gen), coordYRange(gen), coordXRange(gen), coordYRange(gen), ' ', colorRange(gen), colorRange(gen));
			screen1.addString(80, 40, "FPS:" + to_string(framesPerSecond), 0, 15);
			screen1.drawScreen();
			frames++;
			if (std::chrono::steady_clock::now() - lastFrameTime >= std::chrono::duration<int>(1)) {
				framesPerSecond = frames;
				frames = 0;
				lastFrameTime = std::chrono::steady_clock::now();
			}
		}
	}
	catch (runtime_error& excpt) {
		cout << excpt.what() << endl;
	}
}