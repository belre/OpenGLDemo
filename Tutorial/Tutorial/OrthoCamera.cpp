#include "OrthoCamera.h"

void OrthoCamera::keyControl(bool* keys, GLfloat delta_time)
{
	GLfloat velocity = _movementSpeed * delta_time;

	if (keys[GLFW_KEY_W])
	{
		_position += _up * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		_position -= _up * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		_position -= _right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		_position += _right * velocity;
	}
}


OrthoCamera::~OrthoCamera()
{
	
}
