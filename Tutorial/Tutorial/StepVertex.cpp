#include "StepVertex.h"

#include <regex>

StepVertex::StepVertex() {
	_is_parsed = false;
}

void StepVertex::ParseLine(std::string line) {

	std::regex regex(R"((\d+),\[([\-\d\.]+),([\-\d\.]+),([\-\d\.]+)\])");
	std::smatch match;
	if(std::regex_match(line, match, regex))
	{
		_node_id = std::atoi(match[1].str().c_str());

		glm::vec3 pos(1.0f);
		pos.x = std::atof(match[2].str().c_str());
		pos.y = std::atof(match[3].str().c_str());
		pos.z = std::atof(match[4].str().c_str());
		_position = pos;
	}

	_is_parsed = true;
}

StepVertex::~StepVertex() {
	
}
