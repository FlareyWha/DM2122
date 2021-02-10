#include "SceneAssignment2.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "Vertex.h"
#include "Utility.h"
#include "shader.hpp"
#include "LoadTGA.h"
#include "MyMath.h"

SceneAssignment2::SceneAssignment2()
{
}

SceneAssignment2::~SceneAssignment2()
{
}

void SceneAssignment2::Init()
{
	// Init VBO here
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	assignParametersForLights();
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	glUseProgram(m_programID);

	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT], m_parameters[U_MATERIAL_DIFFUSE], m_parameters[U_MATERIAL_SPECULAR], m_parameters[U_MATERIAL_SHININESS]);

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	initLights();

	// Generate a default VBO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	//text
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1,1,1), 1.0f);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//color.tga");

	meshList[GEO_BLACK_QUAD] = MeshBuilder::GenerateQuad("blackQuad", Color(0, 0, 0), 1.0f);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 36, 36, 1.0f);
	meshList[GEO_LIGHTBALL_2] = MeshBuilder::GenerateSphere("lightball2", Color(1, 1, 1), 36, 36, 1.0f);
	meshList[GEO_LIGHTBALL_3] = MeshBuilder::GenerateSphere("lightball3", Color(1, 1, 1), 36, 36, 1.0f);
	meshList[GEO_LIGHTBALL_4] = MeshBuilder::GenerateSphere("lightball4", Color(1, 1, 1), 36, 36, 1.0f);

	initMorgana();
	initScene();
	initCastle();
	initRoom();

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);

	rotateAngle = 1;
	translateX = 1;
	scaleAll = 1;
	csvFile.loadCSV();
	camera.Init(Vector3(0, 0, 50), Vector3(0, 0, 0), Vector3(0, 1, 0));
}

void SceneAssignment2::assignParametersForLights()
{
	//light 0
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	//light 1
	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	//light 2
	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");

	//light 2
	m_parameters[U_LIGHT3_POSITION] = glGetUniformLocation(m_programID, "lights[3].position_cameraspace");
	m_parameters[U_LIGHT3_COLOR] = glGetUniformLocation(m_programID, "lights[3].color");
	m_parameters[U_LIGHT3_POWER] = glGetUniformLocation(m_programID, "lights[3].power");
	m_parameters[U_LIGHT3_KC] = glGetUniformLocation(m_programID, "lights[3].kC");
	m_parameters[U_LIGHT3_KL] = glGetUniformLocation(m_programID, "lights[3].kL");
	m_parameters[U_LIGHT3_KQ] = glGetUniformLocation(m_programID, "lights[3].kQ");
	m_parameters[U_LIGHT3_TYPE] = glGetUniformLocation(m_programID, "lights[3].type");
	m_parameters[U_LIGHT3_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[3].spotDirection");
	m_parameters[U_LIGHT3_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[3].cosCutoff");
	m_parameters[U_LIGHT3_COSINNER] = glGetUniformLocation(m_programID, "lights[3].cosInner");
	m_parameters[U_LIGHT3_EXPONENT] = glGetUniformLocation(m_programID, "lights[3].exponent");

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
}

void SceneAssignment2::initLights()
{
	//light 0
	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(0, 100, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 15;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	//light 1
	light[1].type = Light::LIGHT_POINT;
	light[1].position.Set(0, 100, -675);
	light[1].color.Set(1, 1, 1);
	light[1].power = 30;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);

	//light 2
	light[2].type = Light::LIGHT_POINT;
	light[2].position.Set(0, 100, -935);
	light[2].color.Set(1, 1, 1);
	light[2].power = 30;
	light[2].kC = 1.f;
	light[2].kL = 0.01f;
	light[2].kQ = 0.001f;
	light[2].cosCutoff = cos(Math::DegreeToRadian(45));
	light[2].cosInner = cos(Math::DegreeToRadian(30));
	light[2].exponent = 3.f;
	light[2].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_LIGHT2_TYPE], light[2].type);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1, &light[2].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], light[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], light[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], light[2].kQ);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], light[2].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], light[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], light[2].exponent);

	//light 3
	light[3].type = Light::LIGHT_SPOT;
	light[3].position.Set(-4, 35, -1105);
	light[3].color.Set(1, 1, 1);
	light[3].power = 5;
	light[3].kC = 1.f;
	light[3].kL = 0.01f;
	light[3].kQ = 0.001f;
	light[3].cosCutoff = cos(Math::DegreeToRadian(45));
	light[3].cosInner = cos(Math::DegreeToRadian(30));
	light[3].exponent = 3.f;
	light[3].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_LIGHT3_TYPE], light[3].type);
	glUniform3fv(m_parameters[U_LIGHT3_COLOR], 1, &light[3].color.r);
	glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
	glUniform1f(m_parameters[U_LIGHT3_KC], light[3].kC);
	glUniform1f(m_parameters[U_LIGHT3_KL], light[3].kL);
	glUniform1f(m_parameters[U_LIGHT3_KQ], light[3].kQ);
	glUniform1f(m_parameters[U_LIGHT3_COSCUTOFF], light[3].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT3_COSINNER], light[3].cosInner);
	glUniform1f(m_parameters[U_LIGHT3_EXPONENT], light[3].exponent);

	glUniform1i(m_parameters[U_NUMLIGHTS], 4); //Max of 8 lights. rmb to change Light light[] when adding more
}

void SceneAssignment2::initMorgana()
{
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

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 1, 1), 36, 36, 1.0f);
	meshList[GEO_SPHERE]->material.kAmbient.Set(0.0f, 0.0f, 0.0f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE]->material.kShininess = 1.f;

	rotateHead = 0;
	rotateHeadState = 1;
	translateBodyX = 0;
	translateBodyXState = 1;
	translateBodyY = 0;
	translateBodyYState = 1;
	translateBodyZ = 0;
	translateBodyZState = 1;
	translateBodyZExtra = 0;
	translateBodyZExtraState = 1;
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
	swordRotateStateY = 1;
	swordRotateAngleZ = 0;
	swordRotateStateZ = 1;
	isWalking = false;
	isAttacking = false;
	attackingPhase = 0;
	isDancing = false;
	danceState = 0;
	timer = 0;
}

void SceneAssignment2::initScene()
{
	gameState = 1;
	subGameState = 1;
	doorRotateAngle = 0;
	doorOpen = false;
	pickUpKey = false;
	pickUpCrown = false;
	showDebugInfo = true;
	fakeFrontScale = 50;
	textTimer = -1;

	enemy[0].init(Vector3(50, 0, -560), 0, 0, '0', 90, 1);
	enemy[1].init(Vector3(0, 0, -620), 50, -50, 'x', 90, 1);
	enemy[2].init(Vector3(0, 0, -640), 50, -50, 'x', -90, -1);
	enemy[3].init(Vector3(-30, 0, -770), 50, -50, 'x', 90, 1);
	enemy[4].init(Vector3(100, 0, -750), 10, -10, 'z', 0, 1);
	enemy[5].init(Vector3(-135, 0, -880), 24, -24, 'z', 0, 1);
	enemy[6].init(Vector3(50, 0, -890), 70, -70, 'x', 90, 1);
	enemy[7].init(Vector3(50, 0, -910), 70, -70, 'x', 90, 1);
	enemy[8].init(Vector3(50, 0, -930), 70, -70, 'x', 90, 1);
}

void SceneAssignment2::initCastle()
{
	meshList[GEO_DOOR] = MeshBuilder::GenerateOBJMTL("door", "OBJ//Assignment2//gate.obj", "OBJ//Assignment2//gate.mtl");
	meshList[GEO_WALLDOOR] = MeshBuilder::GenerateOBJMTL("walldoor", "OBJ//Assignment2//wallNarrowGate.obj", "OBJ//Assignment2//wallNarrowGate.mtl");
	meshList[GEO_WALL] = MeshBuilder::GenerateOBJMTL("wall", "OBJ//Assignment2//wall.obj", "OBJ//Assignment2//wall.mtl");
	meshList[GEO_WALLCORNERHALF] = MeshBuilder::GenerateOBJMTL("wallCornerHalf", "OBJ//Assignment2//wallCornerHalf.obj", "OBJ//Assignment2//wallCornerHalf.mtl");
	meshList[GEO_WALLCORNERHALFTOWER] = MeshBuilder::GenerateOBJMTL("wallCornerHalfTower", "OBJ//Assignment2//wallCornerHalfTower.obj", "OBJ//Assignment2//wallCornerHalfTower.mtl");
	meshList[GEO_TOWERSQUAREBASE] = MeshBuilder::GenerateOBJMTL("wallSquareBase", "OBJ//Assignment2//towerSquareBase.obj", "OBJ//Assignment2//towerSquareBase.mtl");
	meshList[GEO_TOWERSQUAREARCH] = MeshBuilder::GenerateOBJMTL("wallSquareArch", "OBJ//Assignment2//towerSquareArch.obj", "OBJ//Assignment2//towerSquareArch.mtl");
	meshList[GEO_TOWERSQUAREMID] = MeshBuilder::GenerateOBJMTL("wallSquareMid", "OBJ//Assignment2//towerSquareMid.obj", "OBJ//Assignment2//towerSquareMid.mtl");
	meshList[GEO_TOWERSQUARETOPROOF] = MeshBuilder::GenerateOBJMTL("wallSquareTopRoof", "OBJ//Assignment2//towerSquareTopRoof.obj", "OBJ//Assignment2//towerSquareTopRoof.mtl");
	meshList[GEO_BARREL] = MeshBuilder::GenerateOBJMTL("barrel", "OBJ//Assignment2//barrel.obj", "OBJ//Assignment2//barrel.mtl");
	meshList[GEO_FLOOR] = MeshBuilder::GenerateQuad("floor", Color(1, 1, 1), 1.0f);
	meshList[GEO_FLOOR]->textureID = LoadTGA("Image//Assignment2//floor.tga");

	//skybox stuff
	meshList[GEO_SUNSETFRONT] = MeshBuilder::GenerateQuad("sunsetfront", Color(1, 1, 1), 1.f);
	meshList[GEO_SUNSETFRONT]->textureID = LoadTGA("Image//Assignment2//sunsetfront.tga");
	meshList[GEO_SUNSETBACK] = MeshBuilder::GenerateQuad("sunsetback", Color(1, 1, 1), 1.f);
	meshList[GEO_SUNSETBACK]->textureID = LoadTGA("Image//Assignment2//sunsetback.tga");
	meshList[GEO_SUNSETLEFT] = MeshBuilder::GenerateQuad("sunsetleft", Color(1, 1, 1), 1.f);
	meshList[GEO_SUNSETLEFT]->textureID = LoadTGA("Image//Assignment2//sunsetleft.tga");
	meshList[GEO_SUNSETRIGHT] = MeshBuilder::GenerateQuad("sunsetright", Color(1, 1, 1), 1.f);
	meshList[GEO_SUNSETRIGHT]->textureID = LoadTGA("Image//Assignment2//sunsetright.tga");
	meshList[GEO_SUNSETTOP] = MeshBuilder::GenerateQuad("sunsettop", Color(1, 1, 1), 1.f);
	meshList[GEO_SUNSETTOP]->textureID = LoadTGA("Image//Assignment2//sunsetup.tga");
	meshList[GEO_SUNSETBOTTOM] = MeshBuilder::GenerateQuad("sunsetbottom", Color(1, 1, 1), 1.f);
	meshList[GEO_SUNSETBOTTOM]->textureID = LoadTGA("Image//Assignment2//sunsetdown.tga");
}

void SceneAssignment2::initRoom()
{
	meshList[GEO_CRATE] = MeshBuilder::GenerateOBJMTL("crate", "OBJ//Assignment2//crate.obj", "OBJ//Assignment2//crate.mtl");
	meshList[GEO_ENEMY] = MeshBuilder::GenerateOBJMTL("enemy", "OBJ//Assignment2//craft_miner.obj", "OBJ//Assignment2//craft_miner.mtl");
	meshList[GEO_REDQUAD] = MeshBuilder::GenerateQuad("redQuad", Color(1, 1, 1), 1.f);
	meshList[GEO_REDQUAD]->material.kAmbient.Set(0.9f, 0.0f, 0.0f);
	meshList[GEO_REDQUAD]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_REDQUAD]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_REDQUAD]->material.kShininess = 1.f;
	meshList[GEO_KEY] = MeshBuilder::GenerateOBJMTL("key", "OBJ//Assignment2//key.obj", "OBJ//Assignment2//key.mtl");
	meshList[GEO_KEY]->textureID = LoadTGA("Image//Assignment2//key.tga");
	meshList[GEO_CROWN] = MeshBuilder::GenerateOBJMTL("crown", "OBJ//Assignment2//crown.obj", "OBJ//Assignment2//crown.mtl");
}

void SceneAssignment2::Update(double dt)
{
	static const float LSPEED = 10.0f;
	//change so each one is not synced
	camera.Update(dt, gameState);
	avgFPS = 1 / dt;
	for (int i = 0; i < 9; ++i)
		enemy[i].update(dt);
	if (textTimer >= 0)
		textTimer += dt;

	collisionWithEnemy();

	if (Application::IsKeyPressed('1')) //0x31
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //0x32
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3')) //0x33
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (Application::IsKeyPressed('4')) //0x34
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (Application::IsKeyPressed('5'))
	{
		light[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('6'))
	{
		light[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	else if (Application::IsKeyPressed('7'))
	{
		light[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	if (Application::IsKeyPressed('9'))
		lightOn = false;
	if (Application::IsKeyPressed('0'))
		lightOn = true;
	if (Application::IsKeyPressed('Z'))
		axesOn = false;
	if (Application::IsKeyPressed('X'))
		axesOn = true;
	if (Application::IsKeyPressed(VK_F3))
		showDebugInfo = true;
	else if (Application::IsKeyPressed(VK_F4))
		showDebugInfo = false;
	if (Application::IsKeyPressed(VK_F5)) //DELETE LTR
	{
		translateBodyXState = 0;
		translateBodyZState = 0;
		translateBodyX = -140;
		translateBodyZ = -585;
		camera.position.Set(-142, 0, -560);
		rotateBodyY = 90;
		translateBodyXState = 1;
		isWalking = true;
		gameState = 3;
	}
	if (Application::IsKeyPressed(VK_F6))
	{
		std::cout << "X: " << camera.position.x << ", " << "Z: " << camera.position.z << std::endl;
	}

	if (Application::IsKeyPressed('I'))
	{
		light[3].position.z -= (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('K'))
	{
		light[3].position.z += (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('J'))
	{
		light[3].position.x -= (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('L'))
	{
		light[3].position.x += (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('O'))
	{
		light[3].position.y -= (float)(LSPEED * dt);
	}
	if (Application::IsKeyPressed('P'))
	{
		light[3].position.y += (float)(LSPEED * dt);
	}

	/*if (Application::IsKeyPressed('R'))
	{
		reset();
		translateBodyX = translateBodyY = translateBodyZ = 0;
		isWalking = false;
		isAttacking = false;
		isDancing = false;
		attackingPhase = 0;
		timer = 0;
		light[0].position.Set(0, 20, 0);
		camera.Reset(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	}*/

	//if (Application::IsKeyPressed(VK_SPACE)) //attack
	//{
	//	reset();
	//	isAttacking = true;
	//	rotateBodyXState = 0;
	//	attackingPhase = 1;
	//	translateBodyZExtraState = -1;
	//	leftUpperArmRotateStateZ = -1;
	//	swordRotateStateX = 0;
	//	swordRotateStateY = 1;
	//	leftLowerArmRotateState = 0;
	//}

	//if (Application::IsKeyPressed('G')) //dancing
	//{
	//	reset();
	//	isDancing = true;
	//	danceState = 1;
	//	rotateHeadState = 0;
	//	rotateBodyYState = 1;
	//	leftUpperArmRotateStateX = 1;
	//	leftLowerArmRotateState = -1;
	//	rightUpperArmRotateStateX = -1;
	//	rightUpperArmRotateStateZ = 1;
	//	rightLowerArmRotateState = -1;
	//	upperLegRotateState = -1;
	//	lowerLegRotateState = -1;
	//}

	if (isWalking == true)
		walking(LSPEED, dt);

	if (isAttacking == true)
		attacking(LSPEED, dt);

	if (isDancing == true)
		dancing(LSPEED, dt);

	gameStateManager(dt);
}

void SceneAssignment2::Render()
{
	// Render VBO here
	// set background colour to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Clear color buffer for every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	renderLights();

	Mtx44 mvp;

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]);
	//RenderMesh(meshList[GEO_AXES], false);

	renderMorgana();

	//skybox
	if (gameState < 3)
		RenderSkybox();
	renderCastle();
	renderFloor();
	if (gameState > 2)
		renderRoom();
	if (gameState == 99)
		RenderMeshOnScreen(meshList[GEO_BLACK_QUAD], 40, 30, 80, 60);
	if (pickUpKey)
		RenderMeshOnScreen(meshList[GEO_KEY], 70, 5, 2, 1);
	renderGameText();
	renderDebug();

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL_2], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[2].position.x, light[2].position.y, light[2].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL_3], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[3].position.x, light[3].position.y, light[3].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL_4], false);
	modelStack.PopMatrix();
}

void SceneAssignment2::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SceneAssignment2::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
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
	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if (mesh->textureID > 0)
		glBindTexture(GL_TEXTURE_2D, 0);
}

void SceneAssignment2::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;
	//glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

	float accelerator = 0.f;

	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(accelerator, 0, i * 0.001); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
		accelerator += csvFile.getWidth(text[i]) / 64.0f;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	//glEnable(GL_DEPTH_TEST);
}

void SceneAssignment2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	float accelerator = 0.f;
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(0.5f + accelerator, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
		accelerator += csvFile.getWidth(text[i]) / 64.0f;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void SceneAssignment2::RenderMeshOnScreen(Mesh* mesh, int x, int y, int sizex, int sizey)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	//to do: scale and translate accordingly
	modelStack.Translate(x, y, 0);
	modelStack.Scale(sizex, sizey, 0);
	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void SceneAssignment2::renderLights()
{
	Position lightPosition_cameraspace0 = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace0.x);

	Position lightDirection_cameraspace1 = viewStack.Top() * light[1].position;
	glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace1.x);

	Position lightDirection_cameraspace2 = viewStack.Top() * light[2].position;
	glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightDirection_cameraspace2.x);

	Position lightPosition_cameraspace3 = viewStack.Top() * light[3].position;
	glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace3.x);
	Vector3 spotDirection_cameraspace3 = viewStack.Top() * light[3].spotDirection;
	glUniform3fv(m_parameters[U_LIGHT3_SPOTDIRECTION], 1, &spotDirection_cameraspace3.x);

	//copy from here if need and make sure to change to the correct light and the middle of function thing also need change maybe its very weird for now not changing works but tbh idk
	/*if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}*/
}

void SceneAssignment2::renderGameText() //render text
{
	switch (gameState)
	{
	case 1:
		RenderTextOnScreen(meshList[GEO_TEXT], "Morgana: Its time to take the treasure!" , Color(0, 1, 0), 4, 0, 3);
		RenderTextOnScreen(meshList[GEO_TEXT], "Lets head through the door first.", Color(0, 1, 0), 4, 0, 0);
		if (camera.checkPosition(5, -5, 0, 0, -10) == true && doorOpen == false) 
		{
			modelStack.PushMatrix();
			modelStack.Translate(-5, -2, -18);
			RenderText(meshList[GEO_TEXT], "Press E to open door", Color(0, 0, 0));
			modelStack.PopMatrix();
		}
		break;
	case 2:
		RenderTextOnScreen(meshList[GEO_TEXT], "Morgana: The infiltration point is right ahead.", Color(0, 1, 0), 4, 0, 3);
		RenderTextOnScreen(meshList[GEO_TEXT], "Its under that arch. Lets go!", Color(0, 1, 0), 4, 0, 0);
		if (camera.checkPosition(5, -5, 0, -162, -168) == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-3, -1, -175);
			RenderText(meshList[GEO_TEXT], "Press E to enter", Color(0, 0, 0));
			modelStack.PopMatrix();
		}
		break;
	case 3:
		if (subGameState > 0 && subGameState < 3)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Morgana: Theres an enemies right in front of us.", Color(0, 1, 0), 4, 0, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], "We should avoid fighting them.", Color(0, 1, 0), 4, 0, 3);
			RenderTextOnScreen(meshList[GEO_TEXT], "Follow me, and dont get spotted.", Color(0, 1, 0), 4, 0, 0);
		}
		break;
	case 4:
		if (textTimer >= 0)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Morgana: There are more enemies ahead. I think", Color(0, 1, 0), 4, 0, 6);
			RenderTextOnScreen(meshList[GEO_TEXT], "we should split up. Ill scout ahead. See you", Color(0, 1, 0), 4, 0, 3);
			RenderTextOnScreen(meshList[GEO_TEXT], "later. Good luck!", Color(0, 1, 0), 4, 0, 0);
		}
		if (camera.checkPosition(100, 90, 0, -830, -840) == true && pickUpKey == false)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "A key? I wonder what its for.", Color(0, 1, 0), 4, 0, 0);
			modelStack.PushMatrix();
			modelStack.Translate(120, 0, -845);
			modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Scale(4, 4, 4);
			RenderText(meshList[GEO_TEXT], "Press E to pick up key", Color(0, 0, 0));
			modelStack.PopMatrix();
		}
		break;
	case 5:
		if (textTimer >= 0)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Morgana: Its a dead end. This is weird.", Color(0, 1, 0), 4, 0, 3);
			RenderTextOnScreen(meshList[GEO_TEXT], "Maybe there's something behind this wall?", Color(0, 1, 0), 4, 0, 0);
		}
		break;
	case 6:
		if (subGameState == 1)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Morgana: That didnt work.", Color(0, 1, 0), 4, 0, 3);
			RenderTextOnScreen(meshList[GEO_TEXT], "There must be something here.", Color(0, 1, 0), 4, 0, 0);
		}
		if (camera.checkPosition(-80, -90, 0, -980, -1000) == true && subGameState == 2)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Morgana: A pedestal?", Color(0, 1, 0), 4, 0, 3);
			RenderTextOnScreen(meshList[GEO_TEXT], "Wonder what its for...", Color(0, 1, 0), 4, 0, 0);
		}
		if (camera.checkPosition(100, 90, 0, -830, -840) == true && pickUpKey == false)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "A key? I wonder what its for.", Color(0, 1, 0), 4, 0, 0);
			modelStack.PushMatrix();
			modelStack.Translate(120, 0, -845);
			modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Scale(4, 4, 4);
			RenderText(meshList[GEO_TEXT], "Press E to pick up key", Color(0, 0, 0));
			modelStack.PopMatrix();
		}
		if (subGameState == 3 && pickUpKey == true && textTimer == -1)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Morgana: Oh u have a key?", Color(0, 1, 0), 4, 0, 3);
			RenderTextOnScreen(meshList[GEO_TEXT], "Maybe try putting it on that pedestal?", Color(0, 1, 0), 4, 0, 0);
		}
		if (camera.checkPosition(-70, -90, 0, -980, -1000) == true && subGameState == 3 && pickUpKey == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-120, 0, -970);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(4, 4, 4);
			RenderText(meshList[GEO_TEXT], "Press E to place key", Color(0, 0, 0));
			modelStack.PopMatrix();
    	}
		break;
	case 7:
		RenderTextOnScreen(meshList[GEO_TEXT], "Morgana: The wall disappeared! And the treasure", Color(0, 1, 0), 4, 0, 3);
		RenderTextOnScreen(meshList[GEO_TEXT], "is right there! Lets grab it and go. I'll wait by the exit.", Color(0, 1, 0), 4, 0, 0);
		break;
	case 99:
		RenderTextOnScreen(meshList[GEO_TEXT], "You Lose", Color(0, 1, 0), 20, 13, 25);
		break;
	}
}
void SceneAssignment2::gameStateManager(double dt) //stuff like where morgana will go etc
{
	switch (gameState)
	{
	case 1:
		translateBodyX = -10;
		translateBodyZ = -15;
		if (doorOpen == true)
			doorRotateAngle += (float)(1 * 50 * dt);
		if (doorRotateAngle >= 90)
		{
			doorOpen = false;
			isWalking = true;
			rotateBodyY = 90;
			translateBodyZState = 0;
			gameState = 2;
		}
		if (Application::IsKeyPressed('E') && camera.checkPosition(5, -5, 0, 0, -10)) //open door at start
			doorOpen = true;
		break;
	case 2:
		if (translateBodyX >= 0)
		{
			rotateBodyY = 180;
			translateBodyXState = 0;
			translateBodyZState = -1;
		}
		if (translateBodyZ <= -165)
		{
			translateBodyXState = 0;
			translateBodyZState = 0;
			translateBodyX = -140;
			translateBodyZ = -585;
			isWalking = false;
		}
		if (Application::IsKeyPressed('E') && camera.checkPosition(5, -5, 0, -162, -168))
		{
			camera.position.Set(-142, 0, -560);
			rotateBodyY = 90;
			translateBodyXState = 1;
			isWalking = true;
			gameState = 3;
		}
		translateBodyX += (float)(translateBodyXState * 25 * dt);
		translateBodyZ += (float)(translateBodyZState * 35 * dt);
		break;
	case 3:
		if (translateBodyX >= 120 && subGameState == 1)
		{
			translateBodyXState = 0;
			translateBodyZState = -1;
			rotateBodyY = 180;
			subGameState = 2;
		}
		if (translateBodyZ <= -630 && subGameState == 2)
		{
			translateBodyZState = 0;
			translateBodyXState = -1;
			rotateBodyY = -90;
			subGameState = 3;
		}
		if (translateBodyX <= -141 && subGameState == 3)
		{
			translateBodyXState = 0;
			translateBodyZState = -1;
			rotateBodyY = 180;
			subGameState = 4;
		}
		if (translateBodyZ <= -680 && subGameState == 4)
		{
			translateBodyZState = 0;
			translateBodyXState = 1;
			rotateBodyY = 90;
			subGameState = 5;
		}
		if (translateBodyX >= 30 && subGameState == 5)
		{
			reset();
			translateBodyZState = 0;
			translateBodyXState = 0;
			rotateBodyY = -90;
			subGameState = 0;
			isWalking = false;
		}
		if (camera.checkPosition(30, -10, 0, -667, -682) == true && subGameState == 0)
		{
			translateBodyZState = 0;
			translateBodyXState = 1;
			rotateBodyY = 90;
			gameState = 4;
			textTimer = 0;
			isWalking = true;
		}
		translateBodyX += (float)(translateBodyXState * 35 * dt);
		translateBodyZ += (float)(translateBodyZState * 25 * dt);
		break;
	case 4:
		if (translateBodyX >= 130)
		{
			translateBodyZState = 0;
			translateBodyXState = 0;
			isWalking = false;
		}
		if (textTimer >= 5)
		{
			textTimer = -1;
			translateBodyX = 0;
			translateBodyZ = -1035;
			rotateBodyYState = -90;
		}
		if (Application::IsKeyPressed('E') && camera.checkPosition(100, 90, 0, -830, -840) == true && pickUpKey == false)
		{
			pickUpKey = true;
		}
		if (camera.checkPosition(80, 0, 0, -953, -1045) == true && subGameState == 0)
		{
			rotateBodyY = 90;
			gameState = 5;
			textTimer = 0;
		}
		translateBodyX += (float)(translateBodyXState * 35 * dt);
		break;
	case 5:
		if (textTimer >= 3)
		{
			reset();
			textTimer = -1;
			isAttacking = true;
			rotateBodyY = 180;
			rotateBodyXState = 0;
			attackingPhase = 1;
			translateBodyZExtraState = -1;
			leftUpperArmRotateStateZ = -1;
			swordRotateStateX = 0;
			swordRotateStateY = 1;
			leftLowerArmRotateState = 0;
		}
		if (textTimer == -1 && isAttacking == false)
		{
			reset();
			rotateBodyY = 180;
			gameState = 6;
			subGameState = 1;
		}
		break;
	case 6:
		if (camera.checkPosition(-70, -90, 0, -980, -1000) == true && subGameState == 1)
		{
			subGameState = 2;
			textTimer = 0;
		}
		if (textTimer >= 3)
		{
			textTimer = -1;
			subGameState = 3;
		}
		if (Application::IsKeyPressed('E') && camera.checkPosition(100, 90, 0, -830, -840) == true && pickUpKey == false)
			pickUpKey = true;
		if (Application::IsKeyPressed('E') && camera.checkPosition(-70, -90, 0, -980, -1000) == true && subGameState == 3 && pickUpKey == true)
		{
			pickUpKey = false;
			gameState = 7;
			subGameState = 1;
			rotateBodyY = 90;
		}
		break;
	case 7:
		if (fakeFrontScale >= 0.1)
			fakeFrontScale += (float)(-1 * 10 * dt);
		if (translateBodyX == -120)
		{
			translateBodyXState = 0;
			translateBodyZState = -1;
			rotateBodyY = 180;
		}
		if (translateBodyZ == -1120)
		{
			translateBodyZState = 0;
			rotateBodyY = 0;
		}
		if (Application::IsKeyPressed('E') && camera.checkPosition(4, -14, 0, -1080, -1090) == true)
		{
			pickUpCrown = false;
			subGameState = 2;
		}
		translateBodyX += (float)(translateBodyXState * 25 * dt);
		translateBodyZ += (float)(translateBodyZState * 25 * dt);
		break;
	}
}

int SceneAssignment2::enemyDirectionCheck(int enemyNumber, Vector3 tempPos)
{
	if (enemy[enemyNumber].getDirection() == 'x' && enemy[enemyNumber].getMoveState() == 1)
		return 1;
	else if (enemy[enemyNumber].getDirection() == 'x' && enemy[enemyNumber].getMoveState() == -1)
		return 2;
	else if (enemy[enemyNumber].getDirection() == 'z' && enemy[enemyNumber].getMoveState() == 1)
		return 3;
	else if (enemy[enemyNumber].getDirection() == 'z' && enemy[enemyNumber].getMoveState() == -1)
		return 4;
	else
		return 0;
}

void SceneAssignment2::collisionWithEnemy()
{
	for (int i = 0; i < 9; ++i)
	{
		Vector3 tempPos = enemy[i].getPosition();
		int directionCheck = enemyDirectionCheck(i, tempPos);
		switch (directionCheck)
		{
		case 1:
			if (camera.checkPosition(tempPos.x + 50, tempPos.x - 10, 0, tempPos.z + 6, tempPos.z - 6) == true)
				gameState = 99;
			break;
		case 2:
			if (camera.checkPosition(tempPos.x + 10, tempPos.x - 50, 0, tempPos.z + 6, tempPos.z - 6) == true)
				gameState = 99;
			break;
		case 3:
			if (camera.checkPosition(tempPos.x + 6, tempPos.x - 6, 0, tempPos.z + 50, tempPos.z - 10) == true)
				gameState = 99;
			break;
		case 4:
			if (camera.checkPosition(tempPos.x + 6, tempPos.x - 6, 0, tempPos.z + 10, tempPos.z - 50) == true)
				gameState = 99;
			break;
		default:
			break;
		}
	}
}

void SceneAssignment2::RenderSkybox()
{
	//normal skybox
	/*modelStack.PushMatrix();
	modelStack.Translate(-500, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_SUNSETFRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(500, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_SUNSETBACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 500);
	modelStack.Rotate(-180, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_SUNSETLEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -500);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_SUNSETRIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 500, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_SUNSETTOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -500, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_SUNSETBOTTOM], false);
	modelStack.PopMatrix();*/

	//translating skybox
	modelStack.PushMatrix();
	modelStack.Translate(-500 + camera.position.x, 0 + camera.position.y, 0 + camera.position.z);
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_SUNSETFRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(500 + camera.position.x, 0 + camera.position.y, 0 + camera.position.z);
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Rotate(-90, 0, 1, 0);
	RenderMesh(meshList[GEO_SUNSETBACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 0 + camera.position.y, 500 + camera.position.z);
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Rotate(-180, 0, 1, 0);
	RenderMesh(meshList[GEO_SUNSETLEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 0 + camera.position.y, -500 + camera.position.z);
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Rotate(0, 0, 1, 0);
	RenderMesh(meshList[GEO_SUNSETRIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, 500 + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(90, 1, 0, 0); //90deg on idk axis yes
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_SUNSETTOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0 + camera.position.x, -500 + camera.position.y, 0 + camera.position.z);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_SUNSETBOTTOM], false);
	modelStack.PopMatrix();
}

void SceneAssignment2::renderFloor()
{
	for (int i = -5; i < 5; ++i)
	{
		for (int j = -7; j < 3; ++j)
		{
			modelStack.PushMatrix();
			modelStack.Translate(i * 50, -15, j * 50);
			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Scale(50, 50, 50);
			RenderMesh(meshList[GEO_FLOOR], true);
			modelStack.PopMatrix();
		}
	}
}

void SceneAssignment2::renderCastle(void)
{
	//outer wall of castle
	for (int i = -6; i < 7; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(15 + i * 30, -15, 150);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_WALL], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(15 + i * 30, -15, -330);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_WALL], true);
		modelStack.PopMatrix();
	}
	
	modelStack.PushMatrix();
	modelStack.Translate(15 - 8 * 30, -15, 150);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_WALLCORNERHALF], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(15 + 7 * 30, -15, 150);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_WALLCORNERHALF], true);
	modelStack.PopMatrix();

	for (int i = 1; i < 16; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(15 + 6 * 30, -15, 150 - i * 30);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_WALL], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(15 - 8 * 30, -15, 150 - i * 30);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_WALL], true);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(15 - 8 * 30, -15, -360);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_WALLCORNERHALF], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(15 + 7 * 30, -15, -360);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_WALLCORNERHALF], true);
	modelStack.PopMatrix();
	//end of outer wall--------------------------------------------------------------------------

	//inner wall---------------------------------------------------------------------------------
	modelStack.PushMatrix();
	modelStack.Translate(-10, -15, -22);
	modelStack.Rotate(-90 + doorRotateAngle, 0, 1, 0);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_DOOR], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(15, -15, -20);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_WALLDOOR], true);
	modelStack.PopMatrix();

	for (int i = -3; i < 0; ++i) //left side of inner wall
	{
		modelStack.PushMatrix();
		modelStack.Translate(15 + i * 30, -15, -20);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_WALL], true);
		modelStack.PopMatrix();
	}

	for (int i = 1; i < 4; ++i) //right side of inner wall
	{
		modelStack.PushMatrix();
		modelStack.Translate(15 + i * 30, -15, -20);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_WALL], true);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(15 - 4 * 30, -15, -50);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_WALLCORNERHALFTOWER], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(15 + 3 * 30, -15, -50);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_WALLCORNERHALFTOWER], true);
	modelStack.PopMatrix();

	for (int i = 1; i < 7; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(105, -15, -20 - i * 30);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_WALL], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-135, -15, -20 - i * 30);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_WALL], true);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(15 - 4 * 30, -15, -230);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_WALLCORNERHALFTOWER], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(15 + 3 * 30, -15, -230);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_WALLCORNERHALFTOWER], true);
	modelStack.PopMatrix();

	for (int i = -3; i < 4; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(15 + i * 30, -15, -230);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_WALL], true);
		modelStack.PopMatrix();
	}

	//end of inner wall----------------------------------------------------------------------------

	modelStack.PushMatrix(); //middle tower
	modelStack.Translate(15, -15, -180);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_TOWERSQUAREARCH], true);
	modelStack.PopMatrix();

	for (int i = 0; i < 3; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(15, 15 + i * 30, -180);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_TOWERSQUAREMID], true);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(15, 105, -182);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_TOWERSQUARETOPROOF], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //left tower
	modelStack.Translate(-45, -15, -122);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_TOWERSQUAREBASE], true);
	modelStack.PopMatrix();

	for (int i = 0; i < 2; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-45, 15 + i * 30, -120);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_TOWERSQUAREMID], true);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(-45, 75, -122);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_TOWERSQUARETOPROOF], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //right tower
	modelStack.Translate(75, -15, -122);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_TOWERSQUAREBASE], true);
	modelStack.PopMatrix();

	for (int i = 0; i < 2; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(75, 15 + i * 30, -120);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_TOWERSQUAREMID], true);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(75, 75, -122);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_TOWERSQUARETOPROOF], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-45, -10, -150);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(15, 15, 15);
	RenderMesh(meshList[GEO_BARREL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix(); 
	modelStack.Translate(45, -10, -150);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(15, 15, 15);
	RenderMesh(meshList[GEO_BARREL], true);
	modelStack.PopMatrix();

}

void SceneAssignment2::renderRoom(void)
{
	for (int y = 0; y < 4; ++y)
	{
		for (int z = -25; z < -10; ++z)
		{
			modelStack.PushMatrix();  //left side
			modelStack.Translate(-150, y * 50 - 15, z * 50);
			modelStack.Rotate(90, 0, 1, 0);
			modelStack.Scale(50, 50, 50);
			RenderMesh(meshList[GEO_FLOOR], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix(); //right side
			modelStack.Translate(150, y * 50 - 15, z * 50);
			modelStack.Rotate(-90, 0, 1, 0);
			modelStack.Scale(50, 50, 50);
			RenderMesh(meshList[GEO_FLOOR], true);
			modelStack.PopMatrix();
		}
	}

	for (int x = 0; x < 7; ++x)
	{
		for (int y = 0; y < 4; ++y)
		{
			modelStack.PushMatrix(); //back
			modelStack.Translate(-150 + x * 50, y * 50 - 15, -550);
			modelStack.Rotate(180, 1, 0, 0);
			modelStack.Scale(50, 50, 50);
			RenderMesh(meshList[GEO_FLOOR], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix(); //front
			modelStack.Translate(-150 + x * 50, y * 50 - 15, -1150);
			modelStack.Scale(50, 50, 50);
			RenderMesh(meshList[GEO_FLOOR], true);
			modelStack.PopMatrix();

			if (fakeFrontScale >= 0.1)
			{
				modelStack.PushMatrix(); //fake front
				modelStack.Translate(-150 + x * 50, y * 50 - 15, -1050);
				modelStack.Scale(fakeFrontScale, fakeFrontScale, fakeFrontScale);
				RenderMesh(meshList[GEO_FLOOR], true);
				modelStack.PopMatrix();
			}
		}
	}

	for (int x = 0; x < 7; ++x)
	{
		for (int z = -25; z < -10; ++z)
		{
			modelStack.PushMatrix(); //bottom
			modelStack.Translate(-150 + x * 50, -15, z * 50);
			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Scale(50, 50, 50);
			RenderMesh(meshList[GEO_FLOOR], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix(); //top
			modelStack.Translate(-150 + x * 50, 135, z * 50);
			modelStack.Rotate(90, 1, 0, 0);
			modelStack.Scale(50, 50, 50);
			RenderMesh(meshList[GEO_FLOOR], true);
			modelStack.PopMatrix();
		}
	}

	modelStack.PushMatrix(); //top
	modelStack.Translate(120, -15, -840);
	RenderMesh(meshList[GEO_TOWERSQUAREBASE], true);
	if (pickUpKey == false)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-5, 10.5, 5);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Scale(0.5, 0.5, 0.5);
		RenderMesh(meshList[GEO_KEY], true);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //top
	modelStack.Translate(-100, -15, -990);
	RenderMesh(meshList[GEO_TOWERSQUAREBASE], true);
	if (pickUpKey == false && gameState == 7)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-5, 10.5, 5);
		modelStack.Rotate(90, 1, 0, 0);
		modelStack.Scale(0.5, 0.5, 0.5);
		RenderMesh(meshList[GEO_KEY], true);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //top
	modelStack.Translate(0, -15, -1110);
	RenderMesh(meshList[GEO_TOWERSQUAREBASE], true);
	if (pickUpCrown == false)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-5, 15.5, 5);
		modelStack.Scale(2, 2, 2);
		RenderMesh(meshList[GEO_CROWN], true);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //middle tower
	modelStack.Translate(-120, -15, -1130);
	modelStack.Scale(3, 3, 3);
	RenderMesh(meshList[GEO_TOWERSQUAREARCH], true);
	modelStack.PopMatrix();

	renderCover();
	renderEnemy();
}

void SceneAssignment2::renderEnemy(void)
{
	for (int i = 0; i < 9; ++i)
	{
		Vector3 tempPos = enemy[i].getPosition();
		int directionCheck = enemyDirectionCheck(i, tempPos);
		int nextTranslateState = 0;

		modelStack.PushMatrix();
		modelStack.Translate(tempPos.x, -10, tempPos.z);
		modelStack.Rotate(enemy[i].getTurnAngle(), 0, 1, 0);
		modelStack.Scale(10, 10, 10);
		RenderMesh(meshList[GEO_ENEMY], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		switch (directionCheck)
		{
		case 1:
			modelStack.Translate(tempPos.x + 10, -13, tempPos.z);
			nextTranslateState = 1;
			break;
		case 2:
			modelStack.Translate(tempPos.x - 10, -13, tempPos.z);
			nextTranslateState = -1;
			break;
		case 3:
			modelStack.Translate(tempPos.x, -13, tempPos.z + 10);
			nextTranslateState = -1;
			break;
		case 4:
			modelStack.Translate(tempPos.x, -13, tempPos.z - 10);
			nextTranslateState = 1;
			break;
		default:
			break;
		}
		modelStack.Rotate(-90, 1, 0, 0);
		modelStack.Scale(10, 10, 10);
		RenderMesh(meshList[GEO_REDQUAD], true);

		for (int i = 0; i < 2; ++i)
		{
			modelStack.PushMatrix();
			if (directionCheck == 1 || directionCheck == 2)
				modelStack.Translate(nextTranslateState, 0, 0);
			else if (directionCheck == 3 || directionCheck == 4)
				modelStack.Translate(0, nextTranslateState, 0);
			RenderMesh(meshList[GEO_REDQUAD], true);
		}
		for (int i = 0; i < 3; ++i)
			modelStack.PopMatrix();
	}
}

void SceneAssignment2::renderCover(void)
{
	for (int i = -14; i < 8; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-5 + i * 10, -15, -600);
		modelStack.Scale(20, 20, 20);
		RenderMesh(meshList[GEO_CRATE], true);
		modelStack.PopMatrix();
	}

	for (int i = 1; i < 16; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-5 + i * 10, -15, -575);
		modelStack.Scale(20, 20, 20);
		RenderMesh(meshList[GEO_CRATE], true);
		modelStack.PopMatrix();
	}

	for (int i = -7; i < 6; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-5 + i * 10, -15, -660);
		modelStack.Scale(20, 20, 20);
		RenderMesh(meshList[GEO_CRATE], true);
		modelStack.PopMatrix();
	}

	for (int i = -14; i < 2; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-5 + i * 10, -15, -690);
		modelStack.Scale(20, 20, 20);
		RenderMesh(meshList[GEO_CRATE], true);
		modelStack.PopMatrix();
	}

	for (int i = -2; i < 3; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(45, -15 + j * 10, -675 + -5 + i * 10);
			modelStack.Scale(20, 20, 20);
			RenderMesh(meshList[GEO_CRATE], true);
			modelStack.PopMatrix();
		}
	}

	for (int i = 6; i < 16; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-5 + i * 10, -15 + j * 10, -700);
			modelStack.Scale(20, 20, 20);
			RenderMesh(meshList[GEO_CRATE], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(-5 + i * 10, -15 + j * 10, -660);
			modelStack.Scale(20, 20, 20);
			RenderMesh(meshList[GEO_CRATE], true);
			modelStack.PopMatrix();
		}
	}

	modelStack.PushMatrix();
	modelStack.Translate(45, -15, -700);
	modelStack.Scale(20, 20, 20);
	RenderMesh(meshList[GEO_CRATE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(45, -15, -690);
	modelStack.Scale(20, 20, 20);
	RenderMesh(meshList[GEO_CRATE], true);
	modelStack.PopMatrix();

	for (int i = 0; i < 4; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(5, -15, -700 - i * 10);
		modelStack.Scale(20, 20, 20);
		RenderMesh(meshList[GEO_CRATE], true);
		modelStack.PopMatrix();
	}

	for (int i = -14; i < 10; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-5 + i * 10, -15, -740);
		modelStack.Scale(20, 20, 20);
		RenderMesh(meshList[GEO_CRATE], true);
		modelStack.PopMatrix();
	}

	for (int i = 0; i < 3; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(115, -15, -740 - i * 10);
		modelStack.Scale(20, 20, 20);
		RenderMesh(meshList[GEO_CRATE], true);
		modelStack.PopMatrix();
	}

	for (int i = 2; i < 16; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-5 + i * 10, -15, -800);
		modelStack.Scale(20, 20, 20);
		RenderMesh(meshList[GEO_CRATE], true);
		modelStack.PopMatrix();
	}

	for (int i = -14; i < -1; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-5 + i * 10, -15, -800);
		modelStack.Scale(20, 20, 20);
		RenderMesh(meshList[GEO_CRATE], true);
		modelStack.PopMatrix();
	}

	for (int i = -11; i < -6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-5 + i * 10, -15, -870 + j * 10);
			modelStack.Scale(20, 20, 20);
			RenderMesh(meshList[GEO_CRATE], true);
			modelStack.PopMatrix();
		}
	}

	for (int i = -6; i < 16; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-5 + i * 10, -15, -870);
		modelStack.Scale(20, 20, 20);
		RenderMesh(meshList[GEO_CRATE], true);
		modelStack.PopMatrix();
	}

	for (int i = 0; i < 3; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-65, -15, -880 - i * 10);
		modelStack.Scale(20, 20, 20);
		RenderMesh(meshList[GEO_CRATE], true);
		modelStack.PopMatrix();
	}

	for (int i = -11; i < -6; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-5 + i * 10, -15, -900);
		modelStack.Scale(20, 20, 20);
		RenderMesh(meshList[GEO_CRATE], true);
		modelStack.PopMatrix();
	}
	for (int i = -14; i < 9; i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-5 + i * 10, -15, -945);
		modelStack.Scale(20, 20, 20);
		RenderMesh(meshList[GEO_CRATE], true);
		modelStack.PopMatrix();
	}
}

void SceneAssignment2::renderDebug(void)
{
	if (showDebugInfo)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "X: " + std::to_string(camera.position.x), Color(0, 1, 0), 2, 0, 58);
		RenderTextOnScreen(meshList[GEO_TEXT], "Y: " + std::to_string(camera.position.y), Color(0, 1, 0), 2, 0, 56);
		RenderTextOnScreen(meshList[GEO_TEXT], "Z: " + std::to_string(camera.position.z), Color(0, 1, 0), 2, 0, 54);
		RenderTextOnScreen(meshList[GEO_TEXT], "GameState " + std::to_string(gameState), Color(0, 1, 0), 2, 0, 52);
		RenderTextOnScreen(meshList[GEO_TEXT], "SubGameState " + std::to_string(subGameState), Color(0, 1, 0), 2, 0, 50);
		RenderTextOnScreen(meshList[GEO_TEXT], "Light 3 X: " + std::to_string(light[3].position.x), Color(0, 1, 0), 2, 0, 48);
		RenderTextOnScreen(meshList[GEO_TEXT], "Light 3 Y: " + std::to_string(light[3].position.y), Color(0, 1, 0), 2, 0, 46);
		RenderTextOnScreen(meshList[GEO_TEXT], "Light 3 Z: " + std::to_string(light[3].position.z), Color(0, 1, 0), 2, 0, 44);
	}
}

void SceneAssignment2::walking(float LSPEED, double dt)
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

void SceneAssignment2::attacking(float LSPEED, double dt)
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
		if (translateBodyZExtra <= -10)
			translateBodyZExtraState = 0;
		if (swordRotateAngleY >= 135)
			swordRotateStateY = 0;
		if (swordRotateAngleZ >= 110)
			swordRotateStateZ = 0;
		if (leftUpperArmRotateStateZ == 0 && leftUpperArmRotateStateX == 0 && translateBodyYState == 0 && translateBodyZExtraState == 0 && upperLegRotateState == 0 && swordRotateStateY == 0)
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
			translateBodyZExtraState = 1;
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
		if (translateBodyZExtra >= 0)
			translateBodyZExtraState = 0;
		if (translateBodyYState == 0)
		{
			translateBodyY = translateBodyZExtra = rotateBodyX = rotateBodyY = leftUpperArmRotateAngleZ = leftUpperArmRotateAngleX = leftLowerArmRotateAngle = rotateUpperLegAngle = rotateLowerLegAngle = swordRotateAngleX = swordRotateAngleY = swordRotateAngleZ = 0;

			translateBodyYState = translateBodyZExtraState = rotateBodyXState = leftUpperArmRotateStateZ = leftUpperArmRotateStateX = leftLowerArmRotateState = upperLegRotateState = lowerLegRotateState = swordRotateStateX = swordRotateStateY = swordRotateStateZ = 1.0;
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
		translateBodyZExtra += (float)(translateBodyZExtraState * LSPEED * dt);
		translateBodyY += (float)(translateBodyYState * 4 * dt);
	}
	else
	{
		translateBodyZExtra += (float)(translateBodyZExtraState * 6 * dt);
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

void SceneAssignment2::dancing(float LSPEED, double dt)
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

void SceneAssignment2::reset(void)
{
	rotateHead = rotateBodyX = leftUpperArmRotateAngleZ = leftUpperArmRotateAngleX = leftLowerArmRotateAngle = rightUpperArmRotateAngleZ = rightUpperArmRotateAngleX = rightLowerArmRotateAngle = rotateUpperLegAngle = rotateLowerLegAngle = swordRotateAngleX = swordRotateAngleY = swordRotateAngleZ = 0;

	rotateHeadState = translateBodyYState = rotateBodyXState = rotateBodyYState = leftUpperArmRotateStateZ = leftUpperArmRotateStateX = leftLowerArmRotateState = rightUpperArmRotateStateZ = rightLowerArmRotateState = upperLegRotateState = lowerLegRotateState = swordRotateStateX = swordRotateStateY = swordRotateStateZ = 1;
	rightUpperArmRotateStateX = -1.0;
}

void SceneAssignment2::renderMorgana()
{
	//body
	modelStack.PushMatrix(); //1
	modelStack.Translate(translateBodyX, translateBodyY + -11.5, translateBodyZ + translateBodyZExtra);
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

void SceneAssignment2::renderHead(void)
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

void SceneAssignment2::renderScarf(void)
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

void SceneAssignment2::renderLeftArm(void)
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

void SceneAssignment2::renderRightArm(void)
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

void SceneAssignment2::renderBelt(void)
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

void SceneAssignment2::renderLeftLeg(void)
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

void SceneAssignment2::renderRightLeg(void)
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

void SceneAssignment2::renderTail(void)
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

void SceneAssignment2::renderSword(void)
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

void SceneAssignment2::renderHilt(void)
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

void SceneAssignment2::renderBlade(void)
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 8, 0);
	RenderMesh(meshList[GEO_BLADE], true);
	modelStack.PopMatrix();
}