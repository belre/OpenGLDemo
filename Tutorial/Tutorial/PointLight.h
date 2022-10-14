#pragma once
#include "Light.h"
class PointLight : public Light
{
public:
	PointLight();

	PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
						GLfloat x_pos , GLfloat y_pos, GLfloat z_pos,
						GLfloat coef_con, GLfloat coef_lin, GLfloat coef_exp);

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation,
		GLuint diffuseIntensityLocation,
		GLuint positionLocation,
		GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation);

	virtual ~PointLight();

protected:
	glm::vec3 _position;

	GLfloat _coef_constant, _coef_linear, _coef_exponent;
};

