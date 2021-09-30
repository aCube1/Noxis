#include "noxis/sprite.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

NOX_Sprite_t *NOX_CreateSprite(SDL_Renderer *renderer, const char *file, SDL_Point frame_size)
{
	NOX_Sprite_t *sprite = malloc(sizeof(NOX_Sprite_t));
	if (sprite == NULL) {
		NOX_Log(NOX_LOG_ERROR | NOX_LOG_FATAL, "Cannot Allocate Memory For Sprite");
		return NULL;
	}

	if (NOX_LoadSprite(renderer, &sprite, file) < 0) {
		NOX_Log(NOX_LOG_ERROR, "Cannot Create Sprite Object");
		return NULL;
	}

	sprite->frame_rect = (SDL_Rect) {
		0, 0,
		frame_size.x != 0 ? frame_size.x : sprite->texture_size.x,
		frame_size.y != 0 ? frame_size.y : sprite->texture_size.y,
	};
	sprite->center = (SDL_FPoint) {
		sprite->frame_rect.w / 2,
		sprite->frame_rect.h / 2,
	};
	sprite->scale = (SDL_FPoint) {1.0f, 1.0f};
	sprite->can_draw = true;

	NOX_Log(NOX_LOG_INFO, "Sprite Object Created");
	return sprite;
}

SDL_Rect NOX_GetSpriteRect(NOX_Sprite_t *sprite) { return sprite->frame_rect; }
SDL_FPoint NOX_GetSpriteCenter(NOX_Sprite_t *sprite) { return sprite->center; }
SDL_FPoint NOX_GetSpriteScale(NOX_Sprite_t *sprite) { return sprite->scale; }
SDL_RendererFlip NOX_GetSpriteFlip(NOX_Sprite_t *sprite) { return sprite->flip; }
double NOX_GetSpriteAngle(NOX_Sprite_t *sprite) { return sprite->angle; }

void NOX_SetSpriteFrameRect(NOX_Sprite_t **sprite, SDL_Rect frame_rect) { (*sprite)->frame_rect = frame_rect; }
void NOX_SetSpriteCenter(NOX_Sprite_t **sprite, SDL_FPoint center) { (*sprite)->center = center; }
void NOX_SetSpriteScale(NOX_Sprite_t **sprite, SDL_FPoint scale) { (*sprite)->scale = scale; }
void NOX_SetSpriteFlip(NOX_Sprite_t **sprite, SDL_RendererFlip flip) { (*sprite)->flip = flip; }
void NOX_SetSpriteAngle(NOX_Sprite_t **sprite, double angle) { (*sprite)->angle = angle; }

int NOX_LoadSprite(SDL_Renderer *renderer, NOX_Sprite_t **sprite, const char *file)
{
	(*sprite)->data = stbi_load(file, &(*sprite)->texture_size.x, &(*sprite)->texture_size.y, &(*sprite)->nr_channels, 0);
	if ((*sprite)->data == NULL) {
		NOX_Log(NOX_LOG_ERROR, "Cannot Load Sprite Texture File: %s", file);
		NOX_DestroySprite(*sprite);
		return -1;
	}

	switch ((*sprite)->nr_channels) {
		case STBI_rgb:
			(*sprite)->depth = 24;
			(*sprite)->pitch = (*sprite)->texture_size.x * 3;
			(*sprite)->pixel_format = SDL_PIXELFORMAT_RGB24;
			break;
		case STBI_rgb_alpha:
			(*sprite)->depth = 32;
			(*sprite)->pitch = (*sprite)->texture_size.x * 4;
			(*sprite)->pixel_format = SDL_PIXELFORMAT_RGBA32;
			break;
		default:
			NOX_Log(NOX_LOG_ERROR, "Cannot Identify Sprite Texture Pixel Format");
			NOX_DestroySprite(*sprite);
			return -1;
	}

	(*sprite)->surface = SDL_CreateRGBSurfaceWithFormatFrom(
			(*sprite)->data,
			(*sprite)->texture_size.x,
			(*sprite)->texture_size.y,
			(*sprite)->depth, (*sprite)->pitch,
			(*sprite)->pixel_format
	);

	if ((*sprite)->surface == NULL) {
		NOX_Log(NOX_LOG_ERROR, "Cannot Create Sprite Surface For Texture: %s", SDL_GetError());
		NOX_DestroySprite(*sprite);
		return -1;
	}

	(*sprite)->texture = SDL_CreateTextureFromSurface(renderer, (*sprite)->surface);
	if ((*sprite)->texture == NULL) {
		NOX_Log(NOX_LOG_ERROR, "Cannot Create Texture From Sprite Surface: %s", SDL_GetError());
		NOX_DestroySprite(*sprite);
		return -1;
	}

	return 0;
}

void NOX_RenderSprite(SDL_Renderer *renderer, NOX_Sprite_t *sprite, SDL_FPoint position, SDL_FPoint size)
{
	int success;

	if (!sprite->can_draw || (renderer == NULL && sprite == NULL)) {
		NOX_Log(NOX_LOG_ERROR, "Sprite Or Renderer Is NULL");
		sprite->can_draw = false;
		return;
	}

	SDL_FRect rect = {
		position.x, position.y,
		size.x * sprite->scale.x, size.y * sprite->scale.y,
	};

	success = SDL_RenderCopyExF(renderer, sprite->texture, &sprite->frame_rect, &rect, sprite->angle, &sprite->center, sprite->flip);
	if (success < 0) {
		NOX_Log(NOX_LOG_ERROR, "Cannot Copy Sprite Texture To Renderer: %s", SDL_GetError());
		sprite->can_draw = false;
		return;
	}
}

void NOX_DestroySprite(NOX_Sprite_t *sprite)
{
	if (sprite->texture != NULL) {
		SDL_DestroyTexture(sprite->texture);
		NOX_Log(NOX_LOG_INFO, "Sprite Texture Destroyed");
	}

	if (sprite->surface != NULL) {
		SDL_FreeSurface(sprite->surface);
		NOX_Log(NOX_LOG_INFO, "Sprite Texture Surface Freed");
	}

	if (sprite->data != NULL) {
		stbi_image_free(sprite->data);
		NOX_Log(NOX_LOG_INFO, "Sprite Texture Data Freed");
	}

	if (sprite != NULL) {
		free(sprite);
		NOX_Log(NOX_LOG_INFO, "Sprite Memory Freed");
	}
}
