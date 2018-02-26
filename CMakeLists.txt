
cmake_minimum_required(VERSION 3.0)

project(feed-stream)

# set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-long-long -pedantic")
include(./utils.cmake)
add_subdirectory(dep/raylib/src)
include_directories(dep/raylib/src dep/klib/)
add_executable(app
    src/app.c
    src/timeline.c
)
link_with_raylib(app)

