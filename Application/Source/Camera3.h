#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Vector3.h"

class Camera3
{
private:

public:
	static Vector3 position;
	Vector3 prevPos;
	static Vector3 target;
	static Vector3 up;
	static Vector3 view;
	static Vector3 right;
	static float yaw;
	static float pitch;
	bool debugMode;

	Camera3();
	~Camera3();
	void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Reset(const Vector3& pos, const Vector3& target, const Vector3& up);
	void Update(double dt, int gameState);
	void boundsCheck(int gameState);
	bool checkPosition(float upperX, float lowerX, float y, float upperZ, float lowerZ);
	bool checkPrevPosition(float upperX, float lowerX, float y, float upperZ, float lowerZ);
	void findClosestPosition(float upperX, float lowerX, float y, float upperZ, float lowerZ);
	static void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
};

#endif