#pragma once

#include <glm/glm.hpp>                  // Matrix library
#include <glm/gtc/matrix_transform.hpp> // Needed for glm::perspective() and friends.
#include <GL/glew.h>
#include <vector>
#include <string>

#include "shaderprogram.h"              // For shader management

//this class needs rewriting but further down the development path. The buffers are made too specifically
//approach: the vertex struct should be defined on child level. the buffer building has to be designed based on the child vertex
class model {


	//ShaderProgram shaderProgram;

public:

	model();
	~model();

	void render();

	void setScale(GLfloat);
	void setTranslate(glm::vec3);
	void setRotation(GLfloat, glm::vec3);

	glm::mat4 getModelMat() { return this->modelMat; }

	void buildBuffers();

	
	
	//glm::mat4 modelMat;

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

	//std::vector<Vertex> vertices; // Source data for our model

	////this is done so that the child can define its own vertex data object
	//virtual GLuint getVertexStructSize() = 0;
	//virtual GLuint getVertexStructNumberOfAttributes() = 0; //returns the number of triplets(or duos) of attributes in the defined vertex. 
	//virtual GLuint getVertexVectorSize() = 0;
	//virtual void* getVertexArray() = 0;


	//GLuint getShaderProgram() { return shaderProgram.getShaderProgram(); }
protected:

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

	virtual void createGeometry() = 0;
	virtual bool loadShaderProgram() = 0;
	virtual ShaderProgram* getShaderProgram() = 0;

	void updateModelMat();


	

private:

	void generateVertexArrayObject(GLuint location, GLuint numberOfElements);


};
