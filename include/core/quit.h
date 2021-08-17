#ifndef _QUIT_H_
#define _QUIT_H_

/* NOX_QuitSDL2
 *
 * Destroy SDL2 objects and uninitialize library
 */

#include "utils.h"

void NOX_QuitSDL2(SDL_Window **window, SDL_Renderer **renderer);

#endif /* _QUIT_H_ */
