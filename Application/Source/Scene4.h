#ifndef SCENE_4_H
#define SCENE_4_H

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"

class Scene4 : public Scene
{

private:
	enum GEOMETRY_TYPE
	{
		GEO_AXES = 0,
		GEO_QUAD = 1,
		GEO_CUBE = 2,
		GEO_CIRCLE = 3,
		GEO_RING = 4,
		GEO_SPHERE = 5,
		GEO_HEMISPHERE = 6,
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
	Camera camera;

	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

public:
	Scene4();
	~Scene4();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};
//star use 3 triangle maybe
#endif