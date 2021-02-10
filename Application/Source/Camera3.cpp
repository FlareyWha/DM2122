#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"
#include "MatrixStack.h"
#include "SceneAssignment2.h"

float Camera3::yaw = -90.0f;
float Camera3::pitch = 0.0f;
Vector3 Camera3::position(0, 0, 0);
Vector3 Camera3::target(0, 0, 0);
Vector3 Camera3::up(0, 0, 0);
Vector3 Camera3::view(0, 0, 0);
Vector3 Camera3::right(0, 0, 0);

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera3::Camera3()
{
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera3::~Camera3()
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
void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
	debugMode = false;
	prevPos.Set(0, 0, 0);
}

/******************************************************************************/
/*!
\brief
Reset the camera settings
*/
/******************************************************************************/
void Camera3::Reset(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void Camera3::Update(double dt, int gameState)
{
	static const float CAMERA_SPEED = 50.0f;

	prevPos = position;

	view = (target - position).Normalized();
	right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();

	if (Application::IsKeyPressed('W'))
	{
		position += view * CAMERA_SPEED * static_cast<float>(dt);
		if (!debugMode)
		{
			position.y = 0;
			boundsCheck(gameState);
		}
		target = position + view;
	}
	if (Application::IsKeyPressed('A'))
	{
		position -= right * CAMERA_SPEED * static_cast<float>(dt);
		if (!debugMode)
		{
			position.y = 0;
			boundsCheck(gameState);
		}
		target = position + view;
	}
	if (Application::IsKeyPressed('S'))
	{
		position -= view * CAMERA_SPEED * static_cast<float>(dt);
		if (!debugMode)
		{
			position.y = 0;
			boundsCheck(gameState);
		}
		target = position + view;
	}
	if (Application::IsKeyPressed('D'))
	{
		position += right * CAMERA_SPEED * static_cast<float>(dt);
		if (!debugMode)
		{
			position.y = 0;
			boundsCheck(gameState);
		}
		target = position + view;
	}
	if (Application::IsKeyPressed('N'))
	{
		position += up * CAMERA_SPEED * static_cast<float>(dt);
		target = position + view;
	}
	if (Application::IsKeyPressed('M'))
	{
		position -= up * CAMERA_SPEED * static_cast<float>(dt);
		target = position + view;
	}
	if (Application::IsKeyPressed(VK_F1))
		debugMode = true;
	else if (Application::IsKeyPressed(VK_F2))
		debugMode = false;

	//incase
	//if (Application::IsKeyPressed(VK_UP))
	//{
	//	//create rotation matrix
	//	Mtx44 rotation;
	//	rotation.SetToRotation(CAMERA_SPEED * dt, right.x, right.y, right.z);
	//	//apply rotation matrix
	//	view = rotation * view;
	//	target = position + view;
	//	up = right.Cross(view).Normalized();
	//}
	//if (Application::IsKeyPressed(VK_LEFT))
	//{
	//	//create rotation matrix
	//	Mtx44 rotation;
	//	rotation.SetToRotation(CAMERA_SPEED * dt, 0, 1, 0);
	//	//apply rotation matrix
	//	view = rotation * view;
	//	target = position + view;
	//	up = rotation * up;
	//}
	//if (Application::IsKeyPressed(VK_DOWN))
	//{
	//	//create rotation matrix
	//	Mtx44 rotation;
	//	rotation.SetToRotation(-CAMERA_SPEED * dt, right.x, right.y, right.z);
	//	//apply rotation matrix
	//	view = rotation * view;
	//	target = position + view;
	//	up = right.Cross(view).Normalized();
	//}
	//if (Application::IsKeyPressed(VK_RIGHT))
	//{
	//	//create rotation matrix
	//	Mtx44 rotation;
	//	rotation.SetToRotation(-CAMERA_SPEED * dt, 0, 1, 0);
	//	//apply rotation matrix
	//	view = rotation * view;
	//	target = position + view;
	//	up = rotation * up;
	//}
}

bool Camera3::checkPosition(float upperX, float lowerX, float y, float upperZ, float lowerZ) //if camera inside the box kick it out somehow maybe get a direction camera is moving in and then reverse it? idk
{
	if ((position.x >= lowerX && position.x <= upperX) && position.y == y && (position.z >= lowerZ && position.z <= upperZ))
		return true;
	else
		return false;
}

bool Camera3::checkPrevPosition(float upperX, float lowerX, float y, float upperZ, float lowerZ)
{
	if ((prevPos.x >= lowerX && prevPos.x <= upperX) && prevPos.y == y && (prevPos.z >= lowerZ && prevPos.z <= upperZ))
		return true;
	else
		return false;
}

void Camera3::findClosestPosition(float upperX, float lowerX, float y, float upperZ, float lowerZ)
{
}

void Camera3::boundsCheck(int gameState)
{
	bool roomBounds = false;
	if (gameState > 2)
		roomBounds = true;

	switch (gameState)
	{
	case 1: 
		position.x = Math::Clamp(position.x, -100.f, 100.f); //outer wall
		position.z = Math::Clamp(position.z, -15.f, 105.f); //outer wall
		break;
	case 2:
		position.x = Math::Clamp(position.x, -100.f, 100.f); //outer wall
		if (checkPrevPosition(-41, -79, 0, -88, -126) == false && checkPosition(-41, -79, 0, -88, -126) == true)
			position = prevPos;
		if (checkPrevPosition(77,  43, 0, -90, -124) == false && checkPosition(77, 43, 0, -90, -124) == true)
			position = prevPos;
		if (checkPrevPosition(-5, -100, 0, -15, -55) == false && checkPosition(-5, -100, 0, -15, -55) == true)
			position = prevPos;
		if (checkPrevPosition(100, 5, 0, -15, -55) == false && checkPosition(100, 5, 0, -15, -55) == true)
			position = prevPos;
		break;
	case 3:
		if (position.z <= -680)
			position.z = -680;
		break;
	case 4: 
		if (position.z <= -1045)
			position.z = -1045;
		break;
	case 5:
		if (position.z <= -1045)
			position.z = -1045;
		if (position.x <= 40)
			position.x = 40;
		break;
	case 6:
		if (position.z <= -1045)
			position.z = -1045;
		break;
	default:
		break;
	}

	if (roomBounds == true)
	{
		position.x = Math::Clamp(position.x, -145.f, 145.f); //outer wall
		position.z = Math::Clamp(position.z, -1165.f, -555.f); //outer wall
		if (checkPrevPosition(148, -2, 0, -552, -582) == false && checkPosition(148, -2, 0, -552, -582) == true)
			position = prevPos;
		if (checkPrevPosition(67, -148, 0, -592, -607) == false && checkPosition(67, -148, 0, -592, -607) == true)
			position = prevPos;
		if (checkPrevPosition(148, -83, 0, -653, -667) == false && checkPosition(148, -83, 0, -653, -667) == true)
			position = prevPos;
		if (checkPrevPosition(148, 37, 0, -652, -707) == false && checkPosition(148, 37, 0, -652, -707) == true)
			position = prevPos;
		if (checkPrevPosition(12, -148, 0, -683, -748) == false && checkPosition(12, -148, 0, -682, -748) == true)
			position = prevPos;
		if (checkPrevPosition(92, 12, 0, -732, -747) == false && checkPosition(92, 12, 0, -732, -747) == true)
			position = prevPos;
		if (checkPrevPosition(122, 108, 0, -732, -767) == false && checkPosition(122, 108, 0, -732, -767) == true)
			position = prevPos;
		if (checkPrevPosition(148, 2, 0, -792, -807) == false && checkPosition(145, 2, 0, -792, -807) == true)
			position = prevPos;
		if (checkPrevPosition(-15, -148, 0, -792, -807) == false && checkPosition(-15, -148, 0, -792, -807) == true)
			position = prevPos;
		if (checkPrevPosition(-67, -122, 0, -833, -882) == false && checkPosition(-67, -122, 0, -833, -882) == true)
			position = prevPos;
		if (checkPrevPosition(148, -67, 0, -863, -882) == false && checkPosition(148, -67, 0, -863, -882) == true)
			position = prevPos;
		if (checkPrevPosition(-58, -72, 0, -872, -908) == false && checkPosition(-58, -72, 0, -872, -908) == true)
			position = prevPos;
		if (checkPrevPosition(-58, -122, 0, -892, -908) == false && checkPosition(-58, -122, 0, -892, -908) == true)
			position = prevPos;
		if (checkPrevPosition(82, -148, 0, -937, -952) == false && checkPosition(82, -148, 0, -937, -952) == true)
			position = prevPos;
	}
}

void Camera3::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	const float sensitivity = 0.1f;

	if (pitch < -70 || pitch > 70)
		xoffset = 0;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.9f)
	{
		pitch = 89.9f;
		yoffset = 0;
	}
	if (pitch < -89.9f)
	{
		pitch = -89.9f;
		yoffset = 0;
	}

	view = (target - position).Normalized();
	right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();

	Mtx44 rotation;
	rotation.SetToRotation(-xoffset, 0, 1, 0);
	Mtx44 rotation2;
	rotation2.SetToRotation(yoffset, right.x, right.y, right.z);
	Mtx44 finalRotation = rotation.operator*(rotation2);
	view = finalRotation * view;
	target = position + view;

	/*view.x = cos(Math::DegreeToRadian(yaw)) * cos(Math::DegreeToRadian(pitch));
	view.y = sin(Math::DegreeToRadian(pitch));
	view.z = sin(Math::DegreeToRadian(yaw)) * cos(Math::DegreeToRadian(pitch));
	view.Normalize();
	target = position + view;*/

	//std::cout << yaw << ", " << pitch << std::endl;
}




