#pragma once
#include "Vector3.h"

struct Position
{
	float x, y, z;
	Position(float x = 0, float y = 0, float z = 0) { Set(x, y, z); }
	void Set(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
};

struct Color
{
	float r, g, b;
	Color(float r = 0, float g = 0, float b = 0) { Set(r, g, b); }
	void Set(float r, float g, float b) { this->r = r; this->g = g; this->b = b; }
};

struct Vertex
{
	Position pos;
	Color color;
	Vector3 normal;
};