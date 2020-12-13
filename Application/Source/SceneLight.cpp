#include "SceneLight.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "Vertex.h"
#include "Utility.h"
#include "shader.hpp"


SceneLight::SceneLight()
{
}

SceneLight::~SceneLight()
{
}

void SceneLight::Init()
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
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1,0,1), 1.0f);
	meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", Color(1, 0, 0), 1.0f);
	meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(1, 1, 0), 1.0f, 0.9f);
	meshList[GEO_RING_2] = MeshBuilder::GenerateRing("ring2", Color(0.3, 0.6, 0.9), 1.0f, 0.95f);

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 0.6, 0), 1.0f);
	//CAN CHANGE COLOUR BASED ON THE MATERIAL!!!
	meshList[GEO_SPHERE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE]->material.kShininess = 5.f;

	meshList[GEO_SPHERE_2] = MeshBuilder::GenerateSphere("sphere2", Color(1, 0, 0), 1.0f);
	meshList[GEO_SPHERE_3] = MeshBuilder::GenerateSphere("sphere3", Color(1, 1, 1), 1.0f);
	meshList[GEO_SPHERE_4] = MeshBuilder::GenerateSphere("sphere4", Color(0.5, 0.5, 0.5), 1.0f);
	meshList[GEO_SPHERE_5] = MeshBuilder::GenerateSphere("sphere5", Color(0.3, 0.2, 0.1), 1.0f);
	meshList[GEO_HEMISPHERE] = MeshBuilder::GenerateHemisphere("hemisphere", Color(1, 1, 1), 1.0f);
	meshList[GEO_CYLINDER] = MeshBuilder::GenerateCylinder("cylinder", Color(1, 1, 1), 1.0f, 5.0f, 10);
	meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", Color(0.9, 0.3, 0.5), 10, 1.0f, 5.0f);
	meshList[GEO_TORUS] = MeshBuilder::GenerateTorus("torus", Color(0.9, 0.9, 0.9), 50, 50, 1.0f, 0.1f);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 1.0f);
	
	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);

	rotateAngle = 1;
	translateX = 1;
	scaleAll = 1;
	camera.Init(Vector3(10, 10, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
}

void SceneLight::Update(double dt)
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
	

	rotateAngle += (float)(1 * dt);

	if (translateX >= 10)
		translateX = -10;
	else
		translateX += (float)(10 * dt);

	if (scaleAll >= 10)
		scaleAll = 1;
	else
		scaleAll += (float)(2 * dt);
}

void SceneLight::Render()
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
	RenderMesh(meshList[GEO_AXES], false);

	/*modelStack.PushMatrix();
	modelStack.Scale(5, 5, 5);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();*/

	modelStack.PushMatrix();
	modelStack.Scale(3, 3, 3);
	modelStack.Translate(-3, 0, 0);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]);
	RenderMesh(meshList[GEO_CYLINDER], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(2, 2, 2);
	modelStack.Translate(3, 0, 0);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]);
	RenderMesh(meshList[GEO_CONE], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(3, 3, 3);
	modelStack.Translate(0, 2, 0);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]);
	RenderMesh(meshList[GEO_TORUS], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -10, 0);
	modelStack.Scale(100, 100, 100);
	modelStack.Rotate(-90, 1, 0, 0);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();
}

void SceneLight::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SceneLight::RenderMesh(Mesh* mesh, bool enableLight)
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
	mesh->Render();
}