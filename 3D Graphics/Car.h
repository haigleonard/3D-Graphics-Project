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
class Car
{
private :
	string id;
	const double PI = 3.14159265359;
	int carX;
	int carY;
	int carZ;
	float rotation = 0;
	int randX;
	int randZ;
public:
	Car(float, float, float, string);
	~Car();
	OBJLoader objLoader;
	ThreeDModel player;
	void drawCar(Shader* , Shader*, glm::mat4 , glm::mat4 , glm::mat4 , glm::mat3 );
	int getcarDam();
	void setcarDam(int);
	int damage = 0;
	void updateCar();
};

