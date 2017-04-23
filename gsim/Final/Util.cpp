#include "Util.h"

Vector Vector::operator+(Vector o)
{
	return Vector{x+o.x, y+o.y, z+o.z};
}

Vector Vector::operator-(Vector o)
{
	return Vector{x-o.x, y-o.y, z-o.z};
}

void Vector::operator+=(Vector o)
{
	x+=o.x; y+=o.y; z+=o.z;
}

void Vector::operator-=(Vector o)
{
	x-=o.x; y-=o.y; z-=o.z;
}

void Vector::operator*=(float s)
{
	x *= s; y *= s; z *= s;
}

void Vector::operator/=(float s)
{
	x /= s; y /= s; z /= s;
}

bool Vector::operator==(Vector o)
{
	return x == o.x&&y == o.y&&z == o.z;
}

bool Vector::operator!=(Vector o)
{
	return !(*this == o);
}

Vector operator*(Vector lhs, float rhs)
{
	return Vector{lhs.x*rhs, lhs.y*rhs, lhs.z*rhs};
}

Vector operator/(Vector lhs, float rhs)
{
	return Vector{lhs.x/rhs, lhs.y/rhs, lhs.z/rhs};
}

float Vector::sqrMag()
{
	return x*x+y*y+z*z;
}
#include<cmath>

float Vector::Mag()
{
	std::sqrt(this->sqrMag());
}

Vector::operator float()
{
	return Mag();
}

Vector Vector::Dir()
{
	return operator/(*this, *this);
}