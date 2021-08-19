#ifndef _UTILS_H_
#define _UTILS_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

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

void NOX_DisplayMessage(Uint8 flags, const char *message, ...);

/* Geters | Seters */
bool NOX_HasFatalError(void);
bool NOX_IsRunning(void);
SDL_Rect NOX_GetWindowRect(void);
Uint32 NOX_GetFPS(void);

void NOX_UpdateFPS(void);

/* Event Handlers */
void NOX_QuitHandler(void);
void NOX_WindowHandler(const SDL_WindowEvent window);

#endif /* _UTILS_H_ */
