#ifndef _NOX_DEBUG_H_
#define _NOX_DEBUG_H_

#include <SDL2/SDL_stdinc.h>

/* Log Flags */
#define NOX_LOG_INFO  0x01u
#define NOX_LOG_WARN  0x02u
#define NOX_LOG_DEBUG 0x04u
#define NOX_LOG_ERROR 0x08u
#define NOX_LOG_FATAL 0x10u

/* NOX_Log
 *
 * Display messages in stdout, and errors messages in stderr
 */
void NOX_Log(Uint8, const char *, ...);

#endif /* _NOX_DEBUG_H_ */
