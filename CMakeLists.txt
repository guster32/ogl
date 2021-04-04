cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_COMPILER /usr/bin/clang++) # Yocto does not suppurt clang natively
#set(CMAKE_CXX_COMPILER /usr/bin/g++)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17") # ToDebug with CLang add '-fstandalone-debug' option
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

project(OpenGLTutorial)

find_package(PkgConfig)
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW
)

include_directories(${CMAKE_SOURCE_DIR})

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# Tutorial 1
add_executable(01_first_window 
	01_first_window/01_first_window.cpp
)
target_link_libraries(01_first_window
	${ALL_LIBS}
)

# Tutorial 2
add_executable(02_red_triangle
	02_red_triangle/02_red_triangle.cpp
	common/shader.hpp
	common/shader.cpp

	02_red_triangle/SimpleFragmentShader.fs.glsl
	02_red_triangle/SimpleVertexShader.vs.glsl
)
target_link_libraries(02_red_triangle
	${ALL_LIBS}
)
configure_file(02_red_triangle/SimpleFragmentShader.fs.glsl SimpleFragmentShader.fs.glsl COPYONLY)
configure_file(02_red_triangle/SimpleVertexShader.vs.glsl SimpleVertexShader.vs.glsl COPYONLY)

# Tutorial 3
add_executable(03_matrices
	03_matrices/03_matrices.cpp
	common/shader.hpp
	common/shader.cpp

	03_matrices/SingleColor.fs.glsl
	03_matrices/SimpleTransform.vs.glsl
)
target_link_libraries(03_matrices
	${ALL_LIBS}
)
configure_file(03_matrices/SingleColor.fs.glsl SingleColor.fs.glsl COPYONLY)
configure_file(03_matrices/SimpleTransform.vs.glsl SimpleTransform.vs.glsl COPYONLY)