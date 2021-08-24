#include <stdarg.h>
#include <stdio.h>
#include "noxis/log.h"

#define NOX_MAX_STRING_BYTES 512

#define NOX_PREFIX_INFO      "\033[1;36m[ INFO ]\033[0m"
#define NOX_PREFIX_DEBUG     "\033[1;32m[ DEBUG ]\033[0m"
#define NOX_PREFIX_WARN      "\033[1;33m[ WARN ]\033[0m"
#define NOX_PREFIX_ERROR     "\033[1;31m[ ERROR ]\033[0m"
#define NOX_PREFIX_FATAL     "\033[0;91m[ FATAL ]\033[0m"
#define NOX_PREFIX_INVALID   "\033[1;91mInvalid log prefix\033[0m\n"

void NOX_Log(Uint8 priority, const char *format, ...)
{
	va_list args;
	char message[NOX_MAX_STRING_BYTES];
	char *prefix;
	
	va_start(args, format);
	vsprintf(message, format, args);
	
	switch (priority) {
	case NOX_LOG_INFO:
		prefix = NOX_PREFIX_INFO;
		break;
	case NOX_LOG_DEBUG:
		prefix = NOX_PREFIX_DEBUG;
		break;
	case NOX_LOG_WARN:
		prefix = NOX_PREFIX_WARN;
		break;
	case NOX_LOG_ERROR:
		prefix = NOX_PREFIX_ERROR;
		break;
	case NOX_LOG_FATAL:
		prefix = NOX_PREFIX_FATAL;
		// TODO: NOX_ForceShutdow();
		break;
	default:
		prefix = NULL;
	}
	
	if (prefix == NULL)
		fprintf(stderr, NOX_PREFIX_INVALID);
	else if (priority & NOX_LOG_ERROR)
		fprintf(stderr, "%s:\n\t%s\n", prefix, message);
	else
		fprintf(stdout, "%s:\n\t%s\n", prefix, message);
	
	va_end(args);
}
