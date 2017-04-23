#pragma once
#include "Util.h"
struct Extrusion
{
	Vector startP;
	Vector endP;
};

struct Layer
{
	std::vector<Extrusion> extrusions;
};

std::vector<Extrusion> readFile(char *name);
std::vector<Vector> readF(char *name, float particlesPerUnitLength);