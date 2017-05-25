#include "coordinateAxes.h"

coordinateAxes::coordinateAxes() {

	this->setTranslate(glm::vec3(0, 0, -0.2f));
}

coordinateAxes::~coordinateAxes() {

}

bool coordinateAxes::createGeometry() {

	modelPositions.clear();
	modelIndices.clear();
	modelColors.clear();

	modelPositions.push_back(glm::vec3(0, 0, 0));
	modelPositions.push_back(glm::vec3(1.0f, 0, 0));
	modelPositions.push_back(glm::vec3(0, 1.0f, 0));
	modelPositions.push_back(glm::vec3(0, 0, 1.0f));


	modelIndices.push_back(0);
	modelIndices.push_back(1);

	modelIndices.push_back(0);
	modelIndices.push_back(2);

	modelIndices.push_back(0);
	modelIndices.push_back(3);

	modelColors.push_back(glm::vec3(0, 0, 0));
	modelColors.push_back(glm::vec3(1, 0, 0));
	modelColors.push_back(glm::vec3(0, 1, 0));
	modelColors.push_back(glm::vec3(0, 0, 1));

	if (modelPositions.empty())
		return false;
	else
		return true;
}

bool coordinateAxes::loadShaderProgram() {

	return shaderProgram.load(vertexShaderName, fragmentShaderName);

}