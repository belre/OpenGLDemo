#include "StepLoop.h"

#include <regex>


StepLoop::StepLoop() 
{
}

void StepLoop::ParseLine(std::string line) {
	std::regex regex_outline(R"((\d+),\[(.+)\])");
	std::smatch match_outline;

	if (!std::regex_match(line, match_outline, regex_outline))
	{
		return;
	}


	_node_id = std::atoi(match_outline[1].str().c_str());

	auto inline_text = match_outline[2].str();
	std::regex regex_inline(R"((\d+),*)");
	std::smatch match_inline;

	while(std::regex_search(inline_text, match_inline, regex_inline)) 
	{
		auto text = match_inline[1].str();
		if (std::find(text.begin(), text.end(), ',') == text.end())
		{
			_loop_id.push_back(std::atoi(match_inline[0].str().c_str()));
		}

		inline_text = match_inline.suffix();
	}

	_is_parsed = true;
}

void StepLoop::Bind(StepData& data)
{
	_edges_ref.clear();
	for(auto iter = _loop_id.begin(); iter != _loop_id.end(); iter++) 
	{
		StepEdgeLine edge_data = data.GetEdge(*iter);

		edge_data.Bind(data);

		_edges_ref.push_back(edge_data);
	}
}

StepLoop::~StepLoop() {
	
}
