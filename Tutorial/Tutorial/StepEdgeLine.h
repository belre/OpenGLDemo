#pragma once
#include "StepEdge.h"

class StepEdgeLine : public StepEdge
{
public:
	StepEdgeLine();
	virtual ~StepEdgeLine();

public:
	void ParseLine(std::string line) override ;
};

