#ifndef _NOX_CONFIG_H_
#define _NOX_CONFIG_H_

#include <stdbool.h>
#include <SDL2/SDL_rect.h>

typedef struct {
	char *assets_path, *title;
	SDL_Point window_size;
	Uint8 window_flags;
} NOX_Config_t;

typedef struct {
	char *content;
	int len;
} NOX_File_t;

bool NOX_LoadConfig(const char *filepath, NOX_Config_t *config);
bool NOX_LoadFile(const char *filepath, NOX_File_t *file);
bool NOX_ReadFile(FILE *pfile, NOX_File_t *file);

void NOX_DestroyConfig(NOX_Config_t *config);

#endif /* _NOX_CONFIG_H_ */
