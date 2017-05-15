#pragma once

#include <glm/glm.hpp>                  // Matrix library
#include <glm/gtc/matrix_transform.hpp> // Needed for glm::perspective() and friends.
#include <GL/glew.h>
#include <vector>
#include <string>

#include "shaderprogram.h"              // For shader management

class model {


	//ShaderProgram shaderProgram;

public:


	GLuint vao, vbo, ibo;

	//glm::mat4 modelMat;

	struct Vertex
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
	};

	std::vector<Vertex> vertices; // Source data for our model
	std::vector<GLushort> indices;

	glm::mat4 modelMat = glm::mat4(1.0f);
	glm::mat4 translateMat = glm::mat4(1.0f);
	glm::mat4 scaleMat = glm::mat4(1.0f);
	glm::mat4 rotationMat = glm::mat4(1.0f);

	GLfloat scaleFactor = 1.0f;
	GLfloat angle = 0.0f;

	model();
	~model();

	void render();
	void buildBuffers();

	void setScale(GLfloat);
	void setTranslate(glm::vec3);
	void setRotation(GLfloat, glm::vec3);
	void updateModelMat();

	

	virtual void createGeometry()=0;
	virtual bool loadShaderProgram()=0;
	virtual ShaderProgram* getShaderProgram()=0;


	//GLuint getShaderProgram() { return shaderProgram.getShaderProgram(); }

};
