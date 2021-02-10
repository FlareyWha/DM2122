#ifndef SCENE_ASSIGNMENT_2_H
#define SCENE_ASSIGNMENT_2_H

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "LoadCSV.h"
#include "Enemy.h"

class SceneAssignment2 : public Scene
{

private:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		//morgana shapes --------------------------------
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
		//end of morgana shapes -------------------------
		GEO_BLACK_QUAD,
		//skybox -----------------------------------
		GEO_SUNSETLEFT,
		GEO_SUNSETRIGHT,
		GEO_SUNSETTOP,
		GEO_SUNSETBOTTOM,
		GEO_SUNSETFRONT,
		GEO_SUNSETBACK,
		//end of skybox ----------------------------
		//castle----------------------------------
		GEO_DOOR,
		GEO_WALLDOOR,
		GEO_WALL,
		GEO_WALLCORNERHALF,
		GEO_WALLCORNERHALFTOWER,
		GEO_TOWERSQUAREBASE,
		GEO_TOWERSQUAREARCH,
		GEO_TOWERSQUAREMID,
		GEO_TOWERSQUARETOPROOF,
		GEO_BARREL,
		//end of castle---------------------------
		//room
		GEO_CRATE,
		GEO_ENEMY,
		GEO_REDQUAD,
		GEO_KEY,
		GEO_CROWN,
		GEO_TEXT,
		GEO_FLOOR,
		GEO_LIGHTBALL,
		GEO_LIGHTBALL_2,
		GEO_LIGHTBALL_3,
		GEO_LIGHTBALL_4,
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

		//Light 0
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		//light 1
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		//light 2
		U_LIGHT2_POSITION,
		U_LIGHT2_COLOR,
		U_LIGHT2_POWER,
		U_LIGHT2_KC,
		U_LIGHT2_KL,
		U_LIGHT2_KQ,
		U_LIGHT2_TYPE,
		U_LIGHT2_SPOTDIRECTION,
		U_LIGHT2_COSCUTOFF,
		U_LIGHT2_COSINNER,
		U_LIGHT2_EXPONENT,

		//light 3
		U_LIGHT3_POSITION,
		U_LIGHT3_COLOR,
		U_LIGHT3_POWER,
		U_LIGHT3_KC,
		U_LIGHT3_KL,
		U_LIGHT3_KQ,
		U_LIGHT3_TYPE,
		U_LIGHT3_SPOTDIRECTION,
		U_LIGHT3_COSCUTOFF,
		U_LIGHT3_COSINNER,
		U_LIGHT3_EXPONENT,

		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

	bool lightOn;
	bool axesOn;
	float avgFPS;

	//morgana variables ------------------------------------------------------------
	float rotateHead;
	int rotateHeadState;
	//body related transformation
	float translateBodyX;
	int translateBodyXState;
	float translateBodyY;
	int translateBodyYState;
	float translateBodyZ;
	int translateBodyZState;
	float translateBodyZExtra;
	int translateBodyZExtraState;
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
	bool isAttacking;
	int attackingPhase;
	bool isWalking;
	bool isDancing;
	int danceState;
	double timer;
	//end of morgana variables -------------------------------------------------------

	float doorRotateAngle;
	bool doorOpen;
	bool pickUpKey;
	bool pickUpCrown;
	double textTimer;
	float fakeFrontScale;

	int gameState;
	int subGameState;
	bool showDebugInfo;

	float rotateAngle;
	float translateX;
	float scaleAll;
	Camera3 camera;
	LoadCSV csvFile;
	Enemy enemy[9];

	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	MS modelStack, viewStack, projectionStack;

	Light light[4]; //change when adding more

	void RenderMesh(Mesh* mesh, bool enableLight);
	void RenderSkybox();
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey);
	void renderLights();
	void assignParametersForLights();
	void initLights();
	void initMorgana();
	void initScene();
	void initCastle();
	void initRoom();

public:
	SceneAssignment2();
	~SceneAssignment2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void renderGameText(void);
	void gameStateManager(double dt);
	int enemyDirectionCheck(int enemyNumber, Vector3 tempPos);
	void collisionWithEnemy(void);
	void renderCastle(void);
	void renderRoom(void);
	void renderEnemy(void);
	void renderCover(void);
	void renderDebug(void);

	//morgana stuff
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