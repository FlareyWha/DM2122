#ifndef CAMERA_2_H
#define CAMERA_2_H

#include "Vector3.h"

class Camera2
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	float phi;
	float theta;
	float radius;

	Camera2();
	~Camera2();
	void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Reset(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Update(double dt);
};

#endif