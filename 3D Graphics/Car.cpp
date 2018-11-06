#include "Car.h"
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
#include <ctime>  
Shader* myCarShader;

Car::Car(float x, float y, float z, string i)
{
	carX = x;
	carY = y;
	carZ = z;
	id = i;
	srand(time(NULL));
	randX = rand() % 200 - 100;
	randZ = rand() % 200 - 100;
	myCarShader = new Shader;
	//if(!myShader->load("BasicView", "glslfiles/basicTransformationsWithDisplacement.vert", "glslfiles/basicTransformationsWithDisplacement.frag"))
	if (!myCarShader->load("BasicView", "glslfiles/basicTransformations.vert", "glslfiles/basicTransformations.frag"))
	{
		cout << "failed to load shader" << endl;
	}
	if (objLoader.loadModel("TestModels/playercar.obj", player))//returns true if the model is loaded, puts the model in the model parameter
	{
		cout << " model loaded " << endl;

		//if you want to translate the object to the origin of the screen,
		//first calculate the centre of the object, then move all the vertices
		//back so that the centre is on the origin.
		player.calcCentrePoint();
		player.centreOnZero();


		player.calcVertNormalsUsingOctree();  //the method will construct the octree if it hasn't already been created.


											   //turn on VBO by setting useVBO to true in threeDmodel.cpp default constructor - only permitted on 8 series cards and higher
		player.initDrawElements();
		player.initVBO(myCarShader);
		player.deleteVertexFaceData();

	}
	else
	{
		cout << " model failed to load " << endl;
	}

}


Car::~Car()
{
}

void Car::setcarDam(int d)
{
	damage = d;
}


int Car::getcarDam()
{
	return damage;
}



void Car::drawCar(Shader *myShader, Shader *myBasicShader, glm::mat4 ModelViewMatrix, glm::mat4 ProjectionMatrix, glm::mat4 viewMatrix, glm::mat3 normalMatrix)
{

	glUseProgram(myBasicShader->handle());  // use the shader

	glUniformMatrix4fv(glGetUniformLocation(myBasicShader->handle(), "ProjectionMatrix"), 1, GL_FALSE, &ProjectionMatrix[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(myBasicShader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &ModelViewMatrix[0][0]);

	glUseProgram(myShader->handle());  // use the shader

	ModelViewMatrix = glm::translate(viewMatrix, glm::vec3(carX, carY, carZ));

	ModelViewMatrix = glm::rotate(ModelViewMatrix, (float)rotation, glm::vec3(0, 1, 0));

	normalMatrix = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

	glUniformMatrix3fv(glGetUniformLocation(myShader->handle(), "NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(myShader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &ModelViewMatrix[0][0]);

	player.drawElementsUsingVBO(myShader);
}

void Car::updateCar()
{
	
	if (carX == randX && carZ == randZ)
	{
		randX = rand() % 200-100;
		randZ = rand() % 200-100;
	}
	if (carX != randX || carZ != randZ)
	{
		if (carX > randX) {
			carX--;
		}
		if (carX < randX) {
			carX++;
		}
		if (carZ > randZ) {
			carZ--;
		}
		if (carZ < randZ) {
			carZ++;
		}
	}
	
	float o = ((float)carZ - (float)randZ);
	float a = -((float)carX - (float)randX);
	if (carX >= randX) {
		rotation = (atan((float)o / a) * 180 / PI) - 90;
	}
	else {
		rotation = (atan((float)o / a) * 180 / PI) + 90;
	}
	
}