#pragma once
#include <string>
#include <vector>

#include "StepVertex.h"

class StepData
{
public:
	StepData();

	void ReadFromTextData(std::string path);



	virtual ~StepData();

private:
	std::vector<StepVertex> _vertexes;

};

