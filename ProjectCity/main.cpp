//Program entry point

#include <thread>
#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include <GL/glew.h>

#include "sdlwrapper.h"
#include "glewwrapper.h"
#include "scene.h"
#include "map.h"






bool checkOpenGLErrors()
{
	GLenum e;
	bool allOk = true;
	while ((e = glGetError()) != GL_NO_ERROR)
	{
		allOk = false;

		switch (e)
		{
#ifdef GL_INVALID_ENUM
		case GL_INVALID_ENUM:
			std::cerr << "OpenGL error GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument." << std::endl;
			break;
#endif
#ifdef GL_INVALID_VALUE
		case GL_INVALID_VALUE:
			std::cerr << "OpenGL error GL_INVALID_VALUE: A numeric argument is out of range." << std::endl;
			break;
#endif
#ifdef GL_INVALID_OPERATION
		case GL_INVALID_OPERATION:
			std::cerr << "OpenGL error GL_INVALID_OPERATION: The specified operation is not allowed in the current state." << std::endl;
			break;
#endif
#ifdef GL_INVALID_FRAMEBUFFER_OPERATION
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cerr << "OpenGL error GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete." << std::endl;
			break;
#endif
#ifdef GL_OUT_OF_MEMORY
		case GL_OUT_OF_MEMORY:
			std::cerr << "OpenGL error GL_OUT_OF_MEMORY: There is not enough memory left to execute the command. The state of the GL is undefined now!" << std::endl;
			break;
#endif
#ifdef GL_STACK_UNDERFLOW
		case GL_STACK_UNDERFLOW:
			std::cerr << "OpenGL error GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow." << std::endl;
			break;
#endif
#ifdef GL_STACK_OVERFLOW
		case GL_STACK_OVERFLOW:
			std::cerr << "OpenGL error GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow." << std::endl;
			break;
#endif
		}
	}

	return allOk;
}



int main(int argc, char* args[]) {

	glewWrapper glewInitSettings;
	SDL sdl(&glewInitSettings);

	
	
	bool runRenderLoop = true;
	Uint32 prevTicks = SDL_GetTicks();

	map activeMap;

	scene mainScene(&activeMap);
	if (!mainScene.init())
	{
		std::cerr << "Unable to init scene." << std::endl;
		return -1;
	}

	if (!checkOpenGLErrors())
	{
		std::cerr << "OpenGL Errors detected during scene.init()" << std::endl;
		return -1;
	}

	mainScene.resize(glewInitSettings.window_width, glewInitSettings.window_height);

	while (runRenderLoop)
	{
		// Update the scene
		Uint32 curTicks = SDL_GetTicks();
		//scene.update(0.001f * (curTicks - prevTicks)); // Parameter in seconds
		prevTicks = curTicks;

		// Render the scene
		mainScene.render();

		// Check for any errors that might have happened inside render call.
		// Stop the loop if there has been an error.
		runRenderLoop &= checkOpenGLErrors();

		// Display window
		SDL_GL_SwapWindow(sdl.getWindow());

		// Process events
		SDL_Event e;


		while (SDL_PollEvent(&e))
		{
			// Sample event handling code. Some of this could be useful in your own scene's handleEvent() function
			switch (e.type)
			{
				// Program window closed etc.
			case SDL_QUIT:
				runRenderLoop = false;
				break;
				// Keyboard key pressed down (scancode is the physical key on keyboard, keycode is the symbolic key meaning)
			case SDL_KEYDOWN:
			{
				//std::cout << "Key " << e.key.keysym.scancode << " (" << SDL_GetKeyName(e.key.keysym.sym) << ") pressed" << std::endl;
				//scene.handleEvent(e);

				break;
			}
			// Keyboard key released
			case SDL_KEYUP:
				//std::cout << "Key " << e.key.keysym.scancode << " (" << SDL_GetKeyName(e.key.keysym.sym) << ") released" << std::endl;
				break;
				// Mouse moved
			case SDL_MOUSEMOTION:
				//std::cout << "Mouse motion: " << e.motion.x << ", " << e.motion.y << std::endl;
				break;
				// Mouse button pressed
			case SDL_MOUSEBUTTONDOWN:
				// See https://wiki.libsdl.org/SDL_MouseButtonEvent
				// Note: Mouse wheel has its own event
				//std::cout << "Mouse button down at : " << e.button.x << ", " << e.button.y << " button: ";
				switch (e.button.button)
				{
				case SDL_BUTTON_LEFT:
					std::cout << "Left";

					break;
				case SDL_BUTTON_RIGHT:
					std::cout << "Right";
					break;
				case SDL_BUTTON_MIDDLE:
					std::cout << "Middle";
					break;
				case SDL_BUTTON_X1:
					std::cout << "X1";
					break;
				case SDL_BUTTON_X2:
					std::cout << "X2";
					break;
				default:
					std::cout << "Unknown (" << e.button.button << ")";
				}
				std::cout << " clicks: " << static_cast<int>(e.button.clicks) << std::endl;
				break;
				// Mouse button released
			case SDL_MOUSEBUTTONUP:
				// See https://wiki.libsdl.org/SDL_MouseButtonEvent
				break;
				// Window-system event
			case SDL_WINDOWEVENT:
				// See https://wiki.libsdl.org/SDL_WindowEvent
				switch (e.window.event)
				{
				case SDL_WINDOWEVENT_RESIZED:
					/*window_width = e.window.data1;
					window_height = e.window.data2;
					std::cout << "Window Resized to : " << window_width << " x " << window_height << std::endl;*/
					mainScene.resize(e.window.data1, e.window.data2);
					break;
				}
				break;
			}

			// Tell running scene what just happened and stop the loop if handler returns false.
			// AND operation is done so that SDL_QUIT handler above won't be ignored either.
			runRenderLoop &= mainScene.handleEvent(e);
		}

	}
	return 0;
}



