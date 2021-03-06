#include "planetile.h"

planeTile::planeTile(map* mapInstancePtr) {


	this->mapInstanceptr = mapInstancePtr;
	setUniformScale(1.0f / (2.0f* mapInstancePtr->getGridX()));
	//ShaderProgram shaderProgram;
}

planeTile::~planeTile() {

	glUseProgram(0); // Shader state
	//glDisableVertexAttribArray(getShaderProgram().getPositionAttribLocation()); // VBO state
	//glDisableVertexAttribArray(tile.getShader().getColorAttribLocation());
	//glDisableVertexAttribArray(tile.getShader().getPositionAttribLocation()); // VBO state
	//glDisableVertexAttribArray(tile.getShader().getColorAttribLocation());
	glDeleteBuffers(1, &vao); // Allocated vertex data
	glDeleteVertexArrays(1, &vao); // Allocated object data

	//ShaderProgram shaderProgram;
}

bool planeTile::createGeometry() {

	modelPositions.clear();
	modelIndices.clear();

	modelPositions.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));
	modelPositions.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	modelPositions.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	modelPositions.push_back(glm::vec3(1.0f, -1.0f, 0.0f));

	modelColors.push_back(glm::vec3(0.5f, 0.5f, 0.5f));;
	modelColors.push_back(glm::vec3(1, 0.5f, 0.5f));
	modelColors.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	modelColors.push_back(glm::vec3(0.5f, 0.5f, 0.5f));


	modelIndices.push_back(0);
	modelIndices.push_back(3);
	modelIndices.push_back(2);
	modelIndices.push_back(0);
	modelIndices.push_back(1);
	modelIndices.push_back(3);

	//
	//this->initialScale = 1.0f;
	//setScale(this->initialScale);
	if (modelPositions.empty())
		return false;
	else
		return true;
}

bool planeTile::loadShaderProgram() {

	return shaderProgram.load(vertexShaderName, fragmentShaderName);
}


void planeTile::buildInstancedBuffers() {

	glGenBuffers(1, &tbo);
	glBindBuffer(GL_ARRAY_BUFFER, tbo);
	glBufferData(GL_ARRAY_BUFFER, propertyCollection.size() * sizeof(InstanceProperties), &propertyCollection[0], GL_STATIC_DRAW);

	//revision needed
	glBindVertexArray(vao);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceProperties), (const GLvoid*)(sizeof(GLfloat) * 0));
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceProperties), (const GLvoid*)(sizeof(GLfloat) * 4));
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceProperties), (const GLvoid*)(sizeof(GLfloat) * 8));
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceProperties), (const GLvoid*)(sizeof(GLfloat) * 12));
	glVertexAttribPointer(6, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceProperties), (const GLvoid*)(sizeof(GLfloat) * 16));
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glEnableVertexAttribArray(6);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}


void planeTile::renderInstanced() {

	glBindVertexArray(vao);
	glDrawElementsInstanced(GL_TRIANGLES
		, static_cast<GLsizei>(modelIndices.size())
		, GL_UNSIGNED_SHORT
		, &modelIndices[0],
		mapInstanceptr->getGridX() * mapInstanceptr->getGridY());

	glBindVertexArray(0);
}


void planeTile::createTileMap() {

	InstanceProperties property;
	//GLfloat offsetX = 1.0f / (mapInstanceptr->getGridX());


	for (int yIterator = -mapInstanceptr->getGridY(); yIterator < mapInstanceptr->getGridY(); yIterator += 2)
	{
		for (int xIterator = -mapInstanceptr->getGridX(); xIterator < mapInstanceptr->getGridX(); xIterator += 2)
		{
			property.translateMat = glm::translate(glm::mat4(1.0f),
				glm::vec3(xIterator + 1.0f, yIterator + 1.0f, 0));

			//this color is assigned this way for later object picking
			property.color = glm::vec3(xIterator + mapInstanceptr->getGridX(), 255, yIterator + mapInstanceptr->getGridY()) / 510.0f;

			propertyCollection.push_back(property);
		}
	}
	setTranslate(glm::vec3(0.5f, 0.5f, 0));
}
