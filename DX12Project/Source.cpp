#include <iostream>
#include <chrono>
#include <thread>

#include <d3d12.h>
#include <dxgi1_6.h>

#include "Window.h"

int main() {
	const int targetFPS = 70;
	const std::chrono::milliseconds frameDuration(1000 / targetFPS);

	Window window(L"DX12 Project", 800, 600);

	bool quit = false;

	auto lastFrameTime = std::chrono::high_resolution_clock::now();
	while (!quit) {
		auto startTime = std::chrono::high_resolution_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(startTime - lastFrameTime);
		lastFrameTime = startTime;

		quit = window.handleMessages();

		auto endTime = std::chrono::high_resolution_clock::now();
		elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
		auto sleepTime = frameDuration - elapsedTime;

		if (sleepTime > std::chrono::milliseconds::zero()) {
			std::this_thread::sleep_for(sleepTime);
		}
	}

	return 0;
}