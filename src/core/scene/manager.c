#include "core/scene/manager.h"

#include <string.h>
#include "flecs/flecs.h"
#include "core/debug.h"

#define MAX_SCENES 10
#define MAX_NAME_SIZE 512

typedef struct {
	const char *name;

	SDL_Renderer **renderer;
	ecs_world_t *world;
} Scene;

static Scene *scenes[MAX_SCENES] = {NULL};

static Sint8 current_scene_id = -1;
static Uint8 active_scenes = 0;

static Sint8 GetSceneID(const char *);
static void DeleteScene(Scene *);

bool NOX_NewScene(const char *name, SDL_Renderer **renderer)
{
	if (active_scenes == MAX_SCENES) {
		NOX_Log(NOX_LOG_WARN, "Max Scenes Exceeded!");
		NOX_Log(NOX_LOG_ERROR, "Cannot Create New Scene!");
		return false;
	} else if (GetSceneID(name) != -1) {
		NOX_Log(NOX_LOG_WARN, "Scene With Same Name Already Exists!");
		return false;
	}

	for (int i = 0; i < MAX_SCENES; ++i) {
		/* Check if Scene is empty */
		if (scenes[i] != NULL) {
			continue;
		}

		/* Scene is empty, lets use it */
		scenes[i] = malloc(sizeof(Scene));
		if (scenes[i] == NULL) {
			NOX_Log(NOX_LOG_ERROR, "Cannot Allocate Memory to Scene!");
			return false;
		}
		scenes[i]->name = name;
		scenes[i]->renderer = renderer;

		scenes[i]->world = ecs_init();
		if (scenes[i]->world == NULL) {
			NOX_Log(NOX_LOG_ERROR, "Cannot Create ECS World to Scene: %s", scenes[i]->name);
			DeleteScene(scenes[i]);
			return false;
		}

		if (current_scene_id == -1) {
			NOX_Log(NOX_LOG_WARN, "Active Scene Don't Exists, Setting to Newly Created...");
			NOX_SetCurrentScene(name);
		}

		break;
	}

	return true;
}

void NOX_DestroyScene(const char *name)
{
	for (int i = 0; i < MAX_SCENES; ++i) {
		if (scenes[i] == NULL || strncmp(scenes[i]->name, name, MAX_NAME_SIZE) != 0) {
			continue;
		}

		DeleteScene(scenes[i]);
		break;
	}
}

void NOX_DestroySceneAll(void)
{
	for (int i = 0; i < MAX_SCENES; ++i) {
		if (scenes[i] != NULL) {
			DeleteScene(scenes[i]);
			continue;
		}
	}
}

bool NOX_SetCurrentScene(const char *name)
{
	Sint8 scene_id = GetSceneID(name);
	if (scene_id == -1) {
		NOX_Log(NOX_LOG_WARN, "Scene Doesn't Exist, Cannot Set it to Current!");
		return false;
	}

	current_scene_id = scene_id;

	return true;
}

static Sint8 GetSceneID(const char *name)
{
	for (int i = 0; i < MAX_SCENES; ++i) {
		if (scenes[i] != NULL && strncmp(scenes[i]->name, name, MAX_NAME_SIZE) == 0)
			return i;
	}

	return -1;
}

static void DeleteScene(Scene *scene)
{
	if (scene->world != NULL) {
		ecs_fini(scene->world);
		NOX_Log(NOX_LOG_INFO, "ECS World of Scene %s Destroyed!", scene->name);
	}

	/* Remove Access to Renderer */
	scene->renderer = NULL;

	free(scene);
}
