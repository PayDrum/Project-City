#pragma once

//#include <GL/glew.h>
#include <SDL/SDL.h>
#include <string>
#include "glewwrapper.h"



class SDL {


	SDL_Window *sdlWindow;
	SDL_GLContext glcontext;
	bool initSuccess;

	Uint32 sdl_init_flags = SDL_INIT_TIMER | SDL_INIT_VIDEO;  // What SDL subsystems to initialize. See https://wiki.libsdl.org/SDL_Init
	std::string window_name = "Project City";              // Created window name - should be UTF-8 string for libSDL
	Uint32 window_width = 640;                                // Initial window width
	Uint32 window_height = 480;


public:
	SDL(glewWrapper* glewInitSettings );
	~SDL();

	bool isOk() const;

	/**
	* \brief Get application window
	* \return Pointer to window information.
	*/
	SDL_Window *getWindow()
	{
		return sdlWindow;
	}
};