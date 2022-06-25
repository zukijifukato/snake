#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL_ttf.h>

class Text {
	public:
		Text(SDL_Renderer* renderer, const char* fontPath, const char* text, int size, const SDL_Color &color);
		~Text();

		void render(SDL_Renderer* renderer, int x, int y);

		static SDL_Texture *loadFont(SDL_Renderer* renderer, const char* fontPath, const char* text, int size, const SDL_Color &color);
	private:
		SDL_Texture* textTexture = nullptr;
		SDL_Rect textRect;
};

#endif