cmake_minimum_required(VERSION 3.16)
project(Noxis C)

include(cmake/base.cmake)
include(cmake/warnings.cmake)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME})

target_sources(
	${PROJECT_NAME}
	PRIVATE
	src/noxis/log.c
	src/noxis/core.c

	include/graphics/sprite.h
	src/graphics/sprite.c

	src/main.c

	ext/stb_image.h
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
		m # Remove GLIBC Error
)
