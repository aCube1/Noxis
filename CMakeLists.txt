cmake_minimum_required(VERSION 3.16)
project(Noxis)

set(CMAKE_C_FLAGS "-Wall -Wpedantic -Wextra -Werror")
set(CMAKE_C_STANDARD 11)

set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

find_package(SDL2 REQUIRED)

set(INCLUDE_DIRS ${SDL2_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)
set(LINK_LIBS ${SDL2_LIBRARIES})

file(GLOB SOURCES
	"src/*.c"
	"src/core/*.c"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LINK_LIBS})
