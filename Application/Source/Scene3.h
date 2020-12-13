#ifndef SCENE_3_H
#define SCENE_3_H

#include "Scene.h"

class Scene3 : public Scene
{

private:
	enum GEOMETRY_TYPE
	{
		RIGHT_ANGLED_TRIANGLE = 0,
		ISOCELES_TRIANGLE = 1,
		EQUALITERAL_TRIANGLE = 2,
		SQUARE = 3,
		SQUARE2 = 4,
		SQUARE3 = 5,
		CIRCLE = 6,
		CIRCLE2 = 7,
		CIRCLE3 = 8,
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
	float colour;
	bool skySwitch;

	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

public:
	Scene3();
	~Scene3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
};
//star use 3 triangle maybe
#endif