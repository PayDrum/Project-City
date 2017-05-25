#include "scene.h"

scene::scene(map* activeMapPtr) : tile(activeMapPtr), grid(activeMapPtr),camera() {

	this->activeMapPtr = activeMapPtr;

	//planeTile tile(activeMapPtr);
	//grid grid(activeMapPtr);

	// These OpenGL functions must be defined by the OpenGL (or through GLEW) for this to work..
	assert(glBindBuffer != 0);
	assert(glBindVertexArray != 0);
	assert(glBufferData != 0);
	assert(glClear != 0);
	assert(glClearColor != 0);
	assert(glCullFace != 0);
	assert(glDepthFunc != 0);
	assert(glDeleteBuffers != 0);
	assert(glDeleteVertexArrays != 0);
	assert(glDisableVertexAttribArray != 0);
	assert(glDrawArrays != 0);
	assert(glEnable != 0);
	assert(glGenVertexArrays != 0);
	assert(glGenBuffers != 0);
	assert(glUseProgram != 0);
	assert(glUniformMatrix4fv != 0);
	assert(glVertexAttribPointer != 0);
	assert(glViewport != 0);
}



bool scene::init() {

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//load the tile, and build it in an instanced manner
	if (!tile.load())
		return false;
	tile.createTileMap();
	tile.buildInstancedBuffers();

	//load the grid
	if (!grid.load())
		return false;
	// Create tile geometry

	if (!coordinateAxes.load())
		return false;

	return true;

}




void scene::render() {


	// Clear background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//culling settings
	glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	glDisable(GL_CULL_FACE);

	// Calculate model transformation
	//modelMat = glm::mat4(1.0f);
	//modelMat = glm::translate(modelMat, glm::vec3(1.0, 0.0, 0.0)); // Translate object +1 on x-axis after rotation
	//modelMat = glm::rotate(modelMat, rotation, glm::vec3(0.0, 1.0, 0.0)); // Rotate object around y-axis
	//modelMat = glm::scale(modelMat, glm::vec3(0.3f, 0.3f, 0.3f));

	//build the mvp mat for each model
	tile.mvpMat = camera.projectionMat * camera.viewMat *tile.getModelMat();
	grid.mvpMat = camera.projectionMat * camera.viewMat * grid.getModelMat();
	coordinateAxes.mvpMat = camera.projectionMat * camera.viewMat * coordinateAxes.getModelMat();

	//assign the uniform and render the tilemap(not a single tile)
	tile.useShaderProgram();
	glUniformMatrix4fv(glGetUniformLocation(tile.getShaderProgram()->getShaderProgramHandler(), "mvpmatrix"), 1, GL_FALSE, glm::value_ptr(tile.mvpMat));
	tile.renderInstanced();
	//tile.render();

	//assign the uniform and render the grid
	grid.useShaderProgram();
	glUniformMatrix4fv(glGetUniformLocation(grid.getShaderProgram()->getShaderProgramHandler(), "mvpmatrix"), 1, GL_FALSE, glm::value_ptr(grid.mvpMat));
	grid.render();

	coordinateAxes.useShaderProgram();
	glUniformMatrix4fv(glGetUniformLocation(coordinateAxes.getShaderProgram()->getShaderProgramHandler(), "mvpmatrix"), 1, GL_FALSE, glm::value_ptr(coordinateAxes.mvpMat));
	coordinateAxes.render();
}


void scene::resize(GLsizei width, GLsizei height)
{

	// Update OpenGL viewport to match window system's window size
	this->width = width;
	this->height = height;
	glViewport(0, 0, width, height);

	camera.calculateProjectionMat();
	camera.calculateViewMat();
	//projectionMat = glm::ortho(cameraClippingRange.x, cameraClippingRange.y, cameraClippingRange.z, cameraClippingRange.w,-3.0f,3.0f);
	
	//viewMat = glm::lookAt(cameraEyePosition, cameraCenterPosition, glm::vec3(1.0f, 1.0f, 1.0f));

	// Set up projection matrix and model matrix etc.
	//float fovy = 45.0f;
	//viewMat = glm::lookAt((glm::vec3(0.5f, 0.705, 0.5f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 1.0f, -1.0f));

}


void scene::update() {

	//timeTicks += timestep * 5;
	// Rotate object (one rotation / 10 seconds)
	//rotation += glm::two_pi<float>() * 0.1f * timestep;

}

bool scene::handleEvent(const SDL_Event &e)
{

	if (e.type == SDL_MOUSEWHEEL) {

		zoomFactor = 0;

		//zoomout
		if (e.wheel.y < 0)
			zoomFactor--;

		//zoomin
		if (e.wheel.y > 0)
			zoomFactor++;
		zoomFactor /= 100;

		camera.cameraClippingRange += glm::vec4(zoomFactor, -zoomFactor, zoomFactor, -zoomFactor);
		camera.calculateProjectionMat();

		/*eye.x += (zoomFactor / 100);
		eye.y += (zoomFactor / 100);
		eye.z += (zoomFactor / 100);
		viewMat = glm::lookAt(eye, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));*/


		//projectionMat = glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f, 0.0f, zoomFactor);
	}
	if (e.type == SDL_KEYDOWN) {
		glm::vec3 panVector;
		switch (e.key.keysym.sym) {

		case(SDLK_RIGHT):
			panVector.x++; panVector.y--; break;
		case (SDLK_LEFT):
			panVector.x--; panVector.y++; break;
		case (SDLK_DOWN):
			panVector.y--; panVector.x--; break;
		case (SDLK_UP):
			panVector.y++; panVector.x++; break;
		}
		panVector /= 100;

		camera.eyePosition += panVector;
		camera.centerPosition += panVector;
		camera.calculateViewMat();
		//bullshit += glm::vec4(panFactor, -panFactor, -panFactor, panFactor);

	}

	if (e.type == SDL_MOUSEBUTTONDOWN) {

		GLfloat pixels[3];
		glReadPixels(e.button.x, this->height - 1 - e.button.y, 1, 1, GL_RGB, GL_FLOAT, &pixels[0]);
		//printf("%f , %f, %f", pixels[0], pixels[1], pixels[2]);
		printf("%d , %d", e.button.x, e.button.y);
	}
	//if (e.type == SDL_MOUSEMOTION) {
	//	//switch(e.)
	//	if (e.motion.xrel > 0)
	//		horizontalAngle++;
	//	if (e.motion.xrel < 0)
	//		horizontalAngle--;


	//	if (e.motion.yrel > 0)
	//		verticalAngle++;
	//	if (e.motion.yrel < 0)
	//		verticalAngle--;

	//	if (verticalAngle > 89.0f)
	//		verticalAngle = 89.0f;
	//	if (verticalAngle < 5.0f)
	//		verticalAngle = 5.0f;

	//	cameraEyePosition.x =
	//		cos(verticalAngle* glm::pi<float>() / 180) * sin(horizontalAngle* glm::pi<float>() / 180);
	//	cameraEyePosition.y =
	//		sin(verticalAngle* glm::pi<float>() / 180);
	//	cameraEyePosition.z =
	//		cos(verticalAngle* glm::pi<float>() / 180) * cos(horizontalAngle* glm::pi<float>() / 180);


	//	viewMat = glm::lookAt(cameraEyePosition, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	//}


	return true;

}

scene::~scene() {

	// Clean up everything
	glUseProgram(0); // Shader state
	//glDisableVertexAttribArray(tile.getShader().getPositionAttribLocation()); // VBO state
	//glDisableVertexAttribArray(tile.getShader().getColorAttribLocation());
	//glDisableVertexAttribArray(tile.getShader().getPositionAttribLocation()); // VBO state
	//glDisableVertexAttribArray(tile.getShader().getColorAttribLocation());
	//glDeleteBuffers(1, &tile.vao); // Allocated vertex data
	//glDeleteVertexArrays(1, &tile.vao); // Allocated object data

	/*if (flagTexture)
		delete flagTexture;*/

}
