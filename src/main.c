#include "noxis.h"

int main(int argc, char *argv[])
{
	(void) argc; (void) argv;

	NOX_Setup_t setup = {
		.title = "Noxis",
		.window = {
			.x = 0,
			.y = 0,
			.w = 800,
			.h = 600
		},

		.callbacks = {
			.HandleEvents = NULL,
			.Update = NULL,
			.Render = NULL,
		}
	};

	NOX_Config_t config;
	if (NOX_LoadConfig("config.json", &config) == 0) {
		NOX_Log(NOX_LOG_DEBUG, "Width: %i Height: %i", config.window_size.x, config.window_size.y);
		NOX_DestroyConfig(&config);
	}

	return NOX_Run(setup);
}
