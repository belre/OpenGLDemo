#include "Light.h"

Light::Light()
{
	_color = glm::vec3(1.0f, 1.0f, 1.0f);
	_ambientIntensity = 1.0f;

	_direction = glm::vec3(0.0f, -1.0f, 0.0f);
	_diffusedIntensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
	GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity)
{
	_color = glm::vec3(red, green, blue);
	_ambientIntensity = aIntensity;

	_direction = glm::vec3(xDir, yDir, zDir);
	_diffusedIntensity = dIntensity;
}

void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation,
	GLfloat diffuseIntensityLocation, GLfloat directionLocation)
{
	glUniform3f(ambientColorLocation, _color.x, _color.y, _color.z);
	glUniform1f(ambientIntensityLocation, _ambientIntensity);

	glUniform3f(directionLocation, _direction.x, _direction.y, _direction.z);
	glUniform1f(diffuseIntensityLocation, _diffusedIntensity);
}


Light::~Light()
{
	
}