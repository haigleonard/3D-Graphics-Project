#pragma once
#include "shaders/Shader.h"  
#include "3DStruct\threeDModel.h"
#include "gl/glew.h"
#include "gl/wglew.h"
#pragma comment(lib, "glew32.lib")
#include "shaders/Shader.h"   // include shader header file, this is not part of OpenGL
//MODEL LOADING
#include "3DStruct\threeDModel.h"
#include "Obj\OBJLoader.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_inverse.hpp"
class Building
{
private:
	string id;
	glm::vec3 coor = glm::vec3(0.0, 0.0, 0.0);
	float rotation = 0;
public:
	Building();
	~Building();
	OBJLoader objLoader;
	ThreeDModel building;
	glm::vec3 getCoor();
	void setCoor(glm::vec3);
	void drawBuilding(Shader*, Shader*, glm::mat4, glm::mat4, glm::mat4, glm::mat3);
};

class House : public Building {
public:
	House(float, float, float, string);
};

class streetLamp : public Building {
public:
	streetLamp(float, float, float, string);
};