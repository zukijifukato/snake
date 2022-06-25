#include "Text.h"

Text::Text(SDL_Renderer* renderer, const char* fontPath, const char* text, int size, const SDL_Color &color) {
	textTexture = loadFont(renderer, fontPath, text, size, color);
	SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
}

Text::~Text() {
	//
}

void Text::render(SDL_Renderer* renderer, int x, int y) {
	textRect.x = x;
	textRect.y = y;
	SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
}

SDL_Texture* Text::loadFont(SDL_Renderer* renderer, const char* fontPath, const char* text, int size, const SDL_Color &color) {
	TTF_Font* font = TTF_OpenFont(fontPath, size);
	if(!font) {
		printf("Error loading font!\n");
	}
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
	if(!textSurface) {
		printf("Error creating text surface!\n");
	}
	SDL_Texture* textTex = SDL_CreateTextureFromSurface(renderer, textSurface);
	if(!textTex) {
		printf("Error creating text texture!\n");
	}
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
	return textTex;
}