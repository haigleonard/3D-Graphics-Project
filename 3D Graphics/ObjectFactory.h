#pragma once
#include "shaders/Shader.h" 
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_inverse.hpp"
class ObjectFactory
{
private:
	//Material properties
	float LightPos[4] = { 0, 35, 0, 0.0 };
	float Material_Ambient[4] = { 1.0f, 1.0f,1.0f, 1.0f }; // Object colour
	float Material_Diffuse[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; // object colour
	float Material_Specular[4] = { 1.0f,1.0f,1.0f,1.0f };
	float Material_Shininess = 1.0;
	float Light_Specular[4] = { 0.0f,0.0f,1.0f,1.0f };
	float Light_Ambient_And_Diffuse[4] = { 1.0, 1.0, 1.0, 1.0f }; // light colour
public:
	ObjectFactory();
	~ObjectFactory();

	void draw(glm::mat4, glm::mat4);
};

