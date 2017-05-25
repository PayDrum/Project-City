#pragma once

#include "model.h"

//this class creates the axis for the coordinate system for debugging purposes. x axis is red, y axis is green, z axis is blue(xyz=rgb)
class coordinateAxes :public model {

private:
	const std::string vertexShaderName = "shaders/coordinateaxes.vs";
	const std::string fragmentShaderName = "shaders/coordinateaxes.fs";

protected:

	virtual bool createGeometry();
	virtual bool loadShaderProgram();
	virtual GLenum getDrawingMode() { return GL_LINES; }

public:

	//GLfloat initialScale;



	coordinateAxes();
	~coordinateAxes();
	


};