#include "core/ecs/setup.h"

#include "core/debug.h"

/* TODO: Callback Function To ecs_atfini
 * static void Destroy(ecs_world_t*, void *);
 */

static ecs_world_t *world = NULL;

ecs_world_t **NOX_SetupECS(void)
{
	if (world != NULL) {
		NOX_Log(NOX_LOG_WARN, "ECS World Already Exists!");
		return &world;
	}

	world = ecs_init();
	if (world == NULL) {
		NOX_Log(NOX_LOG_ERROR, "Can't Create a New ECS World!");
		return NULL;
	}

	return &world;
}
