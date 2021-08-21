#ifndef _INIT_H_
#define _INIT_H_

/* NOX_InitSDL2
 *
 * Initialize SDL2 library, create window and renderer handlers
 */

#include "utils.h"

Uint8 NOX_InitSDL2(SDL_Window **window, SDL_Renderer **renderer, SDL_Rect window_rect, const char *title);

#endif /* _INIT_H_ */
