#include "model.h"

model::model() {

	//ShaderProgram shaderProgram;
}

model::~model() {

	//ShaderProgram shaderProgram;
}


void model::buildBuffers() {

	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(struct Vertex), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices[0], GL_STATIC_DRAW);


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(getShaderProgram()->getPositionAttribLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (const GLvoid*)offsetof(struct Vertex, position));
	glEnableVertexAttribArray(getShaderProgram()->getPositionAttribLocation());

	glVertexAttribPointer(getShaderProgram()->getColorAttribLocation(), 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (const GLvoid*)offsetof(struct Vertex, color));
	glEnableVertexAttribArray(getShaderProgram()->getColorAttribLocation()); // Bind our second VBO as being the active buffer and storing vertex attributes (colors)


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

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