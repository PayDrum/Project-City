#pragma once


#include <GL/glew.h>
#include <SDL/SDL.h>
#include <string>


class SDL {


	SDL_Window *sdlWindow;
	SDL_GLContext glcontext;
	bool initSuccess;


public:
	SDL(bool doOpenGLDebug, int ogl_major_version, int ogl_minor_version, Uint32 flags, const std::string &window_name, Uint32 window_width, Uint32 window_height);
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