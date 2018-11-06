#include "Building.h"
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

Shader* myBuildingShader;


Building::Building()
{
}


Building::~Building()
{
}
void Building::drawBuilding(Shader *myShader, Shader *myBasicShader, glm::mat4 ModelViewMatrix, glm::mat4 ProjectionMatrix, glm::mat4 viewMatrix, glm::mat3 normalMatrix)
{

	glUseProgram(myBasicShader->handle());  // use the shader

	glUniformMatrix4fv(glGetUniformLocation(myBasicShader->handle(), "ProjectionMatrix"), 1, GL_FALSE, &ProjectionMatrix[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(myBasicShader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &ModelViewMatrix[0][0]);

	glUseProgram(myShader->handle());  // use the shader

	ModelViewMatrix = glm::translate(viewMatrix, glm::vec3(coor.x, coor.y, coor.z));

	ModelViewMatrix = glm::rotate(ModelViewMatrix, (float)rotation, glm::vec3(0, 1, 0));

	normalMatrix = glm::inverseTranspose(glm::mat3(ModelViewMatrix));

	glUniformMatrix3fv(glGetUniformLocation(myShader->handle(), "NormalMatrix"), 1, GL_FALSE, &normalMatrix[0][0]);

	glUniformMatrix4fv(glGetUniformLocation(myShader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &ModelViewMatrix[0][0]);

	building.drawElementsUsingVBO(myShader);
}
glm::vec3 Building::getCoor()
{
	return coor;
}
void Building::setCoor(glm::vec3 co)
{
	coor = co;
}

House::House(float x, float y, float z, string i)
{
	setCoor(glm::vec3(x,y,z));

	myBuildingShader = new Shader;
	//if(!myShader->load("BasicView", "glslfiles/basicTransformationsWithDisplacement.vert", "glslfiles/basicTransformationsWithDisplacement.frag"))
	if (!myBuildingShader->load("BasicView", "glslfiles/basicTransformations.vert", "glslfiles/basicTransformations.frag"))
	{
		cout << "failed to load shader" << endl;
	}
	if (objLoader.loadModel("TestModels/house.obj", building))//returns true if the model is loaded, puts the model in the model parameter
	{
		cout << " model loaded " << endl;

		//if you want to translate the object to the origin of the screen,
		//first calculate the centre of the object, then move all the vertices
		//back so that the centre is on the origin.
		building.calcCentrePoint();
		building.centreOnZero();


		building.calcVertNormalsUsingOctree();  //the method will construct the octree if it hasn't already been created.


											   //turn on VBO by setting useVBO to true in threeDmodel.cpp default constructor - only permitted on 8 series cards and higher
		building.initDrawElements();
		building.initVBO(myBuildingShader);
		building.deleteVertexFaceData();

	}
	else
	{
		cout << " model failed to load " << endl;
	}
}

streetLamp::streetLamp(float x, float y, float z, string i)
{
	setCoor(glm::vec3(x, y, z));

	myBuildingShader = new Shader;
	//if(!myShader->load("BasicView", "glslfiles/basicTransformationsWithDisplacement.vert", "glslfiles/basicTransformationsWithDisplacement.frag"))
	if (!myBuildingShader->load("BasicView", "glslfiles/basicTransformations.vert", "glslfiles/basicTransformations.frag"))
	{
		cout << "failed to load shader" << endl;
	}
	if (objLoader.loadModel("TestModels/lamp.obj", building))//returns true if the model is loaded, puts the model in the model parameter
	{
		cout << " model loaded " << endl;

		//if you want to translate the object to the origin of the screen,
		//first calculate the centre of the object, then move all the vertices
		//back so that the centre is on the origin.
		building.calcCentrePoint();
		building.centreOnZero();


		building.calcVertNormalsUsingOctree();  //the method will construct the octree if it hasn't already been created.


											   //turn on VBO by setting useVBO to true in threeDmodel.cpp default constructor - only permitted on 8 series cards and higher
		building.initDrawElements();
		building.initVBO(myBuildingShader);
		building.deleteVertexFaceData();

	}
	else
	{
		cout << " model failed to load " << endl;
	}
}