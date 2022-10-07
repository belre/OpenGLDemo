#pragma once
#include <string>
#include <GL/glew.h>

#include <GLM/mat4x4.hpp>
#include <GLM/gtc/matrix_transform.hpp>

class StepVertex
{
public:
	StepVertex();
	virtual ~StepVertex();

	int GetNodeId() const {
		return _node_id;
	}

	glm::vec3 GetPosition() const {
		return _position;
	}

	bool GetIsParsed() const {
		return _is_parsed;
	}

	void ParseLine(std::string line);



private:
	int _node_id;
	glm::vec3 _position;
	bool _is_parsed;
};

