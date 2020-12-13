#include "SceneAssignment1.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "Vertex.h"
#include "Utility.h"
#include "shader.hpp"

SceneAssignment1::SceneAssignment1()
{
}

SceneAssignment1::~SceneAssignment1()
{
}

void SceneAssignment1::Init()
{
	// Init VBO here
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//Shading.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	glUseProgram(m_programID);

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	// Make sure you pass uniform parameters after glUseProgram()
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);

	// Generate a default VBO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(0,1,0), 1.0f);

	meshList[GEO_EYE] = MeshBuilder::GenerateEye("eye");
	meshList[GEO_EYE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_EYE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_EYE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_EYE]->material.kShininess = 2.f;

	meshList[GEO_HEAD] = MeshBuilder::GenerateHead("head", 1.2f, 1.7f, 1.1f, 1.6f, 1.7f, 0.9f);
	meshList[GEO_HEAD]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HEAD]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HEAD]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_HEAD]->material.kShininess = 2.f;

	meshList[GEO_BLACK_CONE] = MeshBuilder::GenerateConeRingBase("blackCone", Color(1, 1, 1), 50, 1, 0.9, 2);
	meshList[GEO_BLACK_CONE]->material.kAmbient.Set(0.0f, 0.0f, 0.0f);
	meshList[GEO_BLACK_CONE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BLACK_CONE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BLACK_CONE]->material.kShininess = 2.f;

	meshList[GEO_WHITE_CONE] = MeshBuilder::GenerateCone("whiteCone", Color(1, 1, 1), 50, 1.1, 2);
	meshList[GEO_WHITE_CONE]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_WHITE_CONE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_WHITE_CONE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_WHITE_CONE]->material.kShininess = 1.f;

	meshList[GEO_OVAL_SPHERE] = MeshBuilder::GenerateOvalSphere("ovalsphere", Color(1, 1, 1), 2.0f, 1.0f, 0.1f);
	meshList[GEO_OVAL_SPHERE]->material.kAmbient.Set(0.98f, 0.74f, 0.14f);
	meshList[GEO_OVAL_SPHERE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_OVAL_SPHERE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_OVAL_SPHERE]->material.kShininess = 2.f;

	//for bottom half of face, hands
	meshList[GEO_BLACK_HEMISPHERE] = MeshBuilder::GenerateHemisphere("hemisphere", Color(1, 1, 1), 1.0f);
	meshList[GEO_BLACK_HEMISPHERE]->material.kAmbient.Set(0.0f, 0.0f, 0.0f);
	meshList[GEO_BLACK_HEMISPHERE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BLACK_HEMISPHERE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BLACK_HEMISPHERE]->material.kShininess = 2.f;

	meshList[GEO_BLACK_CYLINDER] = MeshBuilder::GenerateCylinderNoBase("blackcylinder", Color(1, 1, 1), 20, 1.0f, 5.f);
	meshList[GEO_BLACK_CYLINDER]->material.kAmbient.Set(0.0f, 0.0f, 0.0f);
	meshList[GEO_BLACK_CYLINDER]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BLACK_CYLINDER]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BLACK_CYLINDER]->material.kShininess = 2.f;

	meshList[GEO_WHITE_CYLINDER_HEMISPHERE] = MeshBuilder::GenerateCylinderHemisphere("whitecylinder", Color(1, 1, 1), 20, 1.0f, 3.f);
	meshList[GEO_WHITE_CYLINDER_HEMISPHERE]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_WHITE_CYLINDER_HEMISPHERE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_WHITE_CYLINDER_HEMISPHERE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_WHITE_CYLINDER_HEMISPHERE]->material.kShininess = 2.f;

	meshList[GEO_BELT_CYLINDER] = MeshBuilder::GenerateCylinder("beltcylinder", Color(1, 1, 1), 3, 1.0f, 0.5f);
	meshList[GEO_BELT_CYLINDER]->material.kAmbient.Set(0.0f, 0.0f, 0.0f);
	meshList[GEO_BELT_CYLINDER]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BELT_CYLINDER]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BELT_CYLINDER]->material.kShininess = 2.f;

	meshList[GEO_BLACK_SHAVED_CONE] = MeshBuilder::GenerateShavedCone("blackcone", Color(1, 1, 1), 50, 0.9f, 2.f);
	meshList[GEO_BLACK_SHAVED_CONE]->material.kAmbient.Set(0.0f, 0.0f, 0.0f);
	meshList[GEO_BLACK_SHAVED_CONE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BLACK_SHAVED_CONE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BLACK_SHAVED_CONE]->material.kShininess = 2.f;

	meshList[GEO_WHITE_SHAVED_CONE] = MeshBuilder::GenerateShavedCone("whitecone", Color(1, 1, 1), 50, 0.3f, 1.f);
	meshList[GEO_WHITE_SHAVED_CONE]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_WHITE_SHAVED_CONE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_WHITE_SHAVED_CONE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_WHITE_SHAVED_CONE]->material.kShininess = 2.f;

	meshList[GEO_TORUS] = MeshBuilder::GenerateTorus("torus", Color(1, 1, 1), 36, 36, 1.0f, 0.2f);
	meshList[GEO_TORUS]->material.kAmbient.Set(0.98f, 0.74f, 0.14f);
	meshList[GEO_TORUS]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_TORUS]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_TORUS]->material.kShininess = 1.f;

	meshList[GEO_QUARTER_TORUS] = MeshBuilder::GenerateQuarterTorus("torus", Color(1, 1, 1), 20, 20, 1.0f, 0.2f);
	meshList[GEO_QUARTER_TORUS]->material.kAmbient.Set(0.0f, 0.0f, 0.0f);
	meshList[GEO_QUARTER_TORUS]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_QUARTER_TORUS]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_QUARTER_TORUS]->material.kShininess = 2.f;

	meshList[GEO_BLADE] = MeshBuilder::GenerateBlade("blade", Color(1, 1, 1), 2.0f);
	meshList[GEO_BLADE]->material.kAmbient.Set(0.753f, 0.753f, 0.753f);
	meshList[GEO_BLADE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BLADE]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BLADE]->material.kShininess = 1.f;

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 1), 1.0f);
	meshList[GEO_SPHERE]->material.kAmbient.Set(0.0f, 0.0f, 0.0f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE]->material.kShininess = 1.f;

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 1.0f);
	
	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);

	rotateHead = 0;
	rotateHeadState = 1;
	translateBodyX = 0;
	translateBodyY = 0;
	translateBodyYState = 1;
	translateBodyZ = 0;
	translateBodyZState = 1;
	rotateBodyX = 0;
	rotateBodyXState = 1;
	rotateBodyY = 0;
	rotateBodyYState = 1;
	leftUpperArmRotateAngleZ = 0;
	leftUpperArmRotateAngleX = 0;
	leftUpperArmRotateStateZ = 1;
	leftUpperArmRotateStateX = 1;
	leftLowerArmRotateAngle = 0;
	leftLowerArmRotateState = 1;
	rightUpperArmRotateAngleZ = 0;
	rightUpperArmRotateAngleX = 0;
	rightUpperArmRotateStateZ = 1;
	rightUpperArmRotateStateX = -1;
	rightLowerArmRotateAngle = 0;
	rightLowerArmRotateState = 1;
	upperLegRotateState = 1;
	lowerLegRotateState = 1;
	rotateUpperLegAngle = 0;
	rotateLowerLegAngle = 0;
	swordRotateAngleX = 0;
	swordRotateStateX = 1;
	swordRotateAngleY = 0;
	swordRotateStateY= 1;
	swordRotateAngleZ = 0;
	swordRotateStateZ = 1;
	for (int i = 0; i < 4; i++)
		pressed[i] = false;
	isWalking = false;
	isAttacking = false;
	attackingPhase = 0;
	isDancing = false;
	danceState = 0;
	timer = 0;
	camera.Init(Vector3(10, 10, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	lightOn = true;
	axesOn = false;
}

void SceneAssignment1::Update(double dt)
{
	static const float LSPEED = 10.0f;
	//change so each one is not synced
	camera.Update(dt);

	if (Application::IsKeyPressed('1')) //0x31
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //0x32
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3')) //0x33
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (Application::IsKeyPressed('4')) //0x34
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (Application::IsKeyPressed('9'))
		lightOn = false;
	if (Application::IsKeyPressed('0'))
		lightOn = true;
	if (Application::IsKeyPressed('Z'))
		axesOn = false;
	if (Application::IsKeyPressed('X'))
		axesOn = true;
	if (Application::IsKeyPressed('R'))
	{
		reset();
		translateBodyX = translateBodyY = translateBodyZ = 0;
		isWalking = false;
		isAttacking = false;
		isDancing = false;
		attackingPhase = 0;
		timer = 0;
		light[0].position.Set(0, 20, 0);
		camera.Reset(Vector3(10, 10, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	}

	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);

	if (Application::IsKeyPressed(VK_UP) && isAttacking == false && isDancing == false)
	{
		translateBodyZ += (float)(3 * dt);
		isWalking = true;
		pressed[0] = true;
		rotateBodyY = 0;
	}
	else if (Application::IsKeyReleased(VK_UP) && pressed[0] == true)
	{
		isWalking = false;
		pressed[0] = false;
	}
	if (Application::IsKeyPressed(VK_LEFT) && isAttacking == false && isDancing == false)
	{
		translateBodyX += (float)(3 * dt);
		isWalking = true;
		pressed[1] = true;
		rotateBodyY = 90;
	}
	else if (Application::IsKeyReleased(VK_LEFT) && pressed[1] == true)
	{
		isWalking = false;
		pressed[1] = false;
	}
	if (Application::IsKeyPressed(VK_DOWN) && isAttacking == false && isDancing == false)
	{
		translateBodyZ -= (float)(3 * dt);
		isWalking = true;
		pressed[2] = true;
		rotateBodyY = 180;
	}
	else if (Application::IsKeyReleased(VK_DOWN) && pressed[2] == true)
	{
		isWalking = false;
		pressed[2] = false;
	}
	if (Application::IsKeyPressed(VK_RIGHT) && isAttacking == false && isDancing == false)
	{
		translateBodyX -= (float)(3 * dt);
		isWalking = true;
		pressed[3] = true;
		rotateBodyY = -90;
	}
	else if (Application::IsKeyReleased(VK_RIGHT) && pressed[3] == true)
	{
		isWalking = false;
		pressed[3] = false;
	}
	if (Application::IsKeyPressed(VK_SPACE)) //attack
	{
		reset();
		isAttacking = true;
		rotateBodyXState = 0;
		attackingPhase = 1;
		leftUpperArmRotateStateZ = -1;
		swordRotateStateX = 0;
		swordRotateStateY = 1;
		leftLowerArmRotateState = 0;
	}

	if (Application::IsKeyPressed('G'))
	{
		reset();
		isDancing = true;
		danceState = 1;
		rotateHeadState = 0;
		rotateBodyYState = 1;
		leftUpperArmRotateStateX = 1;
		leftLowerArmRotateState = -1;
		rightUpperArmRotateStateX = -1;
		rightUpperArmRotateStateZ = 1;
		rightLowerArmRotateState = -1;
		upperLegRotateState = -1;
		lowerLegRotateState = -1;
	}

	if (isWalking == true)
		walking(LSPEED, dt);

	if (isAttacking == true)
		attacking(LSPEED, dt);

	if (isDancing == true)
		dancing(LSPEED, dt);
}

void SceneAssignment1::Render()
{
	// Render VBO here
	// set background colour to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Clear color buffer for every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

	Mtx44 mvp;

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]);

	if (axesOn == true)
		RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	renderFloor();
	renderMorgana();
}

void SceneAssignment1::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SceneAssignment1::walking(float LSPEED, double dt)
{
	if (leftUpperArmRotateAngleX >= 22.5)
		leftUpperArmRotateStateX = -1;
	else if (leftUpperArmRotateAngleX <= -22.5)
		leftUpperArmRotateStateX = 1;

	if (rightUpperArmRotateAngleX >= 22.5)
		rightUpperArmRotateStateX = -1;
	else if (rightUpperArmRotateAngleX <= -22.5)
		rightUpperArmRotateStateX = 1;

	if (rotateUpperLegAngle >= 22.5)
		upperLegRotateState = -1;
	else if (rotateUpperLegAngle <= -22.5)
		upperLegRotateState = 1;
	if (rotateLowerLegAngle >= 33.75)
		lowerLegRotateState = -1;
	else if (rotateLowerLegAngle <= -33.75)
		lowerLegRotateState = 1;

	leftUpperArmRotateAngleX += (float)(leftUpperArmRotateStateX * LSPEED * 10 * dt);
	rightUpperArmRotateAngleX += (float)(rightUpperArmRotateStateX * LSPEED * 10 * dt);
	rotateUpperLegAngle += (float)(upperLegRotateState * LSPEED * 10 * dt);
	rotateLowerLegAngle += (float)(lowerLegRotateState * LSPEED * 15 * dt);

	isAttacking = false;
	isDancing = false;
}

void SceneAssignment1::attacking(float LSPEED, double dt)
{
	switch (attackingPhase)
	{
	case 1:
		if (leftUpperArmRotateAngleZ <= -45)
			leftUpperArmRotateStateZ = 0;
		if (leftUpperArmRotateAngleX >= 35)
			leftUpperArmRotateStateX = 0;
		if (translateBodyY >= 2)
			translateBodyYState = -1;
		else if (translateBodyY < 0)
			translateBodyYState = 0;
		if (rotateUpperLegAngle >= 22.5)
			upperLegRotateState = 0;
		if (rotateLowerLegAngle >= 33.75)
			lowerLegRotateState = 0;
		if (translateBodyZ >= 10)
			translateBodyZState = 0;
		if (swordRotateAngleY >= 135)
			swordRotateStateY = 0;
		if (swordRotateAngleZ >= 110)
			swordRotateStateZ = 0;
		if (leftUpperArmRotateStateZ == 0 && leftUpperArmRotateStateX == 0 && translateBodyYState == 0 && translateBodyZState == 0 && upperLegRotateState == 0 && swordRotateStateY == 0)
		{
			attackingPhase = 2;
			swordRotateStateX = 1;
			swordRotateStateY = 1;
			leftUpperArmRotateStateX = -1;
			leftLowerArmRotateState = -1;
		}
		break;

	case 2:
		if (leftUpperArmRotateAngleX <= -20)
			leftUpperArmRotateStateX = 0;
		if (leftLowerArmRotateAngle <= -70)
			leftLowerArmRotateState = 0;
		if (swordRotateAngleX >= 15)
			swordRotateStateX = 0;
		if (swordRotateAngleY >= 180)
			swordRotateStateY = 0;
		if (leftUpperArmRotateStateX == 0 && leftLowerArmRotateState == 0)
			timer += dt;
		if (timer >= 1.5)
		{
			attackingPhase = 3;
			swordRotateStateX = -1;
			leftUpperArmRotateStateZ = 1;
			leftUpperArmRotateStateX = 1;
			leftLowerArmRotateState = 1;
			timer = 0;
		}
		break;
	case 3:
		if (leftUpperArmRotateAngleZ >= 0)
			leftUpperArmRotateStateZ = 0;
		if (leftUpperArmRotateAngleX >= 0)
			leftUpperArmRotateStateX = 0;
		if (leftLowerArmRotateAngle >= 0)
			leftLowerArmRotateState = 0;
		if (swordRotateAngleX <= 0)
			swordRotateStateX = 0;
		if (leftUpperArmRotateStateZ == 0 && leftUpperArmRotateStateX == 0 && leftLowerArmRotateState == 0)
		{
			attackingPhase = 4;
			swordRotateStateY = -1;
			swordRotateStateZ = -1;
			rotateBodyXState = 1;
			translateBodyY = 0.1;
			translateBodyYState = 1;
			translateBodyZState = -1;
			upperLegRotateState = -1;
			lowerLegRotateState = -1;
		}
		break;

	case 4:
		if (swordRotateAngleY <= 0)
			swordRotateStateY = 0;
		if (swordRotateAngleZ <= 0)
			swordRotateStateZ = 0;
		if (rotateUpperLegAngle <= 0)
			upperLegRotateState = 0;
		if (rotateLowerLegAngle <= 0)
			lowerLegRotateState = 0;
		if (rotateBodyX >= 360)
			rotateBodyXState = 0;
		if (translateBodyY >= 10)
			translateBodyYState = -1;
		else if (translateBodyY < 0)
			translateBodyYState = 0;
		if (translateBodyZ <= 0)
			translateBodyZState = 0;
		if (translateBodyYState == 0)
		{
			translateBodyY = translateBodyZ = rotateBodyX = rotateBodyY = leftUpperArmRotateAngleZ = leftUpperArmRotateAngleX = leftLowerArmRotateAngle = rotateUpperLegAngle = rotateLowerLegAngle = swordRotateAngleX = swordRotateAngleY = swordRotateAngleZ = 0;

			translateBodyYState = translateBodyZState = rotateBodyXState = leftUpperArmRotateStateZ = leftUpperArmRotateStateX = leftLowerArmRotateState = upperLegRotateState = lowerLegRotateState = swordRotateStateX = swordRotateStateY = swordRotateStateZ = 1.0;
			attackingPhase = 0;
			timer = 0;
			isAttacking = false;
		}
		break;
	default:
		break;
	}
	if (attackingPhase == 1)
	{
		translateBodyZ += (float)(translateBodyZState * LSPEED * dt);
		translateBodyY += (float)(translateBodyYState * 4 * dt);
	}
	else
	{
		translateBodyZ += (float)(translateBodyZState * 6 * dt);
		translateBodyY += (float)(translateBodyYState * LSPEED * dt);
	}
	rotateBodyX += (float)(rotateBodyXState * LSPEED * 20 * dt);
	leftUpperArmRotateAngleZ += (float)(leftUpperArmRotateStateZ * LSPEED * 40 * dt);
	leftLowerArmRotateAngle += (float)(leftLowerArmRotateState * LSPEED * 40 * dt);
	leftUpperArmRotateAngleX += (float)(leftUpperArmRotateStateX * LSPEED * 40 * dt);
	rotateUpperLegAngle += (float)(upperLegRotateState * LSPEED * 10 * dt);
	rotateLowerLegAngle += (float)(lowerLegRotateState * LSPEED * 15 * dt);
	swordRotateAngleX += (float)(swordRotateStateX * LSPEED * 30 * dt);
	swordRotateAngleY += (float)(swordRotateStateY * LSPEED * 30 * dt);
	swordRotateAngleZ += (float)(swordRotateStateZ * LSPEED * 30 * dt);
	isWalking = false;
	isDancing = false;
}

void SceneAssignment1::dancing(float LSPEED, double dt)
{
	switch (danceState)
	{
	case 1:
		if (rotateBodyY >= 40)
			rotateBodyYState = 0;
		if (leftUpperArmRotateAngleX >= 20)
			leftUpperArmRotateStateX = 0;
		if (leftLowerArmRotateAngle <= -70)
			leftLowerArmRotateState = 0;
		if (rightUpperArmRotateAngleX <= -20)
			rightUpperArmRotateStateX = 0;
		if (rightUpperArmRotateAngleZ >= 45)
			rightUpperArmRotateStateZ = 0;
		if (rightLowerArmRotateAngle <= -50)
			rightLowerArmRotateState = 0;
		if (rotateUpperLegAngle <= -22.5)
			upperLegRotateState = 0;
		if (rotateLowerLegAngle <= -33.75)
			lowerLegRotateState = 0;

		if (rotateBodyYState == 0)
			timer += dt;
		if (timer >= 1.0)
		{
			danceState = 2;
			rotateBodyYState = -1;
			upperLegRotateState = 1;
			lowerLegRotateState = 1;
			timer = 0;
		}
		break;

	case 2:
		if (rotateBodyY <= -40)
		{
			rotateBodyYState = 0;
			timer += dt;
		}
		if (rotateUpperLegAngle >= 22.5)
			upperLegRotateState = 0;
		if (rotateLowerLegAngle >= 33.75)
			lowerLegRotateState = 0;
		if (timer >= 1.0)
		{
			danceState = 3;
			rotateHeadState = 1;
			leftUpperArmRotateStateX = -1;
			leftUpperArmRotateStateZ = -1;
			leftLowerArmRotateState = 1;
			rightUpperArmRotateStateX = 1;
			rightUpperArmRotateStateZ = -1;
			rightLowerArmRotateState = -1;
			timer = 0;
		}
		break;

	case 3:
		if (rotateHead >= 20)
			rotateHeadState = 0;
		if (leftUpperArmRotateAngleX <= -20)
			leftUpperArmRotateStateX = 0;
		if (leftUpperArmRotateAngleZ <= -45)
			leftUpperArmRotateStateZ = 0;
		if (leftLowerArmRotateAngle >= -50)
			leftLowerArmRotateState = 0;
		if (rightUpperArmRotateAngleX >= 20)
			rightUpperArmRotateStateX = 0;
		if (rightUpperArmRotateAngleZ <= 0)
			rightUpperArmRotateStateZ = 0;
		if (rightLowerArmRotateAngle <= -70)
			rightLowerArmRotateState = 0;

		if (leftUpperArmRotateStateX == 0)
			timer += dt;
		if (timer >= 1.0)
		{
			danceState = 4;
			rotateBodyYState = 1;
			upperLegRotateState = -1;
			lowerLegRotateState = -1;
			timer = 0;
		}
		break;

	case 4:
		if (rotateBodyY >= 40)
		{
			rotateBodyYState = 0;
			timer += dt;
		}
		if (rotateUpperLegAngle <= -22.5)
			upperLegRotateState = 0;
		if (rotateLowerLegAngle <= -33.75)
			lowerLegRotateState = 0;
		if (timer >= 1.0)
		{
			danceState = 5;
			rotateHeadState = -1;
			rightUpperArmRotateStateX = -1;
			rightUpperArmRotateStateZ = 1;
			rightLowerArmRotateState = 1;
			timer = 0;
		}
		break;
	case 5:
		if (rotateHead <= 0)
			rotateHeadState = 0;
		if (rightUpperArmRotateAngleX <= -20)
			rightUpperArmRotateStateX = 0;
		if (rightUpperArmRotateAngleZ >= 45)
			rightUpperArmRotateStateZ = 0;
		if (rightLowerArmRotateAngle >= -50)
			rightLowerArmRotateState = 0;

		if (rightUpperArmRotateAngleZ >= 0)
			timer += dt;
		if (timer >= 1.0)
		{
			danceState = 6;
			rotateBodyYState = -1;
			leftUpperArmRotateStateX = 1;
			leftUpperArmRotateStateZ = 1;
			leftLowerArmRotateState = 1;
			rightUpperArmRotateStateX = 1;
			rightUpperArmRotateStateZ = -1;
			rightLowerArmRotateState = 1;
			upperLegRotateState = 1;
			lowerLegRotateState = 1;
			timer = 0;
		}
		break;

	case 6:
		if (rotateBodyY <= 0)
			rotateBodyYState = 0;
		if (leftUpperArmRotateAngleX >= 0)
			leftUpperArmRotateStateX = 0;
		if (leftUpperArmRotateAngleZ >= 0)
			leftUpperArmRotateStateZ = 0;
		if (leftLowerArmRotateAngle >= 0)
			leftLowerArmRotateState = 0;
		if (rightUpperArmRotateAngleX >= 0)
			rightUpperArmRotateStateX = 0;
		if (rightUpperArmRotateAngleZ <= 0)
			rightUpperArmRotateStateZ = 0;
		if (rightLowerArmRotateAngle >= 0)
			rightLowerArmRotateState = 0;
		if (rotateUpperLegAngle >= 0)
			upperLegRotateState = 0;
		if (rotateLowerLegAngle >= 0)
			lowerLegRotateState = 0;
		if (rotateBodyYState == 0 && leftUpperArmRotateStateZ == 0 && rightUpperArmRotateStateZ == 0)
		{
			danceState = 0;
			rotateHead = rotateBodyY = leftUpperArmRotateAngleX = leftUpperArmRotateAngleZ = leftLowerArmRotateAngle = rightUpperArmRotateAngleX = rightUpperArmRotateAngleZ = rightLowerArmRotateAngle = rotateUpperLegAngle = rotateLowerLegAngle = 0;
			rotateHeadState = rotateBodyYState = leftLowerArmRotateState = leftUpperArmRotateStateX = leftUpperArmRotateStateZ = rightLowerArmRotateState = rightUpperArmRotateStateZ = upperLegRotateState = lowerLegRotateState = 1;
			rightUpperArmRotateStateX = -1;
			isDancing = false;
		}
		break;
	default:
		break;
	}
	rotateHead += (float)(rotateHeadState * LSPEED * 10 * dt);
	rotateBodyY += (float)(rotateBodyYState * LSPEED * 10 * dt);
	leftLowerArmRotateAngle += (float)(leftLowerArmRotateState * LSPEED * 10 * dt);
	leftUpperArmRotateAngleX += (float)(leftUpperArmRotateStateX * LSPEED * 10 * dt);
	if (danceState == 3 || danceState == 6 || danceState == 0)
		leftUpperArmRotateAngleZ += (float)(leftUpperArmRotateStateZ * LSPEED * 10 * dt);
	rightLowerArmRotateAngle += (float)(rightLowerArmRotateState * LSPEED * 10 * dt);
	rightUpperArmRotateAngleX += (float)(rightUpperArmRotateStateX * LSPEED * 10 * dt);
	rightUpperArmRotateAngleZ += (float)(rightUpperArmRotateStateZ * LSPEED * 10 * dt);
	rotateUpperLegAngle += (float)(upperLegRotateState * LSPEED * 10 * dt);
	rotateLowerLegAngle += (float)(lowerLegRotateState * LSPEED * 15 * dt);

	isAttacking = false;
	isWalking = false;
}

void SceneAssignment1::reset(void)
{
	rotateHead = rotateBodyX = rotateBodyY = leftUpperArmRotateAngleZ = leftUpperArmRotateAngleX = leftLowerArmRotateAngle = rightUpperArmRotateAngleZ = rightUpperArmRotateAngleX = rightLowerArmRotateAngle = rotateUpperLegAngle = rotateLowerLegAngle = swordRotateAngleX = swordRotateAngleY = swordRotateAngleZ = 0;

	rotateHeadState = translateBodyYState = translateBodyZState = rotateBodyXState = rotateBodyYState = leftUpperArmRotateStateZ = leftUpperArmRotateStateX = leftLowerArmRotateState = rightUpperArmRotateStateZ = rightLowerArmRotateState = upperLegRotateState = lowerLegRotateState = swordRotateStateX = swordRotateStateY = swordRotateStateZ = 1.0;
	rightUpperArmRotateStateX = -1.0;
}

void SceneAssignment1::renderFloor()
{
	//floor
	modelStack.PushMatrix();
	modelStack.Translate(0, -3.6, 0);
	modelStack.Scale(100, 100, 100);
	modelStack.Rotate(-90, 1, 0, 0);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

	for (int i = -5.0; i < 5.0; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(5, -2.5, i * 10);
		RenderMesh(meshList[GEO_WHITE_CONE], true);
		modelStack.PushMatrix();
		modelStack.Translate(0, 1, 0);
		modelStack.Scale(2, 2, 2);
		RenderMesh(meshList[GEO_BLACK_HEMISPHERE], true);
		modelStack.PopMatrix();
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-5, -2.5, i * 10);
		RenderMesh(meshList[GEO_WHITE_CONE], true);
		modelStack.PushMatrix();
		modelStack.Translate(0, 1, 0);
		modelStack.Scale(2, 2, 2);
		RenderMesh(meshList[GEO_BLACK_HEMISPHERE], true);
		modelStack.PopMatrix();
		modelStack.PopMatrix();
	}
}

void SceneAssignment1::renderMorgana()
{
	//body
	modelStack.PushMatrix(); //1
	modelStack.Translate(translateBodyX, translateBodyY, translateBodyZ);
	modelStack.Rotate(rotateBodyY, 0, 1, 0);
	modelStack.Rotate(rotateBodyX, 1, 0, 0);
	modelStack.Scale(1.2, 1.2, 1.2);
	RenderMesh(meshList[GEO_BLACK_SHAVED_CONE], true);

	renderHead();
	renderScarf();

	renderLeftArm();
	renderRightArm();

	renderBelt();

	renderLeftLeg();
	renderRightLeg();

	renderTail();

	modelStack.PopMatrix(); //-1
}

void SceneAssignment1::renderHead(void)
{
	//head
	modelStack.PushMatrix(); //1
	modelStack.Translate(0, 2, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(rotateHead, 0, 0, 1);
	modelStack.Scale(1.2, 1.2, 1.2);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(0.8, 0.8, 0.8);
	//left ear
	modelStack.PushMatrix(); //2
	modelStack.Translate(-1.6, 1.8, 0);
	modelStack.Rotate(45, 0, 0, 1);
	modelStack.Scale(0.6, 0.6, 0.6);
	RenderMesh(meshList[GEO_BLACK_CONE], true);
	modelStack.PopMatrix(); //-1

	modelStack.PushMatrix(); //1
	modelStack.Translate(-1.6, 1.8, 0.1);
	modelStack.Rotate(45, 0, 0, 1);
	modelStack.Scale(0.4, 0.4, 0.4);
	RenderMesh(meshList[GEO_WHITE_CONE], true);
	modelStack.PopMatrix(); //-1

	//right ear
	modelStack.PushMatrix(); //1
	modelStack.Translate(1.6, 1.8, 0);
	modelStack.Rotate(-45, 0, 0, 1);
	modelStack.Scale(0.6, 0.6, 0.6);
	RenderMesh(meshList[GEO_BLACK_CONE], true);
	modelStack.PopMatrix(); //-1

	modelStack.PushMatrix(); //1
	modelStack.Translate(1.6, 1.8, 0.1);
	modelStack.Rotate(-45, 0, 0, 1);
	modelStack.Scale(0.4, 0.4, 0.4);
	RenderMesh(meshList[GEO_WHITE_CONE], true);
	modelStack.PopMatrix(); //-1

	//left eye
	modelStack.PushMatrix(); //1
	modelStack.Translate(-1, 0.75, 1.25);
	modelStack.Rotate(-107.5, 1, 0, 0);
	modelStack.Rotate(-20, 0, 0, 1);
	modelStack.Scale(0.4, 0.4, 0.4);
	RenderMesh(meshList[GEO_EYE], true);
	modelStack.PopMatrix(); //-1

	//right eye
	modelStack.PushMatrix(); //1
	modelStack.Translate(1, 0.75, 1.25);
	modelStack.Rotate(-107.5, 1, 0, 0);
	modelStack.Rotate(20, 0, 0, 1);
	modelStack.Scale(0.4, 0.4, 0.4);
	RenderMesh(meshList[GEO_EYE], true);
	modelStack.PopMatrix(); //-1

	//mouth 
	modelStack.PushMatrix(); //1
	modelStack.Translate(-0.15, -0.5, 0.95);
	modelStack.Rotate(-63, 1, 0, 0);
	modelStack.Rotate(-2, 0, 0, 1);
	modelStack.Scale(0.2, 0.2, 0.2);
	RenderMesh(meshList[GEO_BLACK_CONE], true);
	modelStack.PopMatrix(); //-1

	modelStack.PushMatrix(); //1
	modelStack.Translate(0.15, -0.5, 0.95);
	modelStack.Rotate(-63, 1, 0, 0);
	modelStack.Rotate(2, 0, 0, 1);
	modelStack.Scale(0.2, 0.2, 0.2);
	RenderMesh(meshList[GEO_BLACK_CONE], true);
	modelStack.PopMatrix(); //-1
	modelStack.PopMatrix();
}

void SceneAssignment1::renderScarf(void)
{
	modelStack.PushMatrix(); //1
	modelStack.Translate(0, 0.9, 0);
	modelStack.Scale(0.4, 0.4, 0.4);
	RenderMesh(meshList[GEO_TORUS], true);

	modelStack.PushMatrix(); //2
	modelStack.Translate(0, 0, -1.2);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(0.15, 0.15, 0.15);
	RenderMesh(meshList[GEO_TORUS], true);
	modelStack.PopMatrix(); //-2

	modelStack.PushMatrix(); //2
	modelStack.Translate(0.8, -0.35, -1.2);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Rotate(-20, 0, 1, 0);
	RenderMesh(meshList[GEO_OVAL_SPHERE], true);
	modelStack.PopMatrix(); //-2

	modelStack.PushMatrix(); //2
	modelStack.Translate(0.6, -0.5, -1.5);
	modelStack.Rotate(120, 0, 1, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Rotate(-40, 0, 1, 0);
	RenderMesh(meshList[GEO_OVAL_SPHERE], true);
	modelStack.PopMatrix(); //-2

	modelStack.PopMatrix(); //-1
}

void SceneAssignment1::renderLeftArm(void)
{
	//left arm
	modelStack.PushMatrix();
	modelStack.Translate(-0.4, 0.3, 0);
	modelStack.Rotate(-45 + leftUpperArmRotateAngleZ, 0, 0, 1);
	modelStack.Rotate(leftUpperArmRotateAngleX, 1, 0, 0);
	modelStack.Scale(0.2, 0.2, 0.2);
	RenderMesh(meshList[GEO_BLACK_CYLINDER], true);
	modelStack.PushMatrix();
	modelStack.Translate(0, -2.5, 0);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PushMatrix();
	modelStack.Rotate(leftLowerArmRotateAngle, 1, 0, 0);
	modelStack.Translate(0, -2.5, 0);
	RenderMesh(meshList[GEO_BLACK_CYLINDER], true);
	modelStack.PushMatrix();
	modelStack.Translate(0, -4, 0);
	modelStack.Rotate(180, 0, 0, 1);
	RenderMesh(meshList[GEO_WHITE_CYLINDER_HEMISPHERE], true);
	if (isDancing == false)
		renderSword();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void SceneAssignment1::renderRightArm(void)
{
	//right arm
	modelStack.PushMatrix();
	modelStack.Translate(0.4, 0.3, 0);
	modelStack.Rotate(45 + rightUpperArmRotateAngleZ, 0, 0, 1);
	modelStack.Rotate(rightUpperArmRotateAngleX, 1, 0, 0);
	modelStack.Scale(0.2, 0.2, 0.2);
	RenderMesh(meshList[GEO_BLACK_CYLINDER], true);
	modelStack.PushMatrix();
	modelStack.Translate(0, -2.5, 0);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PushMatrix();
	modelStack.Rotate(rightLowerArmRotateAngle, 1, 0, 0);
	modelStack.Translate(0, -2.5, 0);
	RenderMesh(meshList[GEO_BLACK_CYLINDER], true);
	modelStack.PushMatrix();
	modelStack.Translate(0, -4, 0);
	modelStack.Rotate(180, 0, 0, 1);
	RenderMesh(meshList[GEO_WHITE_CYLINDER_HEMISPHERE], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void SceneAssignment1::renderBelt(void)
{
	//belt
	modelStack.PushMatrix();
	modelStack.Translate(0, -1.2, 0);
	RenderMesh(meshList[GEO_BELT_CYLINDER], true);
	modelStack.PushMatrix();
	modelStack.Translate(-0.4, 0, 0.93);
	modelStack.Rotate(65, 0, 1, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(0.2, 0.2, 0.2);
	RenderMesh(meshList[GEO_OVAL_SPHERE], true);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(0.4, 0, 0.93);
	modelStack.Rotate(-65, 0, 1, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(0.2, 0.2, 0.2);
	RenderMesh(meshList[GEO_OVAL_SPHERE], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void SceneAssignment1::renderLeftLeg(void)
{
	//left leg
	modelStack.PushMatrix();
	modelStack.Translate(-0.4, -1.8, 0);
	modelStack.Rotate(180 - rotateUpperLegAngle, 1, 0, 0);
	modelStack.Scale(0.6, 0.6, 0.6);
	RenderMesh(meshList[GEO_BLACK_SHAVED_CONE], true);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.9, 0);
	modelStack.Scale(0.3, 0.3, 0.3);
	RenderMesh(meshList[GEO_SPHERE], true);

	modelStack.PushMatrix();
	modelStack.Scale(3.3, 3.3, 3.3);
	if (rotateUpperLegAngle >= 0)
		modelStack.Rotate(rotateLowerLegAngle, 1, 0, 0);
	modelStack.Translate(0, 0.6, 0);
	RenderMesh(meshList[GEO_WHITE_SHAVED_CONE], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void SceneAssignment1::renderRightLeg(void)
{
	//right leg
	modelStack.PushMatrix();
	modelStack.Translate(0.4, -1.8, 0);
	modelStack.Rotate(180 + rotateUpperLegAngle, 1, 0, 0);
	modelStack.Scale(0.6, 0.6, 0.6);
	RenderMesh(meshList[GEO_BLACK_SHAVED_CONE], true);

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.9, 0);
	modelStack.Scale(0.3, 0.3, 0.3);
	RenderMesh(meshList[GEO_SPHERE], true);

	modelStack.PushMatrix();
	modelStack.Scale(3.3, 3.3, 3.3);
	if (-rotateUpperLegAngle >= 0)
		modelStack.Rotate(-rotateLowerLegAngle, 1, 0, 0);
	modelStack.Translate(0, 0.6, 0);
	RenderMesh(meshList[GEO_WHITE_SHAVED_CONE], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void SceneAssignment1::renderTail(void)
{
	//tail
	modelStack.PushMatrix();
	modelStack.Translate(0, -1, -1);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(0.2, 0.2, 0.2);
	RenderMesh(meshList[GEO_BLACK_CYLINDER], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -1.5);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_QUARTER_TORUS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -3.5);
	modelStack.Rotate(90, 0, 0, 1);
	RenderMesh(meshList[GEO_QUARTER_TORUS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 1, -3.8);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(0.2, 0.2, 0.2);
	RenderMesh(meshList[GEO_WHITE_CYLINDER_HEMISPHERE], true);
	modelStack.PopMatrix();
}

void SceneAssignment1::renderSword(void)
{
	modelStack.PushMatrix(); //1
	modelStack.Translate(0, 0.5, 0);
	modelStack.Rotate(swordRotateAngleX, 1, 0, 0);
	modelStack.Rotate(swordRotateAngleY, 0, 1, 0);
	modelStack.Rotate(-90 + swordRotateAngleZ, 0, 0, 1);
	modelStack.Scale(0.9, 0.9, 0.9);
	RenderMesh(meshList[GEO_BLACK_CYLINDER], true);
	renderHilt();
	renderBlade();
	modelStack.PopMatrix();
}

void SceneAssignment1::renderHilt(void)
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 2.5, 0);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_BLACK_HEMISPHERE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 1, 1);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_QUARTER_TORUS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.3, 3);
	modelStack.Scale(0.38, 0.38, 0.38);
	RenderMesh(meshList[GEO_BLACK_CYLINDER], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -0.5, 1);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_QUARTER_TORUS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -2.5, 0);
	modelStack.Scale(1.1, 1.1, 1.1);
	RenderMesh(meshList[GEO_BELT_CYLINDER], true);
	modelStack.PopMatrix();
}

void SceneAssignment1::renderBlade(void)
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 8, 0);
	RenderMesh(meshList[GEO_BLADE], true);
	modelStack.PopMatrix();
}

void SceneAssignment1::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight && lightOn)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	mesh->Render();
}