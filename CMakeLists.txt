cmake_minimum_required(VERSION 3.13)
project(learnCpp)
#set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(glm REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

add_executable(learnCpp main.cpp Texture.cpp Texture.h RenderWindow.cpp RenderWindow.h TextureAtlas.cpp TextureAtlas.h Level.cpp Level.h Player.cpp Player.h Rectangle.cpp Rectangle.h Scene.cpp Scene.h InputHandler.cpp InputHandler.h Entity.cpp Entity.h Enemy.cpp Enemy.h)
target_link_libraries(learnCpp ${SDL2_LIBRARIES})
target_link_libraries(learnCpp ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(learnCpp ${Boost_LIBRARIES})

add_subdirectory(thirdparty/glad)

target_link_libraries(learnCpp glad)