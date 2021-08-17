#include "core/init.h"

Uint8 NOX_InitSDL2(SDL_Window **window, SDL_Renderer **renderer, SDL_Rect window_rect, const char *title)
{
	Uint32 flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS;

	if (SDL_Init(flags) != 0) {
		NOX_DisplayMessage(NOX_LOG_SDL2_ERROR, "Cannot Initialize SDL2 Library");
		return -1;
	}
	NOX_DisplayMessage(NOX_LOG_INFO, "SDL2 Library Initialized");

	flags = SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;
	*window = SDL_CreateWindow(
		title != NULL ? title : "No Title",
		window_rect.x, window_rect.y,
		window_rect.w != 0 ? window_rect.w : 800,
		window_rect.h != 0 ? window_rect.h : 600,
		flags
	);

	if (*window == NULL) {
		NOX_DisplayMessage(NOX_LOG_SDL2_ERROR, "Cannot Create Window Handler");
		return -1;
	}
	NOX_DisplayMessage(NOX_LOG_INFO, "Window Handler Created");

	flags = SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED;
	*renderer = SDL_CreateRenderer(*window, -1, flags);

	if (*renderer == NULL) {
		NOX_DisplayMessage(NOX_LOG_SDL2_ERROR, "Cannot Create Main Window Renderer");
		return -1;
	}
	NOX_DisplayMessage(NOX_LOG_INFO, "Main Window Renderer Created");

	return 0;
}
