#include "DirectionalLight.h"


DirectionalLight::DirectionalLight() : Light()
{
	_direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
	GLfloat aIntensity, GLfloat dIntensity,
	GLfloat xDir, GLfloat yDir, GLfloat zDir)
	: Light(red, green, blue, aIntensity, dIntensity)
{
	_direction = glm::vec3(xDir, yDir, zDir);
}

void DirectionalLight::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation,
	GLfloat diffuseIntensityLocation, GLfloat directionLocation)
{
	glUniform3f(ambientColorLocation, _color.x, _color.y, _color.z);
	glUniform1f(ambientIntensityLocation, _ambientIntensity);

	glUniform3f(directionLocation, _direction.x, _direction.y, _direction.z);
	glUniform1f(diffuseIntensityLocation, _diffusedIntensity);
}


DirectionalLight::~DirectionalLight()
{
	
}

