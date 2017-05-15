#pragma once
#include <GL\glew.h>
#include <SDL\SDL.h>
#include <string>

class glewWrapper {

public:

	bool enableOpenGLDebugging = true;                        // Enable OpenGL debug context and install debug message callback if available
	bool glewExperimentalEnabled = true;
	const int ogl_major_version = 3;                                // OpenGL major version to request. See https://www.opengl.org/wiki/History_of_OpenGL
	const int ogl_minor_version = 2;                                // OpenGL minor version to request.
	Uint32 sdl_init_flags = SDL_INIT_TIMER | SDL_INIT_VIDEO;  // What SDL subsystems to initialize. See https://wiki.libsdl.org/SDL_Init
	std::string window_name = "Chip8 Emulator";              // Created window name - should be UTF-8 string for libSDL
	Uint32 window_width = 640;                                // Initial window width
	Uint32 window_height = 480;                               // Initial window height

	glewWrapper();
	~glewWrapper();

	void init();
};
