#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity);

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation);

	virtual ~Light();

private:
	glm::vec3 _color;
	GLfloat _ambientIntensity;
};

