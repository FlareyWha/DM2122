#ifndef SCENE_5_H
#define SCENE_5_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"

class Scene5 : public Scene
{

private:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_RING,
		GEO_RING_2,
		GEO_SPHERE,
		GEO_SPHERE_2,
		GEO_SPHERE_3,
		GEO_SPHERE_4,
		GEO_SPHERE_5,
		GEO_HEMISPHERE,
		GEO_CYLINDER,
		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_TOTAL,
	};

	float rotateAngle;
	float translateX;
	float scaleAll;
	Camera2 camera;

	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	MS modelStack, viewStack, projectionStack;

public:
	Scene5();
	~Scene5();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};
//star use 3 triangle maybe
#endif