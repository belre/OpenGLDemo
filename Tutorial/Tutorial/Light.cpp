#include "Light.h"

Light::Light()
{
	_color = glm::vec3(1.0f, 1.0f, 1.0f);
	_ambientIntensity = 1.0f;

	_diffusedIntensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity)
{
	_color = glm::vec3(red, green, blue);
	_ambientIntensity = aIntensity;

	_diffusedIntensity = dIntensity;
}


Light::~Light()
{
	
}