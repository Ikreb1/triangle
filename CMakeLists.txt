cmake_minimum_required(VERSION 3.25)
project(triangle)

# target_link_libraries(OpenGL glfw)

set(CMAKE_CXX_STANDARD 14)
#find_package (OpenGL REQUIRED)
include_directories("C:/GLFW/include")
link_directories("C:/GLFW/lib-mingw-w64")

include_directories("C:/glad/include")
include_directories("C:/glad/src")

include_directories("C:/git/triangle/include")


set(SOURCE_FILES main.cpp)
add_executable(triangle main.cpp "C:/glad/src/glad.c" triangle.cpp triangle.h ShaderExample.cpp ShaderExample.h Shader.cpp Shader.h textureExample.cpp textureExample.h idk.h texture.cpp texture.h
        transformationExample.cpp
        transformationExample.h
        CoordSystemExample.cpp
        CoordSystemExample.h)
target_link_libraries (triangle ${OPENGL_LIBRARIES} glfw3 glu32 opengl32)
