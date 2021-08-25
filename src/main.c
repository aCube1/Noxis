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
	
	return NOX_Run(setup);
}
