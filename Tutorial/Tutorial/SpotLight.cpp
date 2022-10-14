#include "SpotLight.h"


SpotLight::SpotLight() : PointLight()
{
	_direction = glm::vec3(0.0f, -1.0f, 0.0f);
	_edge = 0.0f;
}

SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
	GLfloat x_pos, GLfloat y_pos, GLfloat z_pos,
	GLfloat xDir, GLfloat yDir, GLfloat zDir,
	GLfloat coef_con, GLfloat coef_lin, GLfloat coef_exp,
	GLfloat edge)
		: PointLight(red, green, blue, aIntensity, dIntensity, x_pos, y_pos, z_pos, coef_con, coef_lin, coef_exp)
{
	_direction = glm::normalize(glm::vec3(xDir, yDir, zDir));

	_edge = edge;
	_procEdge = cosf(glm::radians(edge));
}

void SpotLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation,
	GLuint diffuseIntensityLocation,
	GLuint positionLocation,
	GLuint directionLocation,
	GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation,
	GLuint edgeLocation)
{
	glUniform3f(ambientColorLocation, _color.x, _color.y, _color.z);
	glUniform1f(ambientIntensityLocation, _ambientIntensity);
	glUniform1f(diffuseIntensityLocation, _diffusedIntensity);

	glUniform3f(positionLocation, _position.x, _position.y, _position.z);
	glUniform1f(constantLocation, _coef_constant);
	glUniform1f(linearLocation, _coef_linear);
	glUniform1f(exponentLocation, _coef_exponent);

	glUniform3f(directionLocation, _direction.x, _direction.y, _direction.z);
	glUniform1f(edgeLocation, _procEdge);
}

void SpotLight::SetFlash(glm::vec3 pos, glm::vec3 dir)
{
	_position = pos;
	_direction = dir;
}


SpotLight::~SpotLight()
{
	
}
