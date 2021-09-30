#ifndef _NOX_CORE_H_
#define _NOX_CORE_H_

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct NOX_Setup {
	const char *title;
	SDL_Rect window;

	struct {
		void (*HandleEvents)(SDL_Event);
		void (*Update)(void);
		void (*Render)(SDL_Renderer *);
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
