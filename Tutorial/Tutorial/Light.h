#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
		GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation,
							GLfloat diffuseIntensityLocation, GLfloat directionLocation);

	virtual ~Light();

private:
	glm::vec3 _color;
	GLfloat _ambientIntensity;

	glm::vec3 _direction;
	GLfloat _diffusedIntensity;
};

