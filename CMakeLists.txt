cmake_minimum_required(VERSION 3.16)
project(Noxis C)

find_package(SDL2 REQUIRED)

include(cmake/base.cmake)
include(cmake/warnings.cmake)

add_executable(${PROJECT_NAME})

set_source_files_properties(
# External
	# Sources
	ext/flecs/flecs.c
	# Headers
	ext/stb/stb_image.h
	ext/flecs/flecs.h
	PROPERTIES
	COMPILE_OPTIONS ""
)

target_sources(
	${PROJECT_NAME}
	PRIVATE
		# Sources
		src/noxis.c
		src/core/debug.c
		src/core/setup.c
		#src/core/ecs/setup.c
		#src/core/ecs/sprite.c

		# Headers
		include/noxis.h
		include/core/debug.h
		include/core/setup.h
		#include/core/ecs/setup.h
		#include/core/ecs/sprite.h

		# External
		# Sources
		ext/flecs/flecs.c
		# Headers
		ext/flecs/flecs.h
		ext/stb/stb_image.h
)

target_compile_features(
	${PROJECT_NAME}
	PRIVATE
		c_std_11
)

set_default_warnings(${PROJECT_NAME})

target_include_directories(
	${PROJECT_NAME}
	PRIVATE
		${PROJECT_SOURCE_DIR}/include
		${PROJECT_SOURCE_DIR}/ext
)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
		SDL2::SDL2
		m
)
