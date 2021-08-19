#include "utils.h"

#include <stdarg.h>
#include <string.h>
#include <SDL2/SDL.h>
//#include "stb_image.h"

static bool NOX_fatal_error = false;
static bool NOX_is_running = true;
static Uint32 NOX_fps = 0;
static SDL_Rect NOX_window_rect = {0, 0, 800, 600};

/* NOTE: Log defines */
#define NOX_MAX_STRING_BYTES 512

/* NOTE: Fatal errors will close the aplicattion */
#define NOX_PREFIX_FATAL "\033[0;91m[ FATAL ]\033[0m"

/* Default prefixes */
#define NOX_PREFIX_ERROR "\033[1;31m[ ERROR ]\033[0m"
#define NOX_PREFIX_WARN "\033[1;33m[ WARN ]\033[0m"
#define NOX_PREFIX_DEBUG "\033[1;32m[ DEBUG ]\033[0m"
#define NOX_PREFIX_INFO "\033[1;36m[ INFO ]\033[0m"
/* SDL2 prefixes */
#define NOX_PREFIX_SDL2_ERROR "\033[4;31m[ SDL2 ERROR ]\033[0m"

void NOX_DisplayMessage(Uint8 flags, const char *message, ...)
{
	va_list arg_list;
	char current_message[NOX_MAX_STRING_BYTES] = {0};
	char current_prefix[64] = {0};

	va_start(arg_list, message);
	vsprintf(current_message, message, arg_list);

	/* TODO: Code optimization needed */
	if (flags & (NOX_LOG_ERROR | NOX_LOG_SDL2_ERROR)) {
		if (flags & NOX_LOG_FATAL) {
			strcpy(current_prefix, NOX_PREFIX_FATAL);
			NOX_fatal_error = true;
		}

		strcat(current_prefix, flags & NOX_LOG_ERROR ? NOX_PREFIX_ERROR : NOX_PREFIX_SDL2_ERROR);

		if (flags & NOX_LOG_ERROR) {
			fprintf(stderr, "%s:\n\t%s\n", current_prefix, current_message);
		} else {
			fprintf(stderr, "%s:\n\t%s: %s\n", current_prefix, current_message, SDL_GetError());
		}
	} else if (flags & (NOX_LOG_WARN | NOX_LOG_DEBUG | NOX_LOG_INFO)) {
		strcpy(current_prefix, flags & NOX_LOG_WARN ? NOX_PREFIX_WARN : ( flags & NOX_LOG_DEBUG ? NOX_PREFIX_DEBUG : NOX_PREFIX_INFO));

		fprintf(stdout, "%s:\n\t%s\n", current_prefix, current_message);
	} else {
		fprintf(stderr, "\033[1;91mInvalid log prefix\033[0m\n");
	}

	va_end(arg_list);
}

bool NOX_IsRunning(void) { return NOX_is_running; }
bool NOX_HasFatalError(void) { return NOX_fatal_error; }
SDL_Rect NOX_GetWindowRect(void) { return NOX_window_rect; }
Uint32 NOX_GetFPS(void) { return NOX_fps; }

void NOX_UpdateFPS(void)
{
	static Uint32 last_time = 0;
	static Uint32 fps_accumulator = 0;
	static double fps_timer = 0;

	fps_accumulator++;
	fps_timer += (SDL_GetTicks() - last_time) / 1000.0f;
	if (fps_timer >= 1.0f) {
		NOX_fps = fps_accumulator;
		fps_accumulator = 0;
		fps_timer = 0;
	}

	last_time = SDL_GetTicks();
}


void NOX_QuitHandler(void)
{
	NOX_is_running = false;
}

void NOX_WindowHandler(SDL_WindowEvent window)
{
	static Uint32 last_timestamp = 0;
	(void)last_timestamp; /* Fix Unused Params Warn */

	switch (window.event) {
		case SDL_WINDOWEVENT_RESIZED: /* FALLTHROUGHT */
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			NOX_window_rect.w = window.data1;
			NOX_window_rect.h = window.data2;

			NOX_DisplayMessage(NOX_LOG_DEBUG, "Window Resized: %i x %i", NOX_window_rect.w, NOX_window_rect.h);
			break;
		default:
			break;
	}

	last_timestamp = window.timestamp;
}
