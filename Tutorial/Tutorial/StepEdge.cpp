#include "StepEdge.h"

#include <regex>
#include <GLM/vec3.hpp>

#include "StepData.h"

StepEdge::StepEdge() {
	_edge_pattern = EdgePattern::UNKNOWN;
}

void StepEdge::ParseLine(std::string line) {
	std::regex regex(R"((\w+),(\d+),(\d+),(\d+))");
	std::smatch match;
	if (!std::regex_match(line, match, regex))
	{
		return;
	}

	auto type = match[1].str();

	if (type == "Line") {
		_edge_pattern = EdgePattern::LINE;
	}
	else if (type == "Circle") {
		_edge_pattern = EdgePattern::CIRCLE;
	}

	_node_id = std::atoi(match[2].str().c_str());
	_start_node_id = std::atoi(match[3].str().c_str());
	_end_node_id = std::atoi(match[4].str().c_str());
	_is_parsed = true;
}


void StepEdge::Bind(StepData& data)
{
	_start_data = data.GetVertex(_start_node_id);
	_end_data = data.GetVertex(_end_node_id);
}

StepEdge::~StepEdge() {
	
}

