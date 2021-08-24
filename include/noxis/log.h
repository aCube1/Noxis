#ifndef _NOX_LOG_H_
#define _NOX_LOG_H_

#include <SDL2/SDL.h>

/* Log Priorities */
#define NOX_LOG_INFO  0x01
#define NOX_LOG_DEBUG 0x02
#define NOX_LOG_WARN  0x04
#define NOX_LOG_ERROR 0x08
#define NOX_LOG_FATAL 0x10

/* NOX_Log
 *
 * Display message on stdout by default and errors
 * messages in stderr
 */
void NOX_Log(Uint8 priority, const char *format, ...);

#endif /* _NOX_LOG_H_ */
