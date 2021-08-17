#include "core/game.h"

#include "utils.h"
#include "core/init.h"
#include "core/quit.h"
#include "core/callbacks.h"

static struct NOX_Game_t {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	double dt, last_time, fps_count;
	int current_fps;
} NOX_Game;

void NOX_StartGame(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	struct NOX_Game_t *self = &NOX_Game;

	if (NOX_InitSDL2(&self->window, &self->renderer, NOX_window_rect, "Noxis") != 0) {
		NOX_DisplayMessage(NOX_LOG_ERROR | NOX_LOG_FATAL, "Cannot Create All SDL2 Objects");
		return;
	}
	NOX_DisplayMessage(NOX_LOG_INFO, "SDL2 Objects Created And Library Initialized");

	NOX_DisplayMessage(NOX_LOG_INFO, "Game Base Created");
}

void NOX_LoopGame(void)
{
	struct NOX_Game_t *self = &NOX_Game;

	NOX_is_running = true;
	self->last_time = SDL_GetTicks();
	while (!NOX_fatal_error && NOX_is_running) {
		/* Get Delta Time */
		self->dt = (SDL_GetTicks() - self->last_time) / 1000.0f;
		self->last_time = SDL_GetTicks();

		self->current_fps++;
		/*Call Callback Functions*/
		NOX_EventHandler(&self->event);
		NOX_Update(self->dt);
		NOX_Render(self->renderer);

		/* Get FPS */
		self->fps_count += (SDL_GetTicks() - self->last_time) / 1000.0f;
		if (self->fps_count >= 1.0f) {
			NOX_fps = self->current_fps;
			self->fps_count = 0;
			NOX_fps = 0;
		}
	}

	if (NOX_fatal_error) {
		NOX_DisplayMessage(NOX_LOG_ERROR, "A Fatal Error Occurried! Shutting Down...");
	}

	NOX_EndGame();
}

void NOX_EndGame(void)
{
	struct NOX_Game_t *self = &NOX_Game;

	NOX_QuitSDL2(&self->window, &self->renderer);
}
