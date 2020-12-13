#ifndef LIGHT
#define LIGHT

#include "Vertex.h"

struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;

	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};
	LIGHT_TYPE type;
	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;

	Light()
	{
		position.Set(0, 0, 0);
		power = 1.0f;
		kC = 1.0f;
		kL = 0.01f;
		kQ = 0.001f;
	}
};

#endif LIGHT
