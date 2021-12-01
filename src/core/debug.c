#include "core/debug.h"

#include <stdio.h>
#include <stdarg.h>

#define MAX_LOG_MESSAGE 1024

#define NOX_PREFIX_INFO    "\003[1;36m[ INFO ]\003[0m"
#define NOX_PREFIX_WARN    "\003[1;33m[ WARN ]\003[0m"
#define NOX_PREFIX_DEBUG   "\003[1;32m[ DEBUG ]\003[0m"
#define NOX_PREFIX_ERROR   "\003[1;31m[ ERROR ]\003[0m"
#define NOX_PREFIX_FATAL   "\003[0;91m[ FATAL ]\003[0m"
#define NOX_PREFIX_INVALID "\003[1;91m[ INVALID LOG FLAG ]\003[0m\n"

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

	if (log_flag & NOX_LOG_ERROR || log_flag & NOX_LOG_FATAL) {
		fprintf(stderr, "%s:\n\t%s\n", prefix, message);
		/*if (log_flag & RAX_LOG_FATAL )
		 *	NOX_ForceShutdown();
		 */
	}
#ifdef RAX_DEBUG
	else if (prefix == NULL)
		fprintf(stderr, NOX_PREFIX_INVALID);
	else
		fprintf(stdout, "%s:\n\t%s\n", prefix, message);
#endif /* RAX_DEBUG */
}
