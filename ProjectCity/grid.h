#pragma once

#include <glm/glm.hpp>                  // Matrix library
#include <glm/gtc/matrix_transform.hpp> // Needed for glm::perspective() and friends.
#include <GL/glew.h>
#include <vector>
#include <string>

#include "shaderprogram.h"              // For shader management
#include "model.h"
#include "map.h"


class grid : public model {

	ShaderProgram shaderProgram;
	map* mapInstancePtr;

public:
	const std::string vertexShaderName = "shaders/grid.vs";
	const std::string fragmentShaderName = "shaders/grid.fs";

	GLfloat initialScale;


	
	grid(map*);
	~grid();
	virtual void createGeometry();
	//void render();
	virtual bool loadShaderProgram();
	//void buildBuffers();

	ShaderProgram* getShaderProgram() { return &shaderProgram; }


};

