#pragma once
#include <string>
#include <vector>

class StepLoop
{
public:
	StepLoop();

	virtual void ParseLine(std::string line);
	virtual bool GetIsParsed() const {
		return _is_parsed;
	}

	virtual ~StepLoop();



private:
	int _node_id;
	bool _is_parsed;
	std::vector<int> _loop_id;
};

