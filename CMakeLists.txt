cmake_minimum_required(VERSION 3.13)
project(learnCpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(learnCpp main.cpp Texture.cpp Texture.h RenderWindow.cpp RenderWindow.h)
target_link_libraries(learnCpp ${SDL2_LIBRARIES})
target_link_libraries(learnCpp ${SDL2_IMAGE_LIBRARIES})
