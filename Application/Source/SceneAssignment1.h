#ifndef SCENE_ASSIGNMENT_1_H
#define SCENE_ASSIGNMENT_1_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"

class SceneAssignment1 : public Scene
{

private:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_EYE,
		GEO_HEAD,
		GEO_BLACK_CONE,
		GEO_WHITE_CONE,
		GEO_OVAL_SPHERE,
		GEO_BLACK_HEMISPHERE,
		GEO_BLACK_SHAVED_CONE,
		GEO_WHITE_SHAVED_CONE,
		GEO_BLACK_CYLINDER,
		GEO_WHITE_CYLINDER_HEMISPHERE,
		GEO_BELT_CYLINDER,
		GEO_TORUS,
		GEO_QUARTER_TORUS,
		GEO_BLADE,
		GEO_SPHERE,
		GEO_LIGHTBALL,
		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_TOTAL,
	};
	bool lightOn;
	bool axesOn;

	float rotateHead;
	int rotateHeadState;
	//body related transformation
	float translateBodyX;
	float translateBodyY;
	int translateBodyYState;
	float translateBodyZ;
	int translateBodyZState;
	float rotateBodyX;
	int rotateBodyXState;
	float rotateBodyY;
	int rotateBodyYState;

	//arm related transformation
	float leftUpperArmRotateAngleZ;
	float leftUpperArmRotateAngleX;
	int leftUpperArmRotateStateZ; 
	int leftUpperArmRotateStateX;
	float leftLowerArmRotateAngle;
	int leftLowerArmRotateState;
	float rightUpperArmRotateAngleZ;
	float rightUpperArmRotateAngleX;
	int rightUpperArmRotateStateZ;
	int rightUpperArmRotateStateX;
	float rightLowerArmRotateAngle;
	int rightLowerArmRotateState;

	//leg related transformation
	float rotateUpperLegAngle;
	float rotateLowerLegAngle;
	int upperLegRotateState;
	int lowerLegRotateState;

	//sword transformation
	float swordRotateAngleX;
	int swordRotateStateX;
	float swordRotateAngleY;
	int swordRotateStateY;
	float swordRotateAngleZ;
	float swordRotateStateZ;
	
	//general stuff
	bool pressed[4];
	bool isAttacking;
	int attackingPhase;
	bool isWalking;
	bool isDancing;
	int danceState;
	double timer;
	Camera2 camera;

	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	MS modelStack, viewStack, projectionStack;

	Light light[1];

	void RenderMesh(Mesh* mesh, bool enableLight);

public:
	SceneAssignment1();
	~SceneAssignment1();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	void walking(float LSPEED, double dt);
	void attacking(float LSPEED, double dt);
	void dancing(float LSPEED, double dt);
	void reset(void);
	void renderFloor(void);

	//morgana functions
	void renderMorgana(void);
	void renderHead(void);
	void renderScarf(void);
	void renderLeftArm(void);
	void renderRightArm(void);
	void renderBelt(void);
	void renderLeftLeg(void);
	void renderRightLeg(void);
	void renderTail(void);

	//sword functions
	void renderSword(void);
	void renderHilt(void);
	void renderBlade(void);
};
//star use 3 triangle maybe
#endif