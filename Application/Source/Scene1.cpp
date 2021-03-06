#include "Scene1.h"
#include "GL\glew.h"

#include "shader.hpp"


Scene1::Scene1()
{
}

Scene1::~Scene1()
{
}

void Scene1::Init()
{
	// Init VBO here
	// set background colour to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);

	// Generate a default VBO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);


	// EIGHT POLYGON
	// An array of 3 vectors which represent 3 vertices
	static const GLfloat vertex_buffer_data_8_polygon[] =
	{
		-0.65625f, 1.0f, 0.0f,
		-0.34325f, 1.0f, 0.0f,
		-0.875f, 0.71875f, 0.0f,
		-0.125f, 0.71875f, 0.0f,
		-0.875f, 0.28125f, 0.0f,
		-0.125f, 0.28125f, 0.0f,
		-0.65625f, 0.0f, 0.0f,
		-0.34325f, 0.0f, 0.0f,
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
		0.125f, 0.7f, 0.0f, //left tip
		0.625f, 0.7f, 0.0f, 
		0.7f, 0.0f, 0.0f, //bottom left of star
		0.875f, 0.7f, 0.0f, //right tip
		0.375f, 0.7f, 0.0f,
		0.3f, 0.0f, 0.0f, //bottom right of star
		0.5f, 1.0f, 0.0f,
		0.6f, 0.7f, 0.0f,
		0.4f, 0.7f, 0.0f,
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
		0.4f, -0.2f, 0.0f,
		0.78f, -1.0f, 0.0f,
		0.45f, -0.7f, 0.0f,
		-0.55f, -0.5f, 0.0f,
		0.1f, 0.0f, 0.0f,
		0.4f, -0.2f, 0.0f
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

	m_programID = LoadShaders("Shader//SimpleVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader");
	//use our shader

	glUseProgram(m_programID);
}

void Scene1::Update(double dt)
{
}

void Scene1::Render()
{
	// Render VBO here
	// Clear color buffer for every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//EIGHT POLYGON
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

void Scene1::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
