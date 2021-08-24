#include "noxis/core.h"
#include "noxis/log.h"

static struct Nox {
	SDL_Window *window;
	SDL_Renderer *renderer;
	
	Uint16 fps;
	double delta_time;
	
	bool running;
} nox;

static bool initialize(NOX_Setup_t setup);
static void eventHandler(NOX_Setup_t setup);
static void updateFPS(void);
static void shutdown(void);

bool NOX_Run(NOX_Setup_t setup)
{
	if (!initialize(setup)) {
		shutdown();
		return false;
	}
	
	while (nox.running) {
		eventsHandler();
		
		if (setup.callbacks.update != NULL)
			setup.callbacks.update();
		
		SDL_RenderClear(nox.renderer);
		if (setup.callbacks.render != NULL)
			setup.callbacks.render(nox.renderer);
		SDL_RenderPresent(nox.renderer);
		
		updateFPS();
	}

	shutdown();
	return true;
}

static bool initialize(NOX_Setup_t setup)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
		NOX_Log(NOX_LOG_ERROR, "Can't initialize SDL2: %s", SDL_GetError());
		return false;
	}
	NOX_Log(NOX_LOG_INFO, "SDL2 Initialized");
	
	nox.window = SDL_CreateWindow(
		setup.title != NULL ? setup.title : "No Title",
		setup.window.x, setup.window.y,
		setup.window.w > 0 ? setup.window.w : 800,
		setup.window.h > 0 ? setup.window.h : 600,
		SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
	
	if (nox.window == NULL) {
		NOX_Log(NOX_LOG_ERROR, "Can't create window handler: %s", SDL_GetError());
		return false;
	}
	NOX_Log(NOX_LOG_INFO, "Window handler created");
	
	nox.renderer = SDL_CreateRenderer(nox.window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (nox.renderer == NULL) {
		NOX_Log(NOX_LOG_ERROR, "Can't create window renderer: %s", SDL_GetError());
		return false;
	}
	NOX_Log(NOX_LOG_INFO, "Window renderer created");
	
	nox.running = true;
	return true;
}

static void eventHandler(NOX_Setup_t setup)
{
	SDL_Event event;
	
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			nox.running = false;
			break;
		default:
			if (setup.callbacks.handleEvents != NULL)
				setup.callbacks.handleEvents(event);
		}
	}
}

static void updateFPS(void)
{
	static Uint32 last_frame = 0;
	static Uint32 fps_count = 0;
	static double fps_timer = 0;
	
	fps_timer += (SDL_GetTicks() - last_frame) / 1000.0;
	if (fps_timer >= 1.0) {
		nox.fps = fps_count;
		fps_count = fps_timer = 0;
	}
	
	++fps_count;
	last_frame = SDL_GetTicks();
}

static void shutdown(void)
{
	nox.running = false;
	
	if (nox.renderer != NULL) {
		SDL_DestroyRenderer(nox.renderer);
		NOX_Log(NOX_LOG_INFO, "Window renderer destroyed");
	}

	if (nox.window != NULL) {
		SDL_DestroyWindow(nox.window);
		NOX_Log(NOX_LOG_INFO, "Window handler destroyed");
	}

	SDL_Quit();
	NOX_Log(NOX_LOG_INFO, "SDL2 shutdowned");
}
