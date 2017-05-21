#include "model.h"

model::model() {

}

model::~model() {

}


void model::buildBuffers() {

	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	glGenVertexArrays(1, &vao);

	if (!modelPositions.empty()) {

		glGenBuffers(1, &vboPositions);
		glBindBuffer(GL_ARRAY_BUFFER, vboPositions);
		glBufferData(GL_ARRAY_BUFFER, modelPositions.size() * 3 * sizeof(GLfloat), &modelPositions[0], GL_STATIC_DRAW);

		generateVertexArrayObject(getShaderProgram()->getPositionAttribLocation(), 3);
	}

	if (!modelColors.empty()) {
		glGenBuffers(1, &vboColors);
		glBindBuffer(GL_ARRAY_BUFFER, vboColors);
		glBufferData(GL_ARRAY_BUFFER, modelColors.size() * 3 * sizeof(GLfloat), &modelColors[0], GL_STATIC_DRAW);

		generateVertexArrayObject(getShaderProgram()->getColorAttribLocation(), 3);

	}

	if (!indices.empty()) {
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);
	}

	

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void model::generateVertexArrayObject(GLuint location, GLuint numberOfElements) {

	glBindVertexArray(vao);
	glVertexAttribPointer(location, numberOfElements, GL_FLOAT, GL_FALSE, numberOfElements * sizeof(GL_FLOAT), 0);
	glEnableVertexAttribArray(location);
	glBindVertexArray(0);

}

bool model::load() {

	bool allOk=true;

	allOk &= loadShaderProgram();
	allOk &= createGeometry();
	try {
		buildBuffers();
	}
	catch (...) {
		allOk = false;
	}
	return allOk;
}

void model::render() {

	glBindVertexArray(vao);
	glDrawElements(GL_LINES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_SHORT, &indices[0]);

	glBindVertexArray(0);
}



void model::setScale(GLfloat scale) {

	this->scaleFactor *= scale;
	this->scaleMat = glm::scale(this->scaleMat, glm::vec3(1.0f)*scaleFactor);
	updateModelMat();
}

void model::setRotation(GLfloat angle, glm::vec3 axis) {

	this->rotationMat = glm::rotate(this->rotationMat, angle, axis);
	updateModelMat();
}

void model::setTranslate(glm::vec3 translateVector) {

	this->translateMat = glm::translate(this->translateMat, translateVector);
	updateModelMat();
}

void model::updateModelMat() {

	this->modelMat = translateMat * rotationMat * scaleMat;
}

void model::useShaderProgram() {

	glUseProgram(shaderProgram.getShaderProgramHandler());
}

//void model::createVboBuffer(size_t vertexStructSize, void* verticesPtr) 
//{
//	glGenBuffers(1, &vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBufferData(GL_ARRAY_BUFFER, *verticesPtr * vertexStructSize, &vertices[0], GL_STATIC_DRAW);
//
//}