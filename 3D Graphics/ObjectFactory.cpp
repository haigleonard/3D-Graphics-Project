#include "ObjectFactory.h"
#include "Car.h"
#include "Building.h"
#include "shaders/Shader.h" 
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_inverse.hpp"
Building *building;
Shader* myShader;  ///shader object 
Shader* myBasicShader;
std::vector<Car*> cars;
std::vector<Building*> buildings;
glm::mat4 ModelViewMatrix;  // matrix for the modelling and viewing

ObjectFactory::ObjectFactory()
{

	myShader = new Shader;
	//if(!myShader->load("BasicView", "glslfiles/basicTransformationsWithDisplacement.vert", "glslfiles/basicTransformationsWithDisplacement.frag"))
	if (!myShader->load("BasicView", "glslfiles/basicTransformations.vert", "glslfiles/basicTransformations.frag"))
	{
		cout << "failed to load shader" << endl;
	}

	myBasicShader = new Shader;
	if (!myBasicShader->load("Basic", "glslfiles/basic.vert", "glslfiles/basic.frag"))
	{
		cout << "failed to load shader" << endl;
	}
	glUseProgram(myShader->handle());  // use the shader

	glEnable(GL_TEXTURE_2D);

	//house = new streetLamp(0, 10, 0, "1");
	//buildings.push_back(house);

	Car *car = new Car(-100, 0, -100, std::to_string(cars.size()));
	cars.push_back(car);
	Car *car1 = new Car(0, 0, 0, std::to_string(cars.size()));
	cars.push_back(car1);
	Car *car2 = new Car(100, 0, -100, std::to_string(cars.size()));
	cars.push_back(car2);
	Car *car3 = new Car(100, 0, 100, std::to_string(cars.size()));
	cars.push_back(car3);
	Car *car4 = new Car(-100, 0, 100, std::to_string(cars.size()));
	cars.push_back(car4);
	
}


ObjectFactory::~ObjectFactory()
{
}

void ObjectFactory::draw(glm::mat4 ProjectionMatrix, glm::mat4 viewMatrix)
{
	glMatrixMode(GL_MODELVIEW);
	glUseProgram(myShader->handle());  // use the shader
	glUniformMatrix4fv(glGetUniformLocation(myBasicShader->handle(), "ProjectionMatrix"), 1, GL_FALSE, &ProjectionMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(myBasicShader->handle(), "ModelViewMatrix"), 1, GL_FALSE, &ModelViewMatrix[0][0]);
	GLuint matLocation = glGetUniformLocation(myShader->handle(), "ProjectionMatrix");
	glUniformMatrix4fv(matLocation, 1, GL_FALSE, &ProjectionMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(myShader->handle(), "ViewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
	glUniform4fv(glGetUniformLocation(myShader->handle(), "LightPos"), 1, LightPos);
	glUniform4fv(glGetUniformLocation(myShader->handle(), "light_ambient"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(myShader->handle(), "light_diffuse"), 1, Light_Ambient_And_Diffuse);
	glUniform4fv(glGetUniformLocation(myShader->handle(), "light_specular"), 1, Light_Specular);
	glUniform4fv(glGetUniformLocation(myShader->handle(), "material_ambient"), 1, Material_Ambient);
	glUniform4fv(glGetUniformLocation(myShader->handle(), "material_diffuse"), 1, Material_Diffuse);
	glUniform4fv(glGetUniformLocation(myShader->handle(), "material_specular"), 1, Material_Specular);
	glUniform1f(glGetUniformLocation(myShader->handle(), "material_shininess"), Material_Shininess);
	glm::mat3 normalMatrix = glm::inverseTranspose(glm::mat3(ModelViewMatrix));
	for (Car *car : cars) {
		car->drawCar(myShader, myBasicShader, ModelViewMatrix, ProjectionMatrix, viewMatrix, normalMatrix);
		car->updateCar();
	}
	for (Building *building : buildings) {
		building->drawBuilding(myShader, myBasicShader, ModelViewMatrix, ProjectionMatrix, viewMatrix, normalMatrix);
	}
}