#include "camera.h"

camera::camera()
{

	//initial camera settings
	eyePosition = glm::vec3(0.0f, 0.0f, 1.0f);
	centerPosition = glm::vec3(0.5f, 0.5f, 0.0f);
	upVector = glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f));
	calculateCameraRightVector();
	verticalAngle = 54.0f;
	cameraClippingRange = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f);
	
	updateViewMat();
	updateProjectionMat();



}

void camera::updateViewMat()
{
	viewMat = glm::lookAt(eyePosition, centerPosition, upVector);
}


void camera::updateProjectionMat()
{
	projectionMat = glm::ortho(cameraClippingRange.x, cameraClippingRange.y, cameraClippingRange.z, cameraClippingRange.w, -3.0f, 3.0f);

	// Set up projection matrix and model matrix etc.
	//float fovy = 45.0f;
	//viewMat = glm::lookAt((glm::vec3(0.5f, 0.705, 0.5f)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 1.0f, -1.0f));
}

void camera::calculateCameraRightVector()
{
	this->rightVector = glm::cross(centerPosition - eyePosition, upVector);
	this->rightVector = glm::normalize(this->rightVector);
}

void camera::calculateCameraForwardtVector()
{
	this->forwardVector = glm::vec3(upVector.x, upVector.y, 0);
	this->forwardVector = glm::normalize(this->forwardVector);
}

void camera::calculateCameraUpVector()
{
	this->upVector = glm::cross(rightVector, centerPosition - eyePosition);
	this->upVector = glm::normalize(this->upVector);
}

void camera::truckCamera(truckDirection direction)
{
	calculateCameraRightVector();
	this->centerPosition += (static_cast<float> (direction)) * rightVector * cameraMovementScale;
	this->eyePosition += (static_cast<float> (direction)) * rightVector * cameraMovementScale;
	updateViewMat();
}

void camera::dollyCamera(dollyDirection direction)
{
	calculateCameraForwardtVector();
	this->centerPosition += (static_cast<float> (direction)) * forwardVector * cameraMovementScale;
	this->eyePosition += (static_cast<float> (direction)) * forwardVector * cameraMovementScale;
	updateViewMat();
}

void camera::pitchCamera(GLint degree)
{
	if ((this->verticalAngle - degree) > 5
		&& (this->verticalAngle - degree) < 85)
	{
		this->verticalAngle -=  degree;
		this->eyePosition = glm::rotate(eyePosition - centerPosition, glm::radians(1.0f* degree), rightVector) + centerPosition;
		calculateCameraUpVector();
		updateViewMat();
	}
}

void camera::yawCamera(GLint degree)
{
	this->eyePosition = glm::rotate(eyePosition - centerPosition, glm::radians(0.5f*degree), glm::vec3(0, 0, 1.0f)) + centerPosition;
	this->rightVector = glm::cross(glm::vec3(0, 0, 1.0f), eyePosition - centerPosition);
	calculateCameraUpVector();
	updateViewMat();
}

void camera::zoomCamera(GLint degree) 
{
	GLfloat zoomRange = static_cast<float> (degree) * zoomScale;
	this->cameraClippingRange += glm::vec4(zoomRange, -zoomRange, zoomRange, -zoomRange);
	updateProjectionMat();
}

camera::~camera() {


}
