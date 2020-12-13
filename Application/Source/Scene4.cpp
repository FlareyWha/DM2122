#include "Scene4.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "Vertex.h"
#include "shader.hpp"


Scene4::Scene4()
{
}

Scene4::~Scene4()
{
}

void Scene4::Init()
{
	// Init VBO here
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
	//use our shader
		
	glUseProgram(m_programID);

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	// Generate a default VBO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1,0,0), 1.0f);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1,0,1), 1.0f);
	meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("circle", Color(1, 0, 0), 1.0f);
	meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(1, 1, 0), 1.0f, 0.9f);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(0, 1, 1), 1.0f);
	meshList[GEO_HEMISPHERE] = MeshBuilder::GenerateHemisphere("hemisphere", Color(1, 1, 1), 1.0f);

	rotateAngle = 1;
	translateX = 1;
	scaleAll = 1;
	camera.Init(Vector3(4, 3, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));
}

void Scene4::Update(double dt)
{
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
	

	if (rotateAngle >= 360)
		rotateAngle += (float)(100 * dt);
	else
		rotateAngle -= (float)(100 * dt);

	if (translateX >= 10)
		translateX = -10;
	else
		translateX += (float)(10 * dt);

	if (scaleAll >= 10)
		scaleAll = 1;
	else
		scaleAll += (float)(2 * dt);
}

void Scene4::Render()
{
	// Render VBO here
	// set background colour to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Clear color buffer for every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 translate, rotate, scale;
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;
	Mtx44 MVP;

	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();
	view.SetToLookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	projection.SetToPerspective(45.f, 4.f / 3, 0.1f, 1000.f); //FOV, Aspect
	//Ratio, Near Plane, Far Plane

	scale.SetToScale(1, 1, 1);
	rotate.SetToRotation(0, 0, 1, 0);
	translate.SetToTranslation(0, 0, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	meshList[GEO_AXES]->Render();
	
	scale.SetToScale(2, 2, 2);
	rotate.SetToRotation(rotateAngle, 0, 1, 0);
	translate.SetToTranslation(10, 0, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP
	
	meshList[GEO_QUAD]->Render();
	meshList[GEO_CUBE]->Render();

	scale.SetToScale(2, 2, 2);
	rotate.SetToRotation(0, 0, 1, 0);
	translate.SetToTranslation(0, 10, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	meshList[GEO_CIRCLE]->Render();

	scale.SetToScale(2, 2, 2);
	rotate.SetToRotation(0, 0, 1, 0);
	translate.SetToTranslation(0, 0, 10);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	meshList[GEO_RING]->Render();

	scale.SetToScale(2, 2, 2);
	rotate.SetToRotation(0, 0, 1, 0);
	translate.SetToTranslation(10, 10, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	meshList[GEO_SPHERE]->Render();

	scale.SetToScale(2, 2, 2);
	rotate.SetToRotation(0, 0, 1, 0);
	translate.SetToTranslation(0, 0, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	meshList[GEO_HEMISPHERE]->Render();

}

void Scene4::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
