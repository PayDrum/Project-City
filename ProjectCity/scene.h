#pragma once

#include <SDL\SDL.h>
#include <vector>

#include "map.h"
#include "shaderprogram.h"              // For shader management
#include "planetile.h"
#include "grid.h"
#include <glm/glm.hpp>                  // Matrix library
#include <glm/gtc/matrix_transform.hpp> // Needed for glm::perspective() and friends.
#include <glm/gtc/type_ptr.hpp>         // Needed for glm::value_ptr(x). You can use &x[0] instead of that.


class scene {
private:
	map* activeMapPtr;

	GLsizei width, height;

	planeTile tile;
	std::vector <planeTile> tileMap;
	grid grid;


	ShaderProgram shaderProgramGrid;
	GLuint vaoGrid, vboGrid, iboGrid;

	/*struct Vertex
	{
		GLfloat position[3];
		GLfloat color[3];

		Vertex(GLfloat x = 0.0, GLfloat y = 0.0, GLfloat z = 0.0, GLfloat r = 0.0f, GLfloat g = 0.0f, GLfloat b = 0.0f)
		{
			position[0] = x;
			position[1] = y;
			position[2] = z;
			color[0] = r;
			color[1] = g;
			color[2] = b;
		}
	};*/
	

	//std::vector<Vertex> gridVertices; // Source data for our model
	//std::vector<GLushort> gridIndices;

	glm::mat4 mvpMat;
	glm::mat4 mvpMattwo;

	glm::mat4 projectionMat;
	glm::mat4 viewMat;
	glm::mat4 modelMat;


	glm::vec3 cameraEyePosition=/* glm::normalize*/(glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 cameraCenterPosition= glm::vec3(0.5f, 0.0f, 0.5f);
	glm::vec4 cameraClippingRange = glm::vec4(-0.5f, 0.5f, 0.5f, -0.5f);

	GLfloat zoomFactor = 100.0f;
	GLfloat cameraRadius = 1.0f;
	GLfloat horizontalAngle = 0;
	GLfloat verticalAngle = 0;

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
