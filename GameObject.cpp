class Food {
	public:
		int x = 5, y = 5;

		void update() {
			x = rand() % (640 / 10);
			y = rand() % (480 / 10);
		}

		void render(SDL_Renderer* renderer) {
			SDL_Rect r{x * 10, y * 10, 10, 10};
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &r);
		}
};

class Snake {
	public:
		int w = 10, h = 10;
		int vel_x = 1, vel_y = 0;
		uint32_t frameCounter = 0;
		int tailLength = 1;
		int temptailLength;
		int tempX, tempY;
		int tailX[100] = {0};
		int tailY[100] = {0};

		void reset() {
			std::fill_n(tailX, 100, 0);
			std::fill_n(tailY, 100, 0);
			tailLength = 1;
			vel_x = 1;
			vel_y = 0;
		}
 
		void update(uint32_t delay_time, Food& food) {
			frameCounter += delay_time;
			if(frameCounter > 80) {
				frameCounter = 0;
				for(int i=tailLength-1; i>0;--i) {
					tailX[i] = tailX[i-1];
					tailY[i] = tailY[i-1];
				}
				tailX[0] += vel_x;
				tailY[0] += vel_y;
			}

			if(tailX[0] >= 64) {
				tailX[0] = 0;
			}

			if(tailY[0] >= 48) {
				tailY[0] = 0;
			}

			if(tailX[0] < 0) {
				tailX[0] = 63;
			}

			if(tailY[0] < 0) {
				tailY[0] = 47;
			}

			if((tailX[0] == food.x) && (tailY[0] == food.y)) {
				tailLength++;
				for(int i=tailLength-1; i>0;--i) {
					tailX[i] = tailX[i-1];
					tailY[i] = tailY[i-1];
				}
				tailX[0] += vel_x;
				tailY[0] += vel_y;
				food.update();
			}

			for(int i=2; i<tailLength; i++) {
				if((tailX[0] == tailX[i]) && tailY[0] == tailY[i]) {
					temptailLength = tailLength;
					tailLength = -1;
				}
			}
		}

		void render(SDL_Renderer* renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			for(int i=0; i<tailLength; i++) {
				SDL_Rect r{tailX[i] * 10, tailY[i] * 10, w, h};
				SDL_RenderFillRect(renderer, &r);
			}
		}
};