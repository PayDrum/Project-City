#pragma once

#include <glm/glm.hpp>                  // Matrix library
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp> // Needed for glm::perspective() and friends.
#include <glm/gtx/rotate_vector.hpp>         // Needed for glm::value_ptr(x). You can use &x[0] instead of that.



 class camera {

 private:

	 const GLfloat cameraMovementScale = 0.01f;
	 const GLfloat zoomScale = 0.01f;

	 //GLfloat horizontalAngle;
	 GLfloat verticalAngle;

	 glm::vec3 eyePosition;
	 glm::vec3 centerPosition;
	 glm::vec3 upVector;
	 glm::vec3 rightVector;
	 glm::vec3 forwardVector;
	 glm::vec4 cameraClippingRange;

	 glm::mat4 viewMat;
	 glm::mat4 projectionMat;

	 void updateViewMat();
	 void updateProjectionMat();

	 void calculateCameraRightVector();
	 void calculateCameraForwardtVector();
	 void calculateCameraUpVector();

 public :

	 enum truckDirection
	 {
		 right = 1,
		 left = -1

	 };

	 enum dollyDirection
	 {
		 forward = 1,
		 backwards = -1
	 };

	 glm::mat4 getViewMat() { return this->viewMat; }
	 glm::mat4 getProjectionMat() { return this->projectionMat; }
	 
	 void truckCamera(truckDirection);
	 void dollyCamera(dollyDirection);
	 void pitchCamera(GLint);
	 void yawCamera(GLint);
	 void zoomCamera(GLint);

	 camera();
	 ~camera();

 
};
