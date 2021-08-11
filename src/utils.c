#include "utils.h"

#include <stdarg.h>
#include <string.h>
#include <SDL2/SDL.h>
//#include "stb_image.h"

bool NOX_fatal_error = false;
FILE **NOX_current_stream = &stdout;

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

void NOX_DisplayMessage(uint8_t flags, const char *message, ...)
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
