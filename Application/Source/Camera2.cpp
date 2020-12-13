#include "Camera2.h"
#include "Application.h"
#include "Mtx44.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera2::Camera2()
{
	phi = 10;
	theta = 10;
	radius = 20.0f;
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera2::~Camera2()
{
}

/******************************************************************************/
/*!
\brief
Initialize camera

\param pos - position of camera
\param target - where the camera is looking at
\param up - up vector of camera
*/
/******************************************************************************/
void Camera2::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = right.Cross(view).Normalized();
}

/******************************************************************************/
/*!
\brief
Reset the camera settings
*/
/******************************************************************************/
void Camera2::Reset(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = right.Cross(view).Normalized();
}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void Camera2::Update(double dt)
{
	static const float CAMERA_SPEED = 50.0f;

	Vector3 view = (target - position).Normalized();

	if (Application::IsKeyPressed('W'))
	{
		//create rotation matrix
		Mtx44 rotation;
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		rotation.SetToRotation(-CAMERA_SPEED * dt, right.x, right.y, right.z);
		//apply rotation matrix
		position = rotation * position;
		up = right.Cross(view).Normalized();
	}
	if (Application::IsKeyPressed('A'))
	{
		//create rotation matrix
		Mtx44 rotation;
		rotation.SetToRotation(-CAMERA_SPEED * dt, 0, 1, 0);
		//apply rotation matrix
		position = rotation * position;
		up = rotation * up;
	}
	if (Application::IsKeyPressed('S'))
	{
		//create rotation matrix
		Mtx44 rotation;
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		rotation.SetToRotation(CAMERA_SPEED * dt, right.x, right.y, right.z);
		//apply rotation matrix
		position = rotation * position;
		up = right.Cross(view).Normalized();
	}
	if (Application::IsKeyPressed('D'))
	{
		//create rotation matrix
		Mtx44 rotation;
		rotation.SetToRotation(CAMERA_SPEED * dt, 0, 1, 0);
		//apply rotation matrix
		position = rotation * position;
		up = rotation * up;
	}
	if (Application::IsKeyPressed('N'))
	{
		position += view * (CAMERA_SPEED / 2) * dt;
	}
	if (Application::IsKeyPressed('M'))
	{
		position -= view * (CAMERA_SPEED / 2) * dt;
	}

	
	//if (Application::IsKeyPressed('W'))
	//	phi -= CAMERA_SPEED * static_cast<float>(dt); // move camera up
	//if (Application::IsKeyPressed('A'))
	//	theta += CAMERA_SPEED * static_cast<float>(dt); // move camera left
	//if (Application::IsKeyPressed('S'))
	//	phi += CAMERA_SPEED * static_cast<float>(dt); // move camera down
	//if (Application::IsKeyPressed('D'))
	//	theta -= CAMERA_SPEED * static_cast<float>(dt); // move camera right
	//if (Application::IsKeyPressed('N'))
	//	radius += CAMERA_SPEED * static_cast<float>(dt) * 50; // move camera in
	//if (Application::IsKeyPressed('M'))
	//	radius -= CAMERA_SPEED * static_cast<float>(dt) * 50; // move camera out

	//if (radius <= 0.2)
	//	radius = 0.3;
	//this->position.x = radius * cosf(phi) * cosf(theta);

	///*if (phi >= 89)
	//	phi = -87;
	//else if (phi <= -89)
	//	phi = 87;*/

	//this->position.y = radius * sinf(phi);

	//this->position.z = radius * cosf(phi) * sinf(theta);
}

