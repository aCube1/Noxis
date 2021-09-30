#include "noxis/configs.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "mjson/mjson.h"
#include "noxis/log.h"

#define MAX_BUFFER_SIZE 512

#define DEFAULT_CONFIG "{\n"					\
		"\t\"assets_path\":\"/assets/\",\n" 	\
		"\t\"window_size\":[800, 600]\n" 		\
	"}\0"

Uint8 NOX_LoadConfig(const char *filepath, NOX_Config_t *config)
{
	NOX_File_t file;
	double window_width, window_height;
	FILE *config_file = fopen(filepath, "rb");
	if (config_file == NULL || NOX_ReadFile(config_file, &file) != 0) {
		NOX_Log(NOX_LOG_WARN, "Cannot open file: %s", filepath);
		NOX_Log(NOX_LOG_INFO, "Creating new config file and using default configs...");

		config_file = fopen(filepath, "wb+");
		if (config_file == NULL) {
			NOX_Log(NOX_LOG_ERROR, "Cannot create new config file.");
			return 1;
		} else {
			fputs(DEFAULT_CONFIG, config_file);
			fflush(config_file);

			freopen(NULL, "rb", config_file);
			if (NOX_ReadFile(config_file, &file) != 0) {
				NOX_Log(NOX_LOG_ERROR, "Cannot use default configs.");
				return 1;
			}
		}
	}

	config->assets_path = calloc(MAX_BUFFER_SIZE, sizeof(char));
	mjson_get_string(file.content, file.len, "$.assets_path", config->assets_path, MAX_BUFFER_SIZE);
	mjson_get_number(file.content, file.len, "$.window_size[0]", &window_width);
	mjson_get_number(file.content, file.len, "$.window_size[1]", &window_height);

	config->window_size = (SDL_Point) {(int) window_width, (int) window_height};

	free(file.content);
	fclose(config_file);
	return 0;
}

Uint8 NOX_LoadFile(const char *filepath, NOX_File_t *file)
{
	FILE *pfile = fopen(filepath, "rb");
	if (pfile == NULL) {
		NOX_Log(NOX_LOG_ERROR, "Cannot open file: %s", filepath);
		return 1;
	}

	Uint8 success = NOX_ReadFile(pfile, file);
	fclose(pfile);
	return success;
}

Uint8 NOX_ReadFile(FILE *pfile, NOX_File_t *file)
{
	if (pfile == NULL) {
		NOX_Log(NOX_LOG_ERROR, "File couldn't be NULL.");
		return 1;
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
	return 0;

ERROR: /* NOTE: I know, maybe I don't need use goto */
	free(buffer);
	NOX_Log(NOX_LOG_ERROR, "Cannot load content of file.");
	return 1;
}

void NOX_DestroyConfig(NOX_Config_t *config)
{
	if (config->assets_path != NULL) {
		free(config->assets_path);
	}
}
