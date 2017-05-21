#pragma once

#include <glm/glm.hpp>                  // Matrix library
#include <glm/gtc/matrix_transform.hpp> // Needed for glm::perspective() and friends.
#include <GL/glew.h>
#include <vector>
#include <string>

#include "shaderprogram.h"              // For shader management

class model {



public:

	glm::mat4 mvpMat = glm::mat4(1.0f);

	model();
	~model();

	void buildBuffers();
	bool load();
	void render();
	void useShaderProgram();

	ShaderProgram* getShaderProgram() {return &shaderProgram; }
	glm::mat4 getModelMat() { return this->modelMat; }

	void setScale(GLfloat);
	void setTranslate(glm::vec3);
	void setRotation(GLfloat, glm::vec3);

protected:

	ShaderProgram shaderProgram;
	
	GLuint vao, vbo, ibo;

	std::vector<glm::vec3> modelPositions;
	std::vector<glm::vec3> modelColors;
	std::vector<glm::vec2> modelUVs;
	std::vector<GLushort> indices;

	GLuint vboPositions, vboColors, vboUVs;

	glm::mat4 modelMat = glm::mat4(1.0f);
	glm::mat4 translateMat = glm::mat4(1.0f);
	glm::mat4 scaleMat = glm::mat4(1.0f);
	glm::mat4 rotationMat = glm::mat4(1.0f);

	GLfloat scaleFactor = 1.0f;
	GLfloat angle = 0.0f;

	virtual bool createGeometry() = 0;
	virtual bool loadShaderProgram() = 0;

	void updateModelMat();


	

private:

	void generateVertexArrayObject(GLuint location, GLuint numberOfElements);


};
