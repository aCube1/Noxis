#ifndef _NOX_SPRITE_H_
#define _NOX_SPRITE_H_

#include <stdbool.h>
#include "noxis/log.h"

#if SDL_BYTEORDER == SDL_BYTE_ENDIAN
#	define NOX_RMASK 0xff000000
#	define NOX_GMASK 0x00ff0000
#	define NOX_BMASK 0x0000ff00
#	define NOX_AMASK 0x000000ff
#else
#	define NOX_RMASK 0x000000ff
#	define NOX_GMASK 0x0000ff00
#	define NOX_BMASK 0x00ff0000
#	define NOX_AMASK 0xff000000
#endif

typedef struct {
	/* Render Data */
	SDL_Texture *texture; /* Read-Only */
	SDL_Surface *surface; /* Read-Only */
	SDL_Rect frame_rect;
	bool can_draw; /* Debug Purposes | Read-Only */

	/* Image Data */
	unsigned char *data; /* Read-Only */
	int nr_channels, pitch, depth; /* Read-Only */
	uint32_t pixel_format; /* Read-Only */
	SDL_Point texture_size; /* Read-Only */

	/* Render config */
	SDL_RendererFlip flip;
	SDL_FPoint scale, center;
	double angle;
} NOX_Sprite_t;

/* NOX_CreateSprite
 *
 */

/* NOX_LoadSprite
 *
 */

/* NOX_DestroySprite
 *
 */

NOX_Sprite_t *NOX_CreateSprite(SDL_Renderer *renderer, const char *file, SDL_Point frame_rect);
int NOX_LoadSprite(SDL_Renderer *renderer, NOX_Sprite_t **sprite, const char *file);
void NOX_DestroySprite(NOX_Sprite_t *sprite);

void NOX_RenderSprite(SDL_Renderer *renderer, NOX_Sprite_t *sprite, SDL_FPoint position, SDL_FPoint size);

/* Getters / Setters */
SDL_Rect NOX_GetSpriteFrameRect(NOX_Sprite_t *sprite);
SDL_FPoint NOX_GetSpriteCenter(NOX_Sprite_t *sprite);
SDL_FPoint NOX_GetSpriteScale(NOX_Sprite_t *sprite);
SDL_RendererFlip NOX_GetSpriteFlip(NOX_Sprite_t *sprite);
double NOX_GetSpriteAngle(NOX_Sprite_t *sprite);

void NOX_SetSpriteFrameRect(NOX_Sprite_t **sprite, SDL_Rect frame_rect);
void NOX_SetSpriteCenter(NOX_Sprite_t **sprite, SDL_FPoint center);
void NOX_SetSpriteScale(NOX_Sprite_t **sprite, SDL_FPoint scale);
void NOX_SetSpriteFlip(NOX_Sprite_t **sprite, SDL_RendererFlip flip);
void NOX_SetSpriteAngle(NOX_Sprite_t **sprite, double angle);

#endif /* _NOX_SPRITE_H_ */
