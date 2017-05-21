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
	indices.clear();

	GLfloat xStep = -mapInstancePtr->getGridX();
	GLfloat zStep = -mapInstancePtr->getGridZ();;
	GLint indiceCounter = 0;
	for (int xIterator = -mapInstancePtr->getGridX(); xIterator <= mapInstancePtr->getGridX(); xIterator += 2)
	{
		modelPositions.push_back(glm::vec3(xIterator, 0.05f, -mapInstancePtr->getGridZ()));
		modelPositions.push_back(glm::vec3(xIterator, 0.05f, mapInstancePtr->getGridZ()));

		modelColors.push_back(glm::vec3(0, 0, 0));
		modelColors.push_back(glm::vec3(0, 0, 0));

		indices.push_back(indiceCounter * 2);
		indices.push_back(indiceCounter * 2 + 1);
		indiceCounter++;

	}

	for (int zIterator = -mapInstancePtr->getGridZ(); zIterator <= mapInstancePtr->getGridZ(); zIterator += 2)
	{
		modelPositions.push_back(glm::vec3(-mapInstancePtr->getGridX(), 0.05f, zIterator));
		modelPositions.push_back(glm::vec3(mapInstancePtr->getGridX(), 0.05f, zIterator));

		modelColors.push_back(glm::vec3(0, 0, 0));
		modelColors.push_back(glm::vec3(0, 0, 0));

		indices.push_back(indiceCounter * 2);
		indices.push_back(indiceCounter * 2 + 1);
		indiceCounter++;
	}

	//we scale the grid based on this formula, because we built it from -gridX to +gridx(and z). we want to map this from -1 to +1
	this->initialScale = 1.0f / (2.0f*mapInstancePtr->getGridX());
	setScale(initialScale);


	setTranslate(glm::vec3(0.5f, 0, 0.5f));

	if (modelPositions.empty())
		return false;
	else
		return true;
}

bool grid::loadShaderProgram() {

	return shaderProgram.load(vertexShaderName, fragmentShaderName);

}
