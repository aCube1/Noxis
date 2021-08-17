#include "core/quit.h"

void NOX_QuitSDL2(SDL_Window **window, SDL_Renderer **renderer)
{
	if (*renderer != NULL) {
		SDL_DestroyRenderer(*renderer);
		NOX_DisplayMessage(NOX_LOG_INFO, "Main Window Renderer Destroyed");
	}

	if (*window != NULL) {
		SDL_DestroyWindow(*window);
		NOX_DisplayMessage(NOX_LOG_INFO, "Window Handler Destroyed");
	}

	SDL_Quit();
	NOX_DisplayMessage(NOX_LOG_INFO, "SDL2 Library Uninitialized");
}
