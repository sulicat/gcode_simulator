#include "GCODE.h"
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>



char x = 1, y = 2, z = 4, e = 8;

std::vector<Extrusion> readFile(char * name)
{
	std::fstream file((const char*)name);
	std::vector<Extrusion> cur;
	int numL;
	std::string line;
	if (file)
	{
		Vector prev;
		float prevz;
		while (true)
		{
			numL++;
			std::getline(file, line, '\n');
			if (line[0] == ';') continue;// comment

			char lineBitMap = 0;

			//std::cout << line << std::endl;
			if (line.find("G1") == 0)//Linear interpolation
			{
				if (line.find("X") != -1)lineBitMap |= x;
				if (line.find("Y") != -1)lineBitMap |= y;
				if (line.find("Z") != -1) { lineBitMap |= z; }
				if (line.find("E") != -1)lineBitMap |= e;
				//cout << line << endl;
				//cout << bool((lineBitMap&z == z)) << endl;
				if ((lineBitMap&x == x) && (lineBitMap&y == y) && (lineBitMap&z == z) && (lineBitMap&e == e))
				{
					float x, y, z, e;
					sscanf("G1 X%f Y%f Z%f E%f", line.c_str(), x, y, z, e);
					if (e == 0) continue;
					if (prev != Vector{ 0,0,0 })
					{
						cur.push_back(Extrusion{ prev, Vector{x,y,z} });
					}
					prev = Vector{ x,y,z };
					prevz = z;
					//cout << "Z" << endl;
				}
				else if ((lineBitMap&x == x) && (lineBitMap&y == y) && (lineBitMap&e == e))
				{
					float x, y, e;
					sscanf("G1 X%f Y%f E%f", line.c_str(), x, y, e);
					if (e == 0) continue;
					if (prev != Vector{ 0,0,0 })
					{
						cur.push_back(Extrusion{ prev, Vector{ x,y,prevz } });
					}
					prev = Vector{ x,y,prevz };
				}

				//cout << (int)lineBitMap << ' ';
			}

			if (file.eof()) break;
		}

		std::cout << numL << std::endl;

		return cur;
	}
	else
	{
		std::cerr << "Error loading file " << name << std::endl;
		return std::vector<Extrusion>();
	}
}

std::vector<PARTICLES> readF(char *name)
{
	std::vector<Extrusion> extrs = readFile(name);
	std::vector<PARTICLES> ret();

	for (auto i = extrs.begin(); i != extrs.end(); ++i)
	{
		
	}

	return ret;
}

int main()
{
	
}