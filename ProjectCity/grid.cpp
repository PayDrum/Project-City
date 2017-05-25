#include "grid.h"

grid::grid(map* mapInstancePtr) {

	this->mapInstancePtr = mapInstancePtr;

	//ShaderProgram shaderProgram;
}

grid::~grid() {

	//ShaderProgram shaderProgram;
}

bool grid::createGeometry() {

	modelPositions.clear();
	modelIndices.clear();

	GLfloat elevation = 0.001f;
	GLint indiceCounter = 0;
	for (int xIterator = -mapInstancePtr->getGridX(); xIterator <= mapInstancePtr->getGridX(); xIterator += 2)
	{
		modelPositions.push_back(glm::vec3(xIterator, -mapInstancePtr->getGridY(), elevation));
		modelPositions.push_back(glm::vec3(xIterator, mapInstancePtr->getGridY(), elevation));

		modelColors.push_back(glm::vec3(0, 0, 0));
		modelColors.push_back(glm::vec3(0, 0, 0));

		modelIndices.push_back(indiceCounter * 2);
		modelIndices.push_back(indiceCounter * 2 + 1);
		indiceCounter++;

	}

	for (int yIterator = -mapInstancePtr->getGridY(); yIterator <= mapInstancePtr->getGridY(); yIterator += 2)
	{
		modelPositions.push_back(glm::vec3(-mapInstancePtr->getGridX(), yIterator, elevation));
		modelPositions.push_back(glm::vec3(mapInstancePtr->getGridX(), yIterator, elevation));

		modelColors.push_back(glm::vec3(0, 0, 0));
		modelColors.push_back(glm::vec3(0, 0, 0));

		modelIndices.push_back(indiceCounter * 2);
		modelIndices.push_back(indiceCounter * 2 + 1);
		indiceCounter++;
	}

	//we scale the grid based on this formula, because we built it from -gridX to +gridx(and z). we want to map this from -1 to +1
	this->initialScale = 1.0f / (2.0f*mapInstancePtr->getGridX());
	//setUniformScale( 1.0f / (2.0f*mapInstancePtr->getGridX()));

	setScale(
		glm::vec3(
			1.0f / (2.0f*mapInstancePtr->getGridX())
			, 1.0f / (2.0f*mapInstancePtr->getGridY())
			, 1.0f)
	);

	setTranslate(glm::vec3(0.5f, 0.5f, 0));

	if (modelPositions.empty())
		return false;
	else
		return true;
}

bool grid::loadShaderProgram() {

	return shaderProgram.load(vertexShaderName, fragmentShaderName);

}
