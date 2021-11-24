#ifndef _NOXIS_CORE_H_
#define _NOXIS_CORE_H_

#include <stdbool.h>
#include <SDL2/SDL.h>

/* NOX_Run
 *
 */
bool NOX_Run(const char *conf_filepath);

/* NOX_ForceShutdown
 *
 */
void NOX_ForceShutdown(void);

/* Getters */
Uint16 NOX_GetFPS(void);

#endif /* _NOXIS_CORE_H_ */
