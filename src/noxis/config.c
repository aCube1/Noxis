#include "noxis/config.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <SDL2/SDL_video.h>
#include "mjson/mjson.h"
#include "noxis/log.h"

#define MAX_BUFFER_SIZE 512

#define DEFAULT_CONFIG "{\n"			\
	"\t\"assets_path\": \"/assets/\",\n"	\
	"\t\"window\": {\n"			\
	"\t\t\"title\": \"Noxis\",\n"		\
	"\t\t\"fullscreen\": false,\n"		\
	"\t\t\"size\": [800, 600]\n"		\
	"\t}\n"					\
"}\0"

bool NOX_LoadConfig(const char *filepath, NOX_Config_t *config)
{
	NOX_File_t file;
	double window_width, window_height;
	int window_fullscreen;
	FILE *config_file = fopen(filepath, "rb");

	if (config_file == NULL || NOX_ReadFile(config_file, &file) != 0) {
		NOX_Log(NOX_LOG_WARN, "Cannot open file: %s", filepath);
		NOX_Log(NOX_LOG_INFO, "Creating new config file and using default configs...");

		config_file = fopen(filepath, "wb+");
		if (config_file == NULL) {
			NOX_Log(NOX_LOG_ERROR, "Cannot create new config file.");
			return false;
		} else {
			fputs(DEFAULT_CONFIG, config_file);
			fflush(config_file);

			freopen(NULL, "rb", config_file);
			if (NOX_ReadFile(config_file, &file) != 0) {
				NOX_Log(NOX_LOG_ERROR, "Cannot use default configs.");
				return false;
			}
		}
	}

	/* Get Configs Variables */
	config->assets_path = calloc(MAX_BUFFER_SIZE, sizeof(char));
	config->title = calloc(MAX_BUFFER_SIZE, sizeof(char));

	mjson_get_string(file.content, file.len, "$.assets_path", config->assets_path, MAX_BUFFER_SIZE);
	mjson_get_string(file.content, file.len, "$.window.title", config->title, MAX_BUFFER_SIZE);
	mjson_get_bool(file.content, file.len, "$.window.fullscreen", &window_fullscreen);
	mjson_get_number(file.content, file.len, "$.window.size[0]", &window_width);
	mjson_get_number(file.content, file.len, "$.window.size[1]", &window_height);

	if (window_fullscreen)
		config->window_flags |= SDL_WINDOW_FULLSCREEN;

	config->window_size = (SDL_Point) {
		window_width != 0 ? (int)window_width : 800,
		window_height != 0 ? (int)window_height : 600,
	};

	free(file.content);
	fclose(config_file);
	return true;
}

bool NOX_LoadFile(const char *filepath, NOX_File_t *file)
{
	FILE *pfile = fopen(filepath, "rb");
	if (pfile == NULL) {
		NOX_Log(NOX_LOG_ERROR, "Cannot open file: %s", filepath);
		return false;
	}

	bool success = NOX_ReadFile(pfile, file);
	fclose(pfile);
	return success;
}

bool NOX_ReadFile(FILE *pfile, NOX_File_t *file)
{
	if (pfile == NULL) {
		NOX_Log(NOX_LOG_ERROR, "File couldn't be NULL.");
		return false;
	}

	Uint32 max_size = MAX_BUFFER_SIZE; /* Max size of current buffer */
	char tmp_buffer[MAX_BUFFER_SIZE]; /* Temporary buffer to append */
	char *buffer = calloc(max_size, sizeof(char));
	if (buffer == NULL) {
		NOX_Log(NOX_LOG_ERROR, "Cannot alocate memory to the buffer.");
		goto ERROR;
	}

	while (!feof(pfile)) {
		size_t bytes_readed = fread(tmp_buffer, sizeof(char), MAX_BUFFER_SIZE, pfile);
		if (bytes_readed != MAX_BUFFER_SIZE && ferror(pfile)) {
				NOX_Log(NOX_LOG_WARN, "An error occurred on file read.");
				break;
		}

		max_size += bytes_readed;
		char *new_buffer = realloc(buffer, max_size * sizeof(char));
		if (new_buffer == NULL) {
			NOX_Log(NOX_LOG_ERROR, "Cannot realloc buffer memory.");
			goto ERROR;
		}

		buffer = new_buffer;
		strncat(buffer, tmp_buffer, bytes_readed);
	}

	file->content = buffer;
	file->len = max_size;
	return true;

ERROR: /* NOTE: I know, maybe I don't need use goto */
	free(buffer);
	NOX_Log(NOX_LOG_ERROR, "Cannot load content of file.");
	return false;
}

void NOX_DestroyConfig(NOX_Config_t *config)
{
	if (config->assets_path != NULL)
		free(config->assets_path);
	if (config->title != NULL)
		free(config->title);
}
