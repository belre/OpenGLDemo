#pragma once

#include <GL\glew.h>
#include <GLFW/glfw3.h>

#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>


class Camera
{
public:

	Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat movement_speed, GLfloat turn_speed);

	virtual void keyControl(bool* keys, GLfloat delta_time);
	virtual void mouseControl(GLfloat change_x, GLfloat change_y);

	glm::vec3 getCameraPosition();

	glm::mat4 calculateViewMatrix();

	virtual ~Camera();

protected:
	glm::vec3 _position;
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _worldUp;

	GLfloat _yaw;
	GLfloat _pitch;

	GLfloat _movementSpeed;
	GLfloat _turnSpeed;

	virtual void update();
};

