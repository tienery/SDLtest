cmake_minimum_required (VERSION 2.6)
cmake_policy(SET CMP0015 NEW)
project (SDLtest)

include_directories(
    lib/win32/SDL2-2.0.3/include
	lib/win32/SDL2_image-2.0.0/include
)

link_directories(
	lib/win32/SDL2-2.0.3/lib/x86
	lib/win32/SDL2_image-2.0.0/lib/x86
)

add_executable(SDLtest
	src/main.cpp
	src/mintSDL/display/anim.cpp
	src/mintSDL/display/display.cpp
	src/mintSDL/display/geom.cpp
	src/mintSDL/display/texture.cpp
	src/mintSDL/input.cpp
)

target_link_libraries(SDLtest
	SDL2main
	SDL2
	SDL2_image
)