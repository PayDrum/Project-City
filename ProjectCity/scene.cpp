#include "scene.h"

scene::scene(map* activeMapPtr) : tile(activeMapPtr), grid(activeMapPtr), camera() {

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

	//build the mvp mat for each model
	tile.mvpMat = camera.getProjectionMat() * camera.getViewMat() *tile.getModelMat();
	grid.mvpMat = camera.getProjectionMat() * camera.getViewMat() * grid.getModelMat();
	coordinateAxes.mvpMat = camera.getProjectionMat() * camera.getViewMat() * coordinateAxes.getModelMat();

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

	//we technically dont need to do these here, because our orthographic arguments are fixed and are not changed by resize. To be moved to scene constructor.
	//camera.calculateProjectionMat();
	//camera.calculateViewMat();
}


void scene::update() {

	//timeTicks += timestep * 5;
	// Rotate object (one rotation / 10 seconds)
	//rotation += glm::two_pi<float>() * 0.1f * timestep;

}

bool scene::handleEvent(const SDL_Event &e)
{

	if (e.type == SDL_MOUSEWHEEL) 
	{
		camera.zoomCamera(e.wheel.y);
	}

	if (e.type == SDL_KEYDOWN) 
	{
		if (e.key.keysym.sym == SDLK_RIGHT) {
			camera.truckCamera(camera::truckDirection::right);
		}
		else if (e.key.keysym.sym == SDLK_LEFT) {
			camera.truckCamera(camera::truckDirection::left);
		}
		else if (e.key.keysym.sym == SDLK_UP) {
			camera.dollyCamera(camera::dollyDirection::forward);
		}
		else if (e.key.keysym.sym == SDLK_DOWN) {
			camera.dollyCamera(camera::dollyDirection::backwards);
		}
	}

	if (e.type == SDL_MOUSEBUTTONDOWN) 
	{
		if (e.button.button == SDL_BUTTON_LEFT) {
			//object picker
			GLfloat pixels[3];
			glReadPixels(e.button.x, this->height - 1 - e.button.y, 1, 1, GL_RGB, GL_FLOAT, &pixels[0]);
			//printf("%f , %f, %f", pixels[0], pixels[1], pixels[2]);
			//printf("%d , %d", e.button.x, e.button.y);
		}
		if (e.button.button == SDL_BUTTON_RIGHT)
		{
			SDL_SetRelativeMouseMode(SDL_TRUE);
			isRightMouseButtonDown = true;
		}
	}

	if (e.type == SDL_MOUSEBUTTONUP) {

		if (e.button.button == SDL_BUTTON_RIGHT)
		{
			SDL_SetRelativeMouseMode(SDL_FALSE);
			isRightMouseButtonDown = false;
		}
	}

	if (e.type == SDL_MOUSEMOTION && isRightMouseButtonDown)
	{
		if (e.motion.yrel != 0)
			camera.pitchCamera(e.motion.yrel);

		if (e.motion.xrel != 0)
			camera.yawCamera(e.motion.xrel);
	}
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
