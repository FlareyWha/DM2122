#include "Scene2.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "Application.h"
#include "shader.hpp"


Scene2::Scene2()
{
}

Scene2::~Scene2()
{
}

void Scene2::Init()
{
	// Init VBO here
	// set background colour to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);

	rotateAngle = 1;
	translateX = 1;
	scaleAll = 1;

	// Generate a default VBO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	m_programID = LoadShaders("Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
	//use our shader
		
	glUseProgram(m_programID);

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

	// EIGHT POLYGON
	// An array of 3 vectors which represent 3 vertices
	static const GLfloat vertex_buffer_data_8_polygon[] =
	{
		-0.1565f, 0.5f, 0.0f,
		 0.1565f, 0.5f, 0.0f,
		-0.37525f, 0.21875f, 0.0f,
		 0.37425f, 0.21875f, 0.0f,
		-0.37525f, -0.21875f, 0.0f,
		 0.37425f, -0.21875f, 0.0f,
		-0.1565f, -0.5f, 0.0f,
		 0.1565f, -0.5f, 0.0f,
	};

	//set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[EIGHT_POLYGON]);
	//Transfer vertices to OPENGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_8_polygon), vertex_buffer_data_8_polygon, GL_STATIC_DRAW);

	// An array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat color_buffer_data_8_polygon[] =
	{
		1.0f, 0.0f, 0.0f, //color of vertex 0
		1.0f, 0.0f, 0.0f, //color of vertex 1
		1.0f, 0.0f, 0.0f, //color of vertex 2
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EIGHT_POLYGON]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_8_polygon), color_buffer_data_8_polygon, GL_STATIC_DRAW);

	
	// FIVE STAR
	// An array of 3 vectors which represent 3 vertices
	static const GLfloat vertex_buffer_data_five_star[] =
	{
		-0.375f, 0.2f, 0.0f, //left tip
		0.125f, 0.2f, 0.0f, 
		0.2f, -0.5f, 0.0f, //bottom left of star
		0.375f, 0.2f, 0.0f, //right tip
		-0.125f, 0.2f, 0.0f,
		-0.2f, -0.5f, 0.0f, //bottom right of star
		0.0f, 0.5f, 0.0f,
		0.1f, 0.2f, 0.0f,
		-0.1f, 0.2f, 0.0f,
	};

	//set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[FIVE_STAR]);
	//Transfer vertices to OPENGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_five_star), vertex_buffer_data_five_star, GL_STATIC_DRAW);

	// An array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat color_buffer_data_five_star[] =
	{
		1.0f, 1.0f, 0.0f, //color of vertex 0
		1.0f, 1.0f, 0.0f, //color of vertex 1
		1.0f, 1.0f, 0.0f, //color of vertex 2
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[FIVE_STAR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_five_star), color_buffer_data_five_star, GL_STATIC_DRAW);
	
	// RANDOM SHAPE
	// An array of 3 vectors which represent 3 vertices
	static const GLfloat vertex_buffer_data_random[] =
	{
		0.2f, 0.3f, 0.0f,
		0.58f, -0.5f, 0.0f,
		0.25f, -0.2f, 0.0f,
		-0.75f, 0.0f, 0.0f,
		-0.1f, 0.5f, 0.0f,
		0.2f, 0.3f, 0.0f
	};

	//set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[RANDOM_SHAPE]);
	//Transfer vertices to OPENGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_random), vertex_buffer_data_random, GL_STATIC_DRAW);

	// An array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat color_buffer_data_random[] =
	{
		1.0f, 0.0f, 0.0f, //color of vertex 0
		0.0f, 1.0f, 0.0f, //color of vertex 1
		0.0f, 0.0f, 1.0f, //color of vertex 2
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[RANDOM_SHAPE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_random), color_buffer_data_random, GL_STATIC_DRAW);
}

void Scene2::Update(double dt)
{
	//change so each one is not synced

	int randNumber = rand() % 50;

	if (Application::IsKeyPressed(VK_SPACE))
	{
		if (rotateAngle >= 360)
			rotateAngle += (float)(10 * dt);
		else
			rotateAngle -= (float)(10 * dt);

		if (translateX >= 10)
			translateX = -10;
		else
			translateX += (float)(randNumber * dt);

		if (scaleAll >= 10)
			scaleAll = 1;
		else
			scaleAll += (float)(2 * dt);
	}
}

void Scene2::Render()
{
	// Render VBO here
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
	view.SetToIdentity(); //no need camera for now, set to origin
	projection.SetToOrtho(-10, 10, -10, 10, -10, 10);

	//EIGHT POLYGON
	scale.SetToScale(7, 7, 7);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(5, 2, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP
	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[EIGHT_POLYGON]);
	glVertexAttribPointer(
		0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
		3,          //size
		GL_FLOAT,   //type
		GL_FALSE,   //normalised?
		0,			//stride
		0			//array buffer offset
	);
	
	glEnableVertexAttribArray(1); //2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EIGHT_POLYGON]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 8); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	
	// FIVE STAR
	scale.SetToScale(scaleAll, scaleAll, scaleAll);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-7, -1, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[FIVE_STAR]);
	glVertexAttribPointer(
		0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
		3,          //size
		GL_FLOAT,   //type
		GL_FALSE,   //normalised?
		0,			//stride
		0			//array buffer offset
	);

	glEnableVertexAttribArray(1); //2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[FIVE_STAR]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 9); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	// RANDOM
	scale.SetToScale(5, 5, 5);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(translateX, 5, 8);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[RANDOM_SHAPE]);
	glVertexAttribPointer(
		0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
		3,          //size
		GL_FLOAT,   //type
		GL_FALSE,   //normalised?
		0,			//stride
		0			//array buffer offset
	);

	glEnableVertexAttribArray(1); //2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[RANDOM_SHAPE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	
}

void Scene2::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
