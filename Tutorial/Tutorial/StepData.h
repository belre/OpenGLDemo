#pragma once
#include <string>
#include <vector>

#include "StepEdgeLine.h"
#include "StepLoop.h"
#include "StepVertex.h"

class StepEdge;

class StepData
{
public:
	StepData();

	void ReadFromTextData(std::string path);



	virtual ~StepData();

private:
	std::vector<StepVertex> _vertexes;
	std::vector<StepEdgeLine> _edges;
	std::vector<StepLoop> _loops;
};

