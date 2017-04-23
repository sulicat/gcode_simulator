#include "GCODE.h"
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <cstdio>


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
			//std::cout << line << std::endl;
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
					float _x, _y, _z, _e;
					sscanf("G1 X%f Y%f Z%f E%f", line.c_str(), _x, _y, _z, _e);
					if (_e == 0) continue;
					if (prev != Vector{ 0,0,0 })
					{
						cur.push_back(Extrusion{ prev, Vector{_x,_y,_z} });
					}
					printf("ls<%f,%f,%f>\n", _x,_y,_z);
					prev = Vector{ _x,_y,_z };
					prevz = _z;
					//cout << "Z" << endl;
				}
				else if ((lineBitMap&x == x) && (lineBitMap&y == y) && (lineBitMap&e == e))
				{
					float _x, _y, _e;
					sscanf("G1 X%f Y%f E%f", line.c_str(), _x, _y, _e);
					if (_e == 0) continue;
					if (prev != Vector{ 0,0,0 })
					{
						cur.push_back(Extrusion{ prev, Vector{ _x,_y,prevz } });
					}
					prev = Vector{ _x,_y,prevz };
				}

				//cout << (int)lineBitMap << ' ';
			}

			if (file.eof()) break;
		}

		return cur;
	}
	else
	{
		std::cerr << "Error loading file " << name << std::endl;
		return std::vector<Extrusion>();
	}
}

std::vector<Vector> readF(char *name, float linearDensity = 10)//linearDensity = Particles/mm
{
	std::vector<Vector> ret;

	std::vector<Extrusion> line = readFile(name);
	std::cout << "\n\n" <<  ret.size() << " particles\n\n" << std::endl;
	Vector pos = Vector{0,0,0};
	ret.push_back(pos);
	for(int i = 0; i < line.size(); i++)
	{
		Extrusion c = line[i];
		Vector trace = c.endP-c.startP;
		Vector delta = trace.Dir()/linearDensity;
		printf("s<%f,%f,%f>\n", c.startP.x, c.startP.y, c.startP.z);
		while(pos.x<c.endP.x&&pos.y<c.endP.y&&pos.z<c.endP.z)
		{
			std::cout<<"Adding" << std::endl;
			ret.push_back(pos);
			pos+=delta;
		}
	}
	std::cout << "\n\n" <<  ret.size() << " particles\n\n" << std::endl;
	return ret;
}