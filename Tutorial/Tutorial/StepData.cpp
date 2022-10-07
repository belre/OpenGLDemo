#include "StepData.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include "StepVertex.h"

StepData::StepData() {
	
}

void StepData::ReadFromTextData(std::string path)
{
	std::ifstream ifs(path, std::ios::in);

	if(!ifs) 
	{
		std::cerr << "Failed to read STEP text" << std::endl;
		return;
	}

	while(!ifs.eof()) 
	{
		std::string text;
		std::getline(ifs, text);

		auto split_iter = std::find(text.begin(), text.end(), ',');
		if(split_iter != text.end() ) {
			auto category = text.substr(0, std::distance(text.begin(), split_iter));

			// Ží—Þ‚Ì”»•Ê
			if(category == "Vertex") {
				StepVertex vertex;
				vertex.ParseLine(text.substr(std::distance(text.begin(), split_iter) + 1));

				if(vertex.GetIsParsed()) {
					_vertexes.push_back(vertex);
				}
			}
			else if(category == "Edge") {
				
			}
			else if(category == "Loop") {
				
			}

		}
	}



}



StepData::~StepData() {
	
}


