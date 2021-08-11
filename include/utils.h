#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/* NOX_DisplayMessage
 *
 * Display formatted message on output stream 
 * Standard -> [ Ouput = stdout | Errors = stderr ]
 */

#define NOX_LOG_FATAL 0x01u /* Flag for fatal errors */

/* Default Log Messages */
#define NOX_LOG_ERROR 0x02u
#define NOX_LOG_WARN 0x04u
#define NOX_LOG_DEBUG 0x08u
#define NOX_LOG_INFO 0x10u
/* SDL2 Log Messages */
#define NOX_LOG_SDL2_ERROR 0x20u

extern bool NOX_fatal_error;
extern FILE **NOX_current_stream;

void NOX_DisplayMessage(uint8_t flags, const char *message, ...);

#endif /* _UTILS_H_ */
