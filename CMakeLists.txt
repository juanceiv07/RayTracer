cmake_minimum_required(VERSION 4.0)
project(RayTracer LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(Rayt
    src/main.cc
    src/glad.c
)

target_include_directories(Rayt PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include)
target_link_libraries(Rayt glfw OpenGL::GL)

target_compile_options(Rayt PRIVATE -Wall -Wextra)
