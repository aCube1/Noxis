#include "core/game.h"

#include "utils.h"
#include "core/init.h"
#include "core/quit.h"
#include "core/callbacks.h"

static struct NOX_Game_t {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;
} NOX_Game;

void NOX_StartGame(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	struct NOX_Game_t *self = &NOX_Game;

	if (NOX_InitSDL2(&self->window, &self->renderer, NOX_GetWindowRect(), "Noxis") != 0) {
		NOX_DisplayMessage(NOX_LOG_ERROR | NOX_LOG_FATAL, "Cannot Create All SDL2 Objects");
		return;
	}
	NOX_DisplayMessage(NOX_LOG_INFO, "SDL2 Objects Created And Library Initialized");

	NOX_DisplayMessage(NOX_LOG_INFO, "Game Base Created");
}

void NOX_LoopGame(void)
{
	struct NOX_Game_t *self = &NOX_Game;

	while (!NOX_HasFatalError() && NOX_IsRunning()) {
		NOX_UpdateDeltaTime();

		/*Call Main Game Functions*/
		NOX_EventHandler(&self->event);
		NOX_Update();
		NOX_Render(self->renderer);
	}

	if (NOX_HasFatalError()) {
		NOX_DisplayMessage(NOX_LOG_ERROR, "A Fatal Error Occurried! Shutting Down...");
	}

	NOX_EndGame();
}

void NOX_EndGame(void)
{
	struct NOX_Game_t *self = &NOX_Game;

	NOX_QuitSDL2(&self->window, &self->renderer);
}
