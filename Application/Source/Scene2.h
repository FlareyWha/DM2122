#ifndef SCENE_2_H
#define SCENE_2_H

#include "Scene.h"

class Scene2 : public Scene
{

private:
	enum GEOMETRY_TYPE
	{
		EIGHT_POLYGON = 0,
		FIVE_STAR = 1,
		RANDOM_SHAPE = 2,
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

	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

public:
	Scene2();
	~Scene2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};
//star use 3 triangle maybe
#endif