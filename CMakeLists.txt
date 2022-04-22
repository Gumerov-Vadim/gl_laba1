cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(project_name opengltest2)
project(${project_name})

add_executable(${project_name} src/main.cpp)

add_subdirectory(external/glfw)
target_link_libraries(${project_name} glfw)

add_subdirectory(external/glad)
target_link_libraries(${project_name} glad)
