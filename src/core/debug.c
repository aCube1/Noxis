#include "core/debug.h"

#include <stdio.h>
#include <stdarg.h>
#include "core/setup.h"

#define MAX_LOG_MESSAGE 1024

#define NOX_PREFIX_INFO    "\033[1;36m[ INFO ]\033[0m"
#define NOX_PREFIX_WARN    "\033[1;33m[ WARN ]\033[0m"
#define NOX_PREFIX_DEBUG   "\033[1;32m[ DEBUG ]\033[0m"
#define NOX_PREFIX_ERROR   "\033[1;31m[ ERROR ]\033[0m"
#define NOX_PREFIX_FATAL   "\033[0;91m[ FATAL ]\033[0m"
#define NOX_PREFIX_INVALID "\033[1;91m[ INVALID LOG FLAG ]\033[0m\n"

void NOX_Log(Uint8 log_flag, const char *format, ...)
{
	va_list args;
	char *prefix, message[MAX_LOG_MESSAGE];

	va_start(args, format);
	vsprintf(message, format, args);

	switch (log_flag) {
	case NOX_LOG_INFO:
		prefix = NOX_PREFIX_INFO; break;
	case NOX_LOG_WARN:
		prefix = NOX_PREFIX_WARN; break;
	case NOX_LOG_DEBUG:
		prefix = NOX_PREFIX_DEBUG; break;
	case NOX_LOG_ERROR:
		prefix = NOX_PREFIX_ERROR; break;
	case NOX_LOG_FATAL:
		prefix = NOX_PREFIX_FATAL; break;
	default:
		prefix = NULL;
		break;
	}

	if (log_flag & NOX_LOG_ERROR) {
		fprintf(stderr, "%s:\n\t%s\n", prefix, message);
		if (log_flag & NOX_LOG_FATAL)
			NOX_ForceShutdown();
	}
#ifdef NOX_DEBUG
	else if (prefix == NULL)
		fprintf(stderr, NOX_PREFIX_INVALID);
	else
		fprintf(stdout, "%s:\n\t%s\n", prefix, message);
#endif /* NOX_DEBUG */
}
