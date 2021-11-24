#include "noxis/core.h"

#include "flecs/flecs.h"
#include "noxis/log.h"
#include "noxis/config.h"

static bool Initialize(NOX_Config_t *config);
static void EventsHandler(void);
static void UpdateFPS(void);
static void Shutdown(void);

static struct Nox {
	SDL_Window *window;
	SDL_Renderer *renderer;
	ecs_world_t *world;

	Uint16 fps;
	double delta_time;

	bool running;
} nox;

bool NOX_Run(const char *conf_filepath)
{
	NOX_Config_t config;
	if (!NOX_LoadConfig(conf_filepath, &config)) {
		return false;
	}

	if (!Initialize(&config)) {
		Shutdown();
		return false;
	}

	while (nox.running) {
		EventsHandler();

		SDL_RenderClear(nox.renderer);
		ecs_progress(nox.world, nox.delta_time);
		SDL_RenderPresent(nox.renderer);

		UpdateFPS();
	}

	NOX_DestroyConfig(&config);
	Shutdown();
	return true;
}

/* TODO: Implement this function */
void NOX_ForceShutdown(void) {}

static bool Initialize(NOX_Config_t *config)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
		NOX_Log(NOX_LOG_ERROR, "Can't initialize SDL2: %s", SDL_GetError());
		return false;
	}
	NOX_Log(NOX_LOG_INFO, "SDL2 initialized!");

	nox.window = SDL_CreateWindow(
		config->title,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, /* Window Centered by Default */
		config->window_size.x, config->window_size.y,
		SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL | config->window_flags
	);

	if (nox.window == NULL) {
		NOX_Log(NOX_LOG_ERROR, "Can't create window handler: %s", SDL_GetError());
		return false;
	}
	NOX_Log(NOX_LOG_INFO, "Window handler created!");

	nox.renderer = SDL_CreateRenderer(nox.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (nox.renderer == NULL) {
		NOX_Log(NOX_LOG_ERROR, "Can't create window renderer: %s", SDL_GetError());
		return false;
	}
	NOX_Log(NOX_LOG_INFO, "Window renderer created!");

	nox.world = ecs_init();
	if (nox.world == NULL) {
		NOX_Log(NOX_LOG_ERROR, "Can't initialize ECS world!");
		return false;
	}

	return nox.running = true;
}

static void EventsHandler(void) {}

static void UpdateFPS(void)
{
	static Uint32 last_frame = 0, fps_count = 0;
	static double fps_timer = 0;

	fps_timer += nox.delta_time = (SDL_GetTicks() - last_frame) / 1000.0f;
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

	if (nox.world != NULL) {
		ecs_fini(nox.world);
		NOX_Log(NOX_LOG_INFO, "ECS world destroyed!");
	}

	if (nox.renderer != NULL) {
		SDL_DestroyRenderer(nox.renderer);
		NOX_Log(NOX_LOG_INFO, "Window renderer destroyed!");
	}

	if (nox.window != NULL) {
		SDL_DestroyWindow(nox.window);
		NOX_Log(NOX_LOG_INFO, "Window handler destroyed!");
	}

	SDL_Quit();
	NOX_Log(NOX_LOG_INFO, "SDL2 Quitted!");
}

Uint16 NOX_GetFPS(void) { return nox.fps; }
