cmake_minimum_required(VERSION 3.16)
project(Noxis C)

include(cmake/base.cmake)
include(cmake/warnings.cmake)

find_package(SDL2 REQUIRED)
find_package(LuaJIT REQUIRED)

add_executable(${PROJECT_NAME})

target_sources(
	${PROJECT_NAME}
	PRIVATE
	src/noxis/log.c
	src/noxis/core.c
	src/noxis/sprite.c
	src/noxis/configs.c

	src/main.c

	# External sources
	ext/mjson/mjson.c
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
		${LUAJIT_INCLUDE_DIR}
)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
		SDL2::SDL2
		${LUAJIT_LIBRARIES}
		m # Remove GLIBC Error
)
