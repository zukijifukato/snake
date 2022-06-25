#ifndef CORE_H
#define CORE_H

#include <SDL2/SDL.h>
#include <time.h>
#include <string>
#include <stdio.h>

class Core {
	public:
		Core();
		~Core();

		void init(const char* title, int xpos, int ypos, int width, int height, uint32_t flags);
		void handleEvents();
		void update();
		void render();
		void clean();

		bool running() {
			return isRunning;
		}
	private:
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		bool isRunning = true;
		int score = 0, highscore = 0;
};

#endif