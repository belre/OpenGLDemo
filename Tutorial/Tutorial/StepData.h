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

	std::vector<glm::vec3> GetVertexPosition()
	{
		std::vector<glm::vec3> src;
		for(auto iter = _vertexes.begin(); iter != _vertexes.end(); iter++) 
		{
			src.push_back(iter->GetPosition());
		}
		return src;
	}

	int GetVertexNumber()
	{
		return _vertexes.size();
	}

	virtual ~StepData();

private:
	std::vector<StepVertex> _vertexes;
	std::vector<StepEdgeLine> _edges;
	std::vector<StepLoop> _loops;
};

