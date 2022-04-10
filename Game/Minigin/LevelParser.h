#pragma once
#include <string>
#include <fstream>
#include "Structs.h"
#include <vector>
namespace dae
{
	//Todo >> Replace with your own structure



	//Just parses vertices and indices
	static bool ParseLevelFile(const std::string& filename, std::vector<Platform>& platforms, std::vector<Ladder>& ladders, std::vector<Float2> spawnPositions)
	{
		std::ifstream file(filename);
		if (!file)
			return false;

		//std::vector<FPoint4> positions;
		//std::vector<FVector3> normals;
		//std::vector<FVector2> UVs;

		platforms.clear();
		ladders.clear();
		spawnPositions.clear();

		std::string sCommand;
		// start a while iteration ending when the end of file is reached (ios::eof)
		while (!file.eof())
		{
			//read the first word of the string, use the >> operator (istream::operator>>) 
			file >> sCommand;
			//use conditional statements to process the different commands	
			if (sCommand == "#")
			{
				// Ignore Comment
			}
			else if (sCommand == "p")
			{
				//Float2
				float x, y;
				float width;
				file >> x >> y >> width;
				
				platforms.push_back(Platform(Float2(x,y), width));
			}
			else if (sCommand == "ld")
			{
				//Float2
				float x, y;
				float height;
				file >> x >> y >> height;
				ladders.push_back(Ladder(Float2(x, y), height));
			}
			else if (sCommand == "ps")
			{
				// Vertex Normal
				float x, y;
				file >> x >> y;
				spawnPositions.push_back(Float2(x, y));
			}
		}

		return true;
	}
}