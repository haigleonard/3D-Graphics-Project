#pragma once
#include "gl/glew.h"
#include "gl/wglew.h"
#pragma comment(lib, "glew32.lib")
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_inverse.hpp"
class Camera
{

private:

	
	glm::vec3 cameraPosition = glm::vec3(0.0f, 10.0f, -80.0f);
	glm::vec3 cameraLook = glm::vec3(0.0f, 0.0f, 50.0f);
	glm::vec3 cameraOrientation = glm::vec3(0.0f, 1.0f, 0.0f);
	float velocity = 1;
	float rotation = 0;
	float zoom;
	const double PI = 3.14159265359;
	glm::mat4 viewMatrix;
public:

	Camera();
	~Camera();
	glm::mat4 getViewMatrix();
	void updateCamera();
	float getRotation();
	float getCameraX();
	float getCameraY();
	float getCameraZ();
	float getZoom();
	void setZoom(int z);
	void setZoom(bool z);
	void left();
	void right();
	void accelerate();
	void brake();
	void pedalOff();
	void reverse();
	void increaseY();
	void decreaseY();
	void strafeLeft();
	void strafeRight();
};

