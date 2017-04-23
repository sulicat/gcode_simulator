#pragma once

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
std::vector<PARTICLE> readF(char *name);