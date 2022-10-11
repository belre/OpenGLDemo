#pragma once
#include <string>
#include <vector>

#include "StepData.h"
#include "StepEdge.h"

class StepData;

class StepLoop
{
public:
	StepLoop();

	virtual void ParseLine(std::string line);

	virtual bool GetIsParsed() const
	{
		return _is_parsed;
	}

	virtual void Bind(StepData& data);

	std::vector<StepEdge>& GetEdges()
	{
		return _edges_ref;
	}

	virtual ~StepLoop();

private:
	int _node_id;
	bool _is_parsed;
	std::vector<int> _loop_id;

	std::vector<StepEdge> _edges_ref;
};

