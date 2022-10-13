#include "Light.h"

Light::Light()
{
	_color = glm::vec3(1.0f, 1.0f, 1.0f);
	_ambientIntensity = 1.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity)
{
	_color = glm::vec3(red, green, blue);
	_ambientIntensity = aIntensity;
}

void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation)
{
	glUniform3f(ambientColorLocation, _color.x, _color.y, _color.z);
	glUniform1f(ambientIntensityLocation, _ambientIntensity);
}


Light::~Light()
{
	
}