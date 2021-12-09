#ifndef _NOX_SCENE_MANAGER_H_
#define _NOX_SCENE_MANAGER_H_

#include <stdbool.h>
#include <SDL2/SDL_render.h>

/* NOX_NewScene
 *
 */
bool NOX_NewScene(const char *, SDL_Renderer **);

/* NOX_DestroyScene
 *
 * Try destroy scene who handle this name, if don't exists just skip
 *
 * NOX_DestroySceneAll
 *
 * Try destroy every scene existent
 */
void NOX_DestroyScene(const char *);
void NOX_DestroySceneAll(void);

/* NOX_SetCurrentScene
 *
 */
bool NOX_SetCurrentScene(const char *);

#endif /* _NOX_SCENE_MANAGER_H_ */
