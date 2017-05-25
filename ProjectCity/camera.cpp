#include "camera.h"

camera::camera() {

	//initial camera settings
	eyePosition = glm::vec3(0.0f, 0.0f, 1.0f);
	centerPosition = glm::vec3(0.5f, 0.5f, 0.0f);
	topVector = glm::vec3(1.0f);
	cameraClippingRange = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f);

}

void camera::calculateViewMat() {

	viewMat = glm::lookAt(eyePosition, centerPosition,topVector);

}


void camera::calculateProjectionMat() {

	projectionMat = glm::ortho(cameraClippingRange.x, cameraClippingRange.y, cameraClippingRange.z, cameraClippingRange.w, -3.0f, 3.0f);

}

camera::~camera() {


}
