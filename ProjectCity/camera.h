#pragma once

#include <glm/glm.hpp>                  // Matrix library
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp> // Needed for glm::perspective() and friends.


 class camera {

 private :

	 

	 GLfloat zoomFactor = 100.0f;
	 GLfloat cameraRadius = 1.0f;
	 GLfloat horizontalAngle = 0;
	 GLfloat verticalAngle = 0;

 public:

	 glm::vec3 eyePosition ;
	 glm::vec3 centerPosition;
	 glm::vec3 topVector;
	 glm::vec4 cameraClippingRange ;

	 glm::mat4 viewMat;
	 glm::mat4 projectionMat;

	 void calculateViewMat();
	 void calculateProjectionMat();

	 camera();
	 ~camera();
};
