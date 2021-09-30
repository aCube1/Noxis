#ifndef _NOX_CONFIG_H_
#define _NOX_CONFIG_H_

#include <SDL2/SDL_rect.h>

typedef struct {
	char *assets_path;
	SDL_Point window_size;
} NOX_Config_t;

typedef struct {
	char *content;
	int len;
} NOX_File_t;

Uint8 NOX_LoadConfig(const char *filepath, NOX_Config_t *config);
Uint8 NOX_LoadFile(const char *filepath, NOX_File_t *file);
Uint8 NOX_ReadFile(FILE *pfile, NOX_File_t *file);

void NOX_DestroyConfig(NOX_Config_t *config);

#endif /* _NOX_CONFIG_H_ */
