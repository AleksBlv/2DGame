cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

set(PROJECT_NAME 2DGame)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/Renderer/shaderProgram.h
    src/Renderer/shaderProgram.cpp 
    src/Renderer/window.h 
    src/Renderer/window.cpp 
    src/fromGit/stb_image.h
    src/fromGit/stb_image.cpp
    src/Renderer/texture.h
    src/Renderer/texture.cpp
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)