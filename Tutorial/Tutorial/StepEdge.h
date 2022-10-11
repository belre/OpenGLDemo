#pragma once
#include <string>

#include "StepVertex.h"

class StepData;


/**
 * \brief �G�b�W���
 * ���{����Tree�\���ɂ��邽�߂ɂ�������ۃN���X��p�ӂ��邪�A�Z���N�g�����Ɋւ��Ă͏ȗ�
 */
class StepEdge
{
public:
	enum EdgePattern {
		UNKNOWN = 0,
		LINE = 1,
		CIRCLE = 2,
	};

public:
	StepEdge();

	
	virtual void ParseLine(std::string line);

	virtual int GetNodeId() const {
		return _node_id;
	}

	virtual EdgePattern GetPattern() const {
		return _edge_pattern;
	}


	virtual bool GetIsParsed() const {
		return _is_parsed;
	}

	virtual void Bind(StepData& data);

	StepVertex& GetStartVertex()
	{
		return _start_data;
	}

	StepVertex& GetEndVertex()
	{
		return _end_data;
	}

	virtual ~StepEdge();

private:
	int _node_id;
	int _start_node_id;
	int _end_node_id;
	EdgePattern _edge_pattern;
	bool _is_parsed;

	StepVertex _start_data;
	StepVertex _end_data;
};

