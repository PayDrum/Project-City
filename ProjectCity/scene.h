#pragma once

#include <SDL\SDL.h>
#include <vector>

#include "map.h"
#include "shaderprogram.h"              // For shader management
#include "planetile.h"
#include "grid.h"
#include "coordinateAxes.h"
#include "camera.h"
#include <glm/glm.hpp>                  // Matrix library
#include <glm/gtc/matrix_transform.hpp> // Needed for glm::perspective() and friends.
#include <glm/gtc/type_ptr.hpp>         // Needed for glm::value_ptr(x). You can use &x[0] instead of that.
#include <glm/gtx/rotate_vector.hpp>         // Needed for glm::value_ptr(x). You can use &x[0] instead of that.


class scene {
private:
	map* activeMapPtr;

	GLsizei width, height;

	camera camera;

	//std::vector <planeTile> tileMap;
	grid grid;
	planeTile tile;
	coordinateAxes coordinateAxes;


	//ShaderProgram shaderProgramGrid;
	//GLuint vaoGrid, vboGrid, iboGrid;


	GLfloat zoomFactor;


	/*glm::mat4 projectionMat;
	glm::mat4 viewMat;*/
	glm::mat4 modelMat;


	
	bool isRightMouseButtonDown = false;
	//GLfloat timeTicks = 0;



public:
	void update();
	void render();
	bool handleEvent(const SDL_Event &e);

	scene(map*);
	~scene();
	bool init(void);
	void resize(GLsizei width, GLsizei height);

};
