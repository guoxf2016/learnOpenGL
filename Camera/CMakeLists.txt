cmake_minimum_required(VERSION 3.10)
project(HelloWindow)

set(CMAKE_CXX_STANDARD 11)

include_directories("/home/guoxiaofei/local/include/")

find_package (PkgConfig REQUIRED)
find_package (OpenGL REQUIRED)
find_package (GLUT REQUIRED)
link_libraries(SOIL)
link_libraries(glfw3)
#link_libraries(glad)
include_directories(${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIRS} ${glfw_INCLUDE_DIRS})
add_executable(HelloWindow main.cpp glad.c shader.h shader.cpp)

target_link_libraries (HelloWindow ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} GL m dl Xinerama Xrandr Xi Xcursor X11 Xxf86vm pthread)