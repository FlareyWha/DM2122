#include "Scene5.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "Vertex.h"
#include "shader.hpp"


Scene5::Scene5()
{
}

Scene5::~Scene5()
{
}

void Scene5::Init()
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
	meshList[GEO_RING_2] = MeshBuilder::GenerateRing("ring2", Color(0.3, 0.6, 0.9), 1.0f, 0.95f);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 0.6, 0), 36, 36, 1.0f);
	meshList[GEO_SPHERE_2] = MeshBuilder::GenerateSphere("sphere2", Color(1, 0, 0), 36, 36, 1.0f);
	meshList[GEO_SPHERE_3] = MeshBuilder::GenerateSphere("sphere3", Color(1, 1, 1), 36, 36, 1.0f);
	meshList[GEO_SPHERE_4] = MeshBuilder::GenerateSphere("sphere4", Color(0.5, 0.5, 0.5), 36, 36, 1.0f);
	meshList[GEO_SPHERE_5] = MeshBuilder::GenerateSphere("sphere5", Color(0.3, 0.2, 0.1), 36, 36, 1.0f);
	meshList[GEO_HEMISPHERE] = MeshBuilder::GenerateHemisphere("hemisphere", Color(1, 1, 1), 1.0f);
	meshList[GEO_CYLINDER] = MeshBuilder::GenerateCylinder("cylinder", Color(1, 1, 1), 1.0f, 5.0f, 10);
	
	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);

	rotateAngle = 1;
	translateX = 1;
	scaleAll = 1;
	camera.Init(Vector3(10, 10, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
}

void Scene5::Update(double dt)
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

void Scene5::Render()
{
	// Render VBO here
	// set background colour to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Clear color buffer for every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 mvp;

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with the new MVP
	meshList[GEO_AXES]->Render();

	//star in middle
	modelStack.PushMatrix();
	modelStack.Scale(20, 20, 20);
	modelStack.Rotate(rotateAngle * 2, 1, 1, 0);
	modelStack.Translate(0, 0, 0);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with the new MVP
	meshList[GEO_SPHERE]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(5, 5, 5);
	modelStack.Rotate(rotateAngle * 10, 1, 1, 0);
	modelStack.Translate(0, 0, 10);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with the new MVP
	meshList[GEO_SPHERE_2]->Render();

	modelStack.PushMatrix();
	modelStack.Scale(1.2, 1.2, 1.2);
	modelStack.Rotate(rotateAngle * 10, 1, 0, 0);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with the new MVP
	meshList[GEO_RING]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(0.2, 0.2, 0.2);
	modelStack.Rotate(rotateAngle * 50, 0, 1, 1);
	modelStack.Translate(5, 0, 0);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with the new MVP
	meshList[GEO_SPHERE_3]->Render();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Scale(6, 6, 6);
	modelStack.Rotate(rotateAngle * 20, 1, 0, 1);
	modelStack.Translate(0, 5, 0);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with the new MVP
	meshList[GEO_SPHERE_4]->Render();

	modelStack.PushMatrix();
	modelStack.Scale(3, 3, 3);
	modelStack.Rotate(rotateAngle * 10, 1, 0, 0);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with the new MVP
	meshList[GEO_RING_2]->Render();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(4, 4, 4);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Translate(0, 0, 10);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with the new MVP
	meshList[GEO_CYLINDER]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(20, 20, 20);
	modelStack.Rotate(rotateAngle * 20, 0, 1, 1);
	modelStack.Translate(5, 0, 0);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with the new MVP
	meshList[GEO_SPHERE_5]->Render();

	modelStack.PushMatrix();
	modelStack.Scale(0.5, 0.5, 0.5);
	modelStack.Rotate(rotateAngle * 30, 0, 1, 0);
	modelStack.Translate(10, 0, 0);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with the new MVP
	meshList[GEO_SPHERE_3]->Render();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(0.2, 0.2, 0.2);
	modelStack.Rotate(rotateAngle * 10, 1, 0, 0);
	modelStack.Translate(0, 10, 15);
	mvp = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &mvp.a[0]); //update the shader with the new MVP
	meshList[GEO_SPHERE_2]->Render();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

}

void Scene5::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
