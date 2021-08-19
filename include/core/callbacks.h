#ifndef _CALLBACKS_H_
#define _CALLBACKS_H_

#include "utils.h"

void NOX_EventHandler(SDL_Event *event);
void NOX_Update(void);
void NOX_Render(SDL_Renderer *renderer);

#endif /* _CALLBACKS_H_ */
