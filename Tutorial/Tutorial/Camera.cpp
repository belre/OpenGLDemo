#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat movement_speed, GLfloat turn_speed)
{
	_position = position;
	_worldUp = up;
	_yaw = yaw;
	_pitch = pitch;
	_front = glm::vec3(0.0f, 0.0f, -1.0f);

	_movementSpeed = movement_speed;
	_turnSpeed = turn_speed;

	update();
}

void Camera::keyControl(bool* keys, GLfloat delta_time)
{
	GLfloat velocity = _movementSpeed * delta_time;

	if(keys[GLFW_KEY_W]) 
	{
		_position += _front * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		_position -= _front * velocity;
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

void Camera::mouseControl(GLfloat change_x, GLfloat change_y)
{
	change_x *= _turnSpeed;
	change_y *= _turnSpeed;

	_yaw += change_x;
	_pitch += change_y;

	if(_pitch > 89.0f) 
	{
		_pitch = 89.0f;
	}

	if(_pitch < -89.0f) 
	{
		_pitch = -89.0f;
	}

	update();
}


glm::vec3 Camera::getCameraPosition()
{
	return _position;
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(_position, _position + _front, _up);
}

void Camera::update()
{
	_front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_front.y = sin(glm::radians(_pitch));
	_front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_front = glm::normalize(_front);

	_right = glm::normalize(glm::cross(_front, _worldUp));
	_up = glm::normalize(glm::cross(_right, _front));
}


Camera::~Camera()
{
	
}

