#pragma once
#include "PointLight.h"
class SpotLight :
    public PointLight
{
public:
	SpotLight();

	SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
		GLfloat x_pos, GLfloat y_pos, GLfloat z_pos,
		GLfloat xDir, GLfloat yDir, GLfloat zDir,
		GLfloat coef_con, GLfloat coef_lin, GLfloat coef_exp,
		GLfloat edge);

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation,
		GLuint diffuseIntensityLocation,
		GLuint positionLocation,
		GLuint directionLocation,
		GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation,
		GLuint edgeLocation);

	void SetFlash(glm::vec3 pos, glm::vec3 dir);

  virtual ~SpotLight();

private:
  glm::vec3 _direction;
  GLfloat _edge, _procEdge;

};

