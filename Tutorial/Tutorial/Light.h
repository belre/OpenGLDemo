#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity);
	
	virtual ~Light();

protected:
	glm::vec3 _color;
	GLfloat _ambientIntensity;

	GLfloat _diffusedIntensity;
};

