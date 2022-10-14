#include "PointLight.h"

PointLight::PointLight() : Light()
{
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_coef_constant = 1.0f;
	_coef_linear = 0.0f;
	_coef_exponent = 0.0f;
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
	GLfloat x_pos, GLfloat y_pos, GLfloat z_pos,
	GLfloat coef_con, GLfloat coef_lin, GLfloat coef_exp)
		: Light(red, green, blue, aIntensity, dIntensity)
{
	_position = glm::vec3(x_pos, y_pos, z_pos);
	_coef_constant = coef_con;
	_coef_linear = coef_lin;
	_coef_exponent = coef_exp;
}

void PointLight::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation,
	GLfloat diffuseIntensityLocation,
	GLfloat positionLocation,
	GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation)
{
	glUniform3f(ambientColorLocation, _color.x, _color.y, _color.z);
	glUniform1f(ambientIntensityLocation, _ambientIntensity);
	glUniform1f(diffuseIntensityLocation, _diffusedIntensity);

	glUniform3f(positionLocation, _position.x, _position.y, _position.z);
	glUniform1f(constantLocation, _coef_constant);
	glUniform1f(linearLocation, _coef_linear);
	glUniform1f(exponentLocation, _coef_exponent);
}


PointLight::~PointLight() {
	
}
