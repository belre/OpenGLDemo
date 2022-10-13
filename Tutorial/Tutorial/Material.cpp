#include "Material.h"



Material::Material()
{
	_specularIntensity = 0.0f;
	_shininess = 0.0f;
}

Material::Material(GLfloat sIntensity, GLfloat shine)
{
	_specularIntensity = sIntensity;
	_shininess = shine;
}

void Material::UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation)
{
	glUniform1f(specularIntensityLocation, _specularIntensity);
	glUniform1f(shininessLocation, _shininess);
}

Material::~Material()
{
}
