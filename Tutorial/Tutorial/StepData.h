#pragma once
#include <string>
#include <vector>

#include "StepEdgeLine.h"
#include "StepLoop.h"
#include "StepVertex.h"

class StepLoop;

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

	StepEdgeLine& GetEdge(int id)
	{
		for(auto iter = _edges.begin() ; iter != _edges.end(); iter++) 
		{
			if(iter->GetNodeId() == id) 
			{
				return *iter;
			}
		}

		return InvalidEdgeData;
	}

	std::vector<int> GetEdgeId()
	{
		std::vector<int> id_list;

		for(auto iter = _edges.begin(); iter != _edges.end(); iter++) 
		{
			id_list.push_back(iter->GetNodeId());
		}

		return id_list;
	}

	StepVertex& GetVertex(int id)
	{
		for (auto iter = _vertexes.begin(); iter != _vertexes.end(); iter++)
		{
			if (iter->GetNodeId() == id)
			{
				return *iter;
			}
		}

		return InvalidVertexData;
	}

	std::vector<int> GetVertexId()
	{
		std::vector<int> id_list;

		for (auto iter = _vertexes.begin(); iter != _vertexes.end(); iter++)
		{
			id_list.push_back(iter->GetNodeId());
		}

		return id_list;
	}

	std::vector<StepLoop>& GetClosedLoop()
	{
		return _loops;
	}

	virtual ~StepData();

public:
	StepEdgeLine InvalidEdgeData;
	StepVertex InvalidVertexData;

private:
	std::vector<StepVertex> _vertexes;
	std::vector<StepEdgeLine> _edges;
	std::vector<StepLoop> _loops;
};

