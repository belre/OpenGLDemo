#pragma once
#include "StepEdge.h"


class StepData;

class StepEdgeLine : public StepEdge
{
public:
	StepEdgeLine();
	virtual ~StepEdgeLine();

public:
	void ParseLine(std::string line) override ;

};

