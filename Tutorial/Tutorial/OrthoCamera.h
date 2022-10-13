#pragma once
#include "Camera.h"

class OrthoCamera : public Camera
{
public:
	OrthoCamera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat movement_speed, GLfloat turn_speed)
		: Camera(position, up, yaw, pitch, movement_speed, turn_speed)
	{
		
	}

	void keyControl(bool* keys, GLfloat delta_time) override;

	virtual ~OrthoCamera();
};

