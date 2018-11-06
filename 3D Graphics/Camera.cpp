#include "Camera.h"
#include <math.h>
#include "gl/glew.h"
#include "gl/wglew.h"
#pragma comment(lib, "glew32.lib")
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_inverse.hpp"
#include "console.h"
Camera::Camera()
{
	velocity = 0;
	rotation = 0;
}


Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix()
{
	return viewMatrix;
}

void Camera::updateCamera()
{
	cameraPosition.x += velocity * cos((90 + rotation)*(PI / 180.0));
	cameraPosition.z += velocity * sin((90 + rotation)*(PI / 180.0));
	cameraLook.x = -sin(rotation*(PI / 180.0)) * 100;
	cameraLook.z = cos(rotation*(PI / 180.0)) * 100;

	if (rotation >= 360) {
		rotation = 0;
	}
	viewMatrix = glm::lookAt(cameraPosition, cameraLook+ cameraPosition, cameraOrientation);
}

void Camera::increaseY()
{
	cameraPosition.y+=2;
}

void Camera::decreaseY()
{
	cameraPosition.y-=2;
}

float Camera::getRotation()
{
	return rotation;
}

float Camera::getCameraX()
{
	return cameraPosition.x;
}

float Camera::getCameraY()
{
	return cameraPosition.y;
}

float Camera::getCameraZ()
{
	return cameraPosition.z;
}

float Camera::getZoom()
{
	return zoom;
}
void Camera::setZoom(int z)
{
	zoom = z;
}
void Camera::setZoom(bool z)
{
	if (z)
	{
		//zoom += 1.08* adjustedDeltaT;
	}
	else {
		//zoom -= 1.08* adjustedDeltaT;
	}
}
void Camera::left()
{
	rotation --;
}
void Camera::right()
{
	rotation ++;
}

void Camera::accelerate()
{
	velocity = 1;
}
void Camera::brake()
{
	
}
void Camera::pedalOff()
{
	velocity = 0;
}
void Camera::reverse()
{
	velocity = -1;
}
void Camera::strafeLeft()
{
	cameraPosition.x += 1 * cos((90 + rotation-90)*(PI / 180.0));
	cameraPosition.z += 1 * sin((90 + rotation-90)*(PI / 180.0));
	cameraLook.x = -sin(rotation-90*(PI / 180.0)) * 100;
	cameraLook.z = cos(rotation-90*(PI / 180.0)) * 100;
	if (rotation >= 360) {
		rotation = 0;
	}
	viewMatrix = glm::lookAt(cameraPosition, cameraLook + cameraPosition, cameraOrientation);
}
void Camera::strafeRight()
{
	cameraPosition.x += 1 * cos((90 + rotation + 90)*(PI / 180.0));
	cameraPosition.z += 1 * sin((90 + rotation + 90)*(PI / 180.0));
	cameraLook.x = -sin(rotation + 90 * (PI / 180.0)) * 100;
	cameraLook.z = cos(rotation + 90 * (PI / 180.0)) * 100;
	if (rotation >= 360) {
		rotation = 0;
	}
	viewMatrix = glm::lookAt(cameraPosition, cameraLook + cameraPosition, cameraOrientation);
}
