#pragma once

#include <glm/glm.hpp>                  // Matrix library
#include <glm/gtc/matrix_transform.hpp> // Needed for glm::perspective() and friends.
#include <GL/glew.h>
#include <vector>
#include <string>

#include "shaderprogram.h"              // For shader management
#include "model.h"
#include "map.h"


class planeTile : public model {

	//ShaderProgram shaderProgram;
	const std::string vertexShaderName = "shaders/groundplane.vs";
	const std::string fragmentShaderName = "shaders/groundplane.fs";

	GLuint tbo; //transformation matrix buffer for instancing purpose

	GLfloat initialScale = 1.0f;

	struct InstanceProperties
	{
		glm::mat4 translateMat;
		glm::vec3 color;

		InstanceProperties(glm::mat4 mat = glm::mat4(1.0f), GLfloat r = 0.0f, GLfloat g = 0.0f, GLfloat b = 0.0f)
		{
			translateMat = mat;
			color.x = r;
			color.y = g;
			color.z = b;
		}
	};
	std::vector<InstanceProperties> propertyCollection;

	map* mapInstanceptr;

public:

	planeTile(map*);
	~planeTile();

	virtual bool createGeometry();
	virtual bool loadShaderProgram();
	virtual GLenum getDrawingMode() {return GL_TRIANGLES;}

	void createTileMap();

	//virtual void render();
	//virtual void buildBuffers();

	void renderInstanced();
	void buildInstancedBuffers();

	/*void setScale(GLfloat);
	void setTranslate(glm::vec3);
	void setRotation(GLfloat, glm::vec3);
	void updateModelMat();*/


	ShaderProgram* getShaderProgram() { return &shaderProgram; }

	/*glm::mat4 getModelMat() {
		return this->modelMat;
	}*/

};
