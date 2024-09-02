cmake_minimum_required(VERSION 3.10)

#set(CMAKE_CXX_COMPILER /usr/bin/clang++) # Yocto does not suppurt clang natively
#set(CMAKE_CXX_COMPILER /usr/bin/g++)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17") # ToDebug with CLang add '-fstandalone-debug' option
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if(POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif()


project(OpenGLTutorial)

find_package(PkgConfig)
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(SDL2 REQUIRED)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW
	SDL2
)

include_directories(${CMAKE_SOURCE_DIR})

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# Tutorial 00
add_executable(00_sdl2
	00_sdl2/00_sdl2.cpp
)
target_link_libraries(00_sdl2
	${ALL_LIBS}
)
install(TARGETS 00_sdl2 RUNTIME DESTINATION bin)

# Tutorial 1
add_executable(01_first_window 
	01_first_window/01_first_window.cpp
)
target_link_libraries(01_first_window
	${ALL_LIBS}
)
install(TARGETS 01_first_window RUNTIME DESTINATION bin)

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
install(TARGETS 02_red_triangle RUNTIME DESTINATION bin)


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
install(TARGETS 03_matrices RUNTIME DESTINATION bin)

# Tutorial 4
add_executable(04_colored_cube
	04_colored_cube/04_colored_cube.cpp
	common/shader.hpp
	common/shader.cpp

	04_colored_cube/ColorFragmentShader.fs.glsl
	04_colored_cube/TransformVertexShader.vs.glsl
)
target_link_libraries(04_colored_cube
	${ALL_LIBS}
)
configure_file(04_colored_cube/ColorFragmentShader.fs.glsl ColorFragmentShader.fs.glsl COPYONLY)
configure_file(04_colored_cube/TransformVertexShader.vs.glsl TransformVertexShader.vs.glsl COPYONLY)
install(TARGETS 04_colored_cube RUNTIME DESTINATION bin)

# Tutorial 5
add_executable(05_textured_cube
	05_textured_cube/05_textured_cube.cpp
	common/shader.hpp
	common/shader.cpp
	common/texture.hpp
	common/texture.cpp

	05_textured_cube/TextureFragmentShader05.fs.glsl
	05_textured_cube/TransformVertexShader05.vs.glsl
)
target_link_libraries(05_textured_cube
	${ALL_LIBS}
)
configure_file(05_textured_cube/TextureFragmentShader05.fs.glsl TextureFragmentShader05.fs.glsl COPYONLY)
configure_file(05_textured_cube/TransformVertexShader05.vs.glsl TransformVertexShader05.vs.glsl COPYONLY)
configure_file(05_textured_cube/uvtemplate.DDS uvtemplate.DDS COPYONLY) 
configure_file(05_textured_cube/uvtemplate.bmp uvtemplate.bmp COPYONLY) 
configure_file(05_textured_cube/uvtemplate.tga uvtemplate.tga COPYONLY)
install(TARGETS 05_textured_cube RUNTIME DESTINATION bin)

# Tutorial 6
add_executable(06_keyboard_and_mouse
	06_keyboard_and_mouse/06_keyboard_and_mouse.cpp
	common/shader.hpp
	common/shader.cpp
	common/texture.hpp
	common/texture.cpp
	common/controls.hpp
	common/controls.cpp

	06_keyboard_and_mouse/TextureFragmentShader06.fs.glsl
	06_keyboard_and_mouse/TransformVertexShader06.vs.glsl
)
target_link_libraries(06_keyboard_and_mouse
	${ALL_LIBS}
)
configure_file(06_keyboard_and_mouse/TextureFragmentShader06.fs.glsl TextureFragmentShader06.fs.glsl COPYONLY)
configure_file(06_keyboard_and_mouse/TransformVertexShader06.vs.glsl TransformVertexShader06.vs.glsl COPYONLY)
configure_file(06_keyboard_and_mouse/uvtemplate.DDS uvtemplate.DDS COPYONLY) 
configure_file(06_keyboard_and_mouse/uvtemplate.bmp uvtemplate.bmp COPYONLY) 
configure_file(06_keyboard_and_mouse/uvtemplate.tga uvtemplate.tga COPYONLY) 
install(TARGETS 06_keyboard_and_mouse RUNTIME DESTINATION bin)