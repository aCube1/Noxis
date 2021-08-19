#include "core/callbacks.h"

void NOX_EventHandler(SDL_Event *event)
{
	while (SDL_PollEvent(event)) {
		switch (event->type) {
			case SDL_QUIT:
				NOX_QuitHandler();
				break;
			case SDL_WINDOWEVENT:
				NOX_WindowHandler(event->window);
				break;
			default:
				break;
		}
	}
}

void NOX_Update(void) {
	NOX_UpdateFPS();
}

void NOX_Render(SDL_Renderer *renderer)
{
	SDL_RenderClear(renderer);
	/* Draw Something Here */
	SDL_RenderPresent(renderer);
}
