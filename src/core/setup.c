#include "core/setup.h"

#include <SDL2/SDL.h>
#include "core/debug.h"
#include "core/ecs/setup.h"

static bool Initiliaze(void);
static void UpdateFPS(void);
static void Shutdown(void);

static struct Nox {
	SDL_Window *window;
	SDL_Renderer *render;
	ecs_world_t **ecs_world;

	Uint16 fps;
	double dt; /* delta_time */

	bool running;
} nox;

bool NOX_Run(void)
{
	if (!Initiliaze())
		return false;

	while (nox.running) {
		SDL_RenderClear(nox.render);
		ecs_progress(*nox.ecs_world, nox.dt);
		SDL_RenderPresent(nox.render);

		UpdateFPS();
	}

	Shutdown();
	return true;
}

void NOX_ForceShutdown(void)
{
	NOX_Log(NOX_LOG_ERROR, "A Fatal Error Occurried, Forcing Engine Shutdown...");
	Shutdown();
}

static bool Initiliaze(void)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
		NOX_Log(NOX_LOG_ERROR | NOX_LOG_FATAL, "Can't Initialize SDL2: %s", SDL_GetError());
		return false;
	}
	NOX_Log(NOX_LOG_INFO, "SDL2 Library Initialized!");

	nox.window = SDL_CreateWindow(
		"NOXIS",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, /* NOTE: Window Centered by Default. */
		800, 600, /* TODO: Placeholder, window position will be provided by config file. */
		SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL /* TODO: Placeholder, window flags will be provided by config file */
	);

	if (nox.window == NULL) {
		NOX_Log(NOX_LOG_ERROR | NOX_LOG_FATAL, "Can't Create Window Handler: %s", SDL_GetError());
		return false;
	}
	NOX_Log(NOX_LOG_INFO, "Window Handler Created!");

	nox.render = SDL_CreateRenderer(nox.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (nox.render == NULL) {
		NOX_Log(NOX_LOG_ERROR | NOX_LOG_FATAL, "Can't Create Window Render: %s", SDL_GetError());
		return false;
	}
	NOX_Log(NOX_LOG_INFO, "Window Render Created!");

	 nox.ecs_world = NOX_SetupECS();
	 if (nox.ecs_world == NULL) {
		NOX_Log(NOX_LOG_ERROR | NOX_LOG_FATAL, "Can't Create ECS World Manager.");
		return false;
	 }
	 NOX_Log(NOX_LOG_INFO, "ECS World Manager Created!");

	return nox.running = true;
}

static void UpdateFPS(void)
{
	static Uint32 last_frame = 0, fps_count = 0;
	static double fps_timer = 0;

	fps_timer += nox.dt = (SDL_GetTicks() - last_frame) / 1000.0f;
	if (fps_timer >= 1.0f) {
		nox.fps = fps_count;
		fps_count = fps_timer = 0;
	}

	++fps_count;
	last_frame = SDL_GetTicks();
}

static void Shutdown(void)
{
	nox.running = false;

	if (nox.ecs_world != NULL) {
		ecs_fini(*nox.ecs_world);
		NOX_Log(NOX_LOG_INFO, "ECS World Destroyed!");
	}

	if (nox.render != NULL) {
		SDL_DestroyRenderer(nox.render);
		NOX_Log(NOX_LOG_INFO, "Window Renderer Destroyed!");
	}

	if (nox.window != NULL) {
		SDL_DestroyWindow(nox.window);
		NOX_Log(NOX_LOG_INFO, "Window Handler Destroyed!");
	}

	SDL_Quit();
	NOX_Log(NOX_LOG_INFO, "SDL2 Library Quitted!");
}
