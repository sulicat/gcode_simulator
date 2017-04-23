#pragma once
struct Vector
{
	float x,y,z;
	Vector operator+(Vector o);
	Vector operator-(Vector o);
	void operator-=(Vector o);
	void operator+=(Vector o);

	void operator*=(float s);
	void operator/=(float s);
	bool operator==(Vector o);
	bool operator!=(Vector o);
	float sqrMag();
	float Mag();
	operator float();
	Vector Dir();
};

Vector operator*(Vector lhs, float rhs);
Vector operator/(Vector lhs, float rhs);


#include <vector>