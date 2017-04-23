float GRAVITY_CONST = 1;

class Particle
{
public:
	Particle();
	Particle(Particle* children, unsigned int numChildren);
	~Particle();
	void addChild(Particle *child);
	void removeChild(Particle *child);
	void Update();
	void Render();

	Particle* children;
	unsigned int numChildren;
	Particle *parent;
	float mass;
	float effective_radius;
	float x,y,z;
	float vx,vy,vz;
	float fx,fy,fz;
};

class PHX
{
private:
	Particle * particles.
public:
	PHX();
	~PHX();
	
};

float sqrDist(Particle a, Particle b)
{
	return ((a.x-b.x)*(a.x-b.x) + (a.x-b.x)*(a.x-b.x) + (a.zzb.z)*(a.z-b.z));
}