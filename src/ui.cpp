#include "SDL/SDL_ttf.h"
#include "ui.hpp"
#include "level_utils.hpp"

static SDL_Color white = {0xff, 0xff, 0xff, 0xff};

int init_sdl (void) {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	font = TTF_OpenFont("../img/FreeSans.ttf",
			15);

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
			SDL_SWSURFACE);
}

void teardown_sdl (void) {
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}

int show_screen (char **message, int dur) {
	SDL_FillRect(screen, NULL, 0);

	int line = 0;
	while (*message) {
		SDL_Surface *text = TTF_RenderText_Solid(font, *message, white);
		apply_surface(text, screen, 15, 15 + line * 15, NULL);
		line++;
		message++;
	}
	SDL_Flip(screen);

	SDL_Event event;
	bool end = false;
	Uint32 start_time = SDL_GetTicks();
	while (!end) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				return -1;
			/* hidden feature: spacebar to skip any screen,
			 * regardless of timer */
			if (event.type == SDL_KEYDOWN) {
				if ((SDL_GetTicks() - start_time > dur) ||
					(event.key.keysym.sym == SDLK_SPACE))
					end = true;
				break;
			}
		}
	}

	return 0;
}
