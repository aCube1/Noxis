#include "utils.h"
#include "core/game.h"

extern bool NOX_fatal_error;

int main(int argc, char *argv[])
{
	NOX_StartGame(argc, argv);
	NOX_LoopGame();

	return NOX_fatal_error ? EXIT_FAILURE : EXIT_SUCCESS;
}
