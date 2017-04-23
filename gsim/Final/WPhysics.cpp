#include "WPhysics.h"

Particle *root;

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}

Particle::Particle()
{
	children = new Particle[100];
	numChildren = 0;
	parent = nullptr;
	mass = 1;
	effective_radius = 1;
	x=y=z=0;
	vx=vy=vz=0;
	fx=fy=fz=0;
}

Particle::Particle(Particle* children, unsigned int numChildren)
{
	this->children = children; this->numChildren = numChildren;
	parent = nullptr;
	mass = 1;
	effective_radius = 1;
	x=y=z=0;
	vx=vy=vz=0;
	fx=fy=fz=0;
}

Particle::~Particle()
{
	delete children;
}

void Particle::addChild(Particle *child)
{
	children[numChildren++] = *child;
	child->parent = this;
}

void Particle::removeChild(Particle *child)
{
	//todo
}

void Particle::Update()
{

}

void Particle::Render()
{

}

float sqrDist(Particle a, Particle b)
{
	return ((a.x-b.x) + (a.y-b.y)                                                                                                                                                                                            yby + a.z*a.z);
}                                                                                                                                              