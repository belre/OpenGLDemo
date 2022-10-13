#pragma once
#include <GL/glew.h>


class Material
{
public:
	Material();
	Material(GLfloat sIntensity, GLfloat shininess);

	void UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);

	virtual ~Material();

private:
	GLfloat _specularIntensity;
	GLfloat _shininess;
};

