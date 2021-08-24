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
			.handleEvents = NULL,
			.update = NULL,
			.render = NULL,
		}
	};
	
	return NOX_Run(setup);
}
