#include "Core.h"
#include "GameObject.cpp"
#include "Text.h"

Snake snake;
Food food;

Text* stext = nullptr;
Text* htext = nullptr;

uint32_t previous_time, current_time = 0, delay_time = 0;

Core::Core() {
	printf("Core starting!\n");
}

Core::~Core() {
	printf("Core exiting!\n");
}

void Core::init(const char* title, int xpos, int ypos, int width, int height, uint32_t flags) {
	srand(time(0));
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("Could not initialize SDL!\n");
		isRunning = false;
	} else {
		if(TTF_Init() < 0) {
			printf("Could not initialize TTF!\n");
			isRunning = false;
		}
		SDL_Window* window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window == nullptr) {
			printf("Window could not be created!\n");
			isRunning = false;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

		if(renderer == nullptr) {
			printf("Renderer could not be created!\n");
			isRunning = false;
		}

		FILE* file;
		if(file = fopen("config", "r")) {
			fscanf(file, "%d", &highscore);
			fclose(file);
		}

		isRunning = true;
	}
}

void Core::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
		 	if(event.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
				break;
			} else if(event.key.keysym.sym == SDLK_UP) {
				if(snake.vel_y == 1) break;
				snake.vel_y = -1;
				snake.vel_x = 0;
				break;
			} else if(event.key.keysym.sym == SDLK_DOWN) {
				if(snake.vel_y == -1) break;
				snake.vel_y = 1;
				snake.vel_x = 0;
				break;
			} else if(event.key.keysym.sym == SDLK_LEFT) {
				if(snake.vel_x == 1) break;
				snake.vel_y = 0;
				snake.vel_x = -1;
				break;
			} else if(event.key.keysym.sym == SDLK_RIGHT) {
				if(snake.vel_x == -1) break;
				snake.vel_y = 0;
				snake.vel_x = 1;
				break;
			}
		default:
			break;
	}
}

void Core::update() {
	previous_time = current_time;
	current_time = SDL_GetTicks();
	delay_time = current_time - previous_time;
	snake.update(delay_time, food);
	if(snake.tailLength == -1) {
		// isRunning = false;
		snake.reset();
	} else {
		score = snake.tailLength - 1;
		if(score > highscore) {
			highscore = score;
		}
	}
}

void Core::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	char s_text[100] = "Score: ";
	char h_text[100] = " | Highscore: ";
	stext = new Text(renderer, "./assets/fonts/arial.ttf", strcat(strcat(s_text, std::to_string(score).c_str()), strcat(h_text, std::to_string(highscore).c_str())), 24, {255,255,255,50});
	stext->render(renderer, 220, 0);
	snake.render(renderer);
	food.render(renderer);
	SDL_RenderPresent(renderer);
}

void Core::clean() {
	window = nullptr;
	renderer = nullptr;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

	FILE* file;
	if(file = fopen("config", "w")) {
		fprintf(file, "%d", highscore);
	}
	fclose(file);
}