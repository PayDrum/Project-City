#pragma once


#include "model.h"
#include "map.h"


class grid : public model {

private:
	const std::string vertexShaderName = "shaders/grid.vs";
	const std::string fragmentShaderName = "shaders/grid.fs";
	map* mapInstancePtr;

protected:

	virtual bool createGeometry();
	virtual bool loadShaderProgram();
	virtual GLenum getDrawingMode() { return GL_LINES; }

public:
	GLfloat initialScale;
	
	grid(map*);
	~grid();

	


};

