#ifndef _NOX_CORE_H_
#define _NOX_CORE_H_

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct NOX_Setup {
	const char *title;
	SDL_Rect window;
	
	struct {
		void (*handleEvents)(SDL_Event *);
		void (*update)(void);
		void (*render)(SDL_Renderer *);
	} callbacks;
} NOX_Setup_t;

/* NOX_Run
 *
 */
bool NOX_Run(NOX_Setup_t setup);

/* NOX_ForceShutdown
 *
 */
void NOX_ForceShutdown(void);

#endif /* _NOX_CORE_H_ */
