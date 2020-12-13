#include "Scene3.h"
#include "GL\glew.h"
#include "Mtx44.h"
#include "Application.h"
#include "shader.hpp"


Scene3::Scene3()
{
}

Scene3::~Scene3()
{
}

void Scene3::Init()
{
	// Init VBO here

	glEnable(GL_DEPTH_TEST);

	rotateAngle = 1;
	translateX = 1;
	scaleAll = 1;
	colour = 0.0f;
	skySwitch = false;

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

	// Right angled triangle
	// An array of 3 vectors which represent 3 vertices
	static const GLfloat vertex_buffer_data_rat[] =
	{
		-0.334f, 0.667f, 0.0f,
		-0.334f, -0.334f, 0.0f,
		0.667f, -0.334f, 0.0f
	};

	//set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[RIGHT_ANGLED_TRIANGLE]);
	//Transfer vertices to OPENGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_rat), vertex_buffer_data_rat, GL_STATIC_DRAW);

	// An array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat color_buffer_data_rat[] =
	{
		1.0f, 0.0f, 0.0f, //color of vertex 0
		1.0f, 0.0f, 0.0f, //color of vertex 1
		1.0f, 0.0f, 0.0f, //color of vertex 2
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[RIGHT_ANGLED_TRIANGLE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_rat), color_buffer_data_rat, GL_STATIC_DRAW);

	
	// Isoceles Triangle
	// An array of 3 vectors which represent 3 vertices
	static const GLfloat vertex_buffer_data_it[] =
	{
		0.0f, 1.0f, 0.1f,
		-0.5f, -1.0f, 0.1f,
		0.5f, -1.0f, 0.1f
	};

	//set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[ISOCELES_TRIANGLE]);
	//Transfer vertices to OPENGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_it), vertex_buffer_data_it, GL_STATIC_DRAW);

	// An array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat color_buffer_data_it[] =
	{
		0.0f, 0.0f, 0.0f, //color of vertex 0
		0.0f, 0.0f, 0.0f, //color of vertex 1
		0.0f, 0.0f, 0.0f, //color of vertex 2
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[ISOCELES_TRIANGLE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_it), color_buffer_data_it, GL_STATIC_DRAW);
	
	// Equaliteral triangle
	// An array of 3 vectors which represent 3 vertices
	static const GLfloat vertex_buffer_data_et[] =
	{
		0.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f
	};

	//set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[EQUALITERAL_TRIANGLE]);
	//Transfer vertices to OPENGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_et), vertex_buffer_data_et, GL_STATIC_DRAW);

	// An array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat color_buffer_data_et[] =
	{
		0.0f, 0.3f, 0.0f, //color of vertex 0
		0.0f, 0.3f, 0.0f, //color of vertex 1
		0.0f, 0.3f, 0.0f, //color of vertex 2
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EQUALITERAL_TRIANGLE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_et), color_buffer_data_et, GL_STATIC_DRAW);

	// Square
	// An array of 3 vectors which represent 3 vertices
	static const GLfloat vertex_buffer_data_sq[] =
	{
		-0.75f, 1.0f, 0.0f,
		0.75f, 1.0f, 0.0f,
		-0.75f, -1.0f, 0.0f,
		0.75f, -1.0f, 0.0f
	};

	//set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[SQUARE]);
	//Transfer vertices to OPENGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_sq), vertex_buffer_data_sq, GL_STATIC_DRAW);

	// An array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat color_buffer_data_sq[] =
	{
		0.0f, 1.0f, 0.0f, //color of vertex 0
		0.0f, 1.0f, 0.0f, //color of vertex 1
		0.0f, 1.0f, 0.0f, //color of vertex 2
		0.0f, 1.0f, 0.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[SQUARE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_sq), color_buffer_data_sq, GL_STATIC_DRAW);

	static const GLfloat vertex_buffer_data_sq2[] =
	{
		-0.75f, 1.0f, 0.1f,
		0.75f, 1.0f, 0.1f,
		-0.75f, -1.0f, 0.1f,
		0.75f, -1.0f, 0.1f
	};

	//set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[SQUARE2]);
	//Transfer vertices to OPENGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_sq2), vertex_buffer_data_sq2, GL_STATIC_DRAW);

	// An array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat color_buffer_data_sq2[] =
	{
		0.5f, 1.0f, 1.0f, //color of vertex 0
		0.5f, 1.0f, 1.0f, //color of vertex 1
		0.5f, 1.0f, 1.0f, //color of vertex 2
		0.5f, 1.0f, 1.0f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[SQUARE2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_sq2), color_buffer_data_sq2, GL_STATIC_DRAW);

	static const GLfloat vertex_buffer_data_sq3[] =
	{
		-0.75f, 1.0f, 0.0f,
		0.75f, 1.0f, 0.0f,
		-0.75f, -1.0f, 0.0f,
		0.75f, -1.0f, 0.0f
	};

	//set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[SQUARE3]);
	//Transfer vertices to OPENGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_sq3), vertex_buffer_data_sq3, GL_STATIC_DRAW);

	// An array of 3 vectors which represents the colors of the 3 vertices
	static const GLfloat color_buffer_data_sq3[] =
	{
		0.54f, 0.27f, 0.07f, //color of vertex 0
		0.54f, 0.27f, 0.07f, //color of vertex 1
		0.54f, 0.27f, 0.07f, //color of vertex 2
		0.54f, 0.27f, 0.07f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[SQUARE3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_sq3), color_buffer_data_sq3, GL_STATIC_DRAW);

	// Circle
	// An array of 3 vectors which represent 3 vertices
	int r = 1;
	int idx = 0;
	static GLfloat vertex_buffer_data_ci[1080] =
	{
		0.0f, 0.0f, 0.2f,
	};

	// An array of 3 vectors which represents the colors of the 3 vertices
	static GLfloat color_buffer_data_ci[1080] =
	{
		1.0f, 0.0f, 0.0f,
	};

	for (int i = 0; i < 360; i++)
	{
		float theta = 3.1415926 * float(i) / 180;
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		
		vertex_buffer_data_ci[idx] = x;
		if (i % 20 == 0)
		{
			color_buffer_data_ci[idx] = 1.0f;
		}
		else
		{
			color_buffer_data_ci[idx] = 0.0f;
		}
		
		idx++;
		vertex_buffer_data_ci[idx] = y;
		color_buffer_data_ci[idx] = 0.0f;
		idx++;
		vertex_buffer_data_ci[idx] = 0.2f;
		color_buffer_data_ci[idx] = 0.0f;
		idx++;
	}

	//set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE]);
	//Transfer vertices to OPENGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_ci), vertex_buffer_data_ci, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CIRCLE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_ci), color_buffer_data_ci, GL_STATIC_DRAW);

	idx = 0;
	static GLfloat vertex_buffer_data_ci2[1080] =
	{
		0.0f, 0.0f, 0.3f,
	};

	// An array of 3 vectors which represents the colors of the 3 vertices
	static GLfloat color_buffer_data_ci2[1080] =
	{
		1.0f, 1.0f, 0.0f,
	};

	for (int i = 0; i < 360; i++)
	{
		float theta = 3.1415926 * float(i) / 180;
		float x = r * cosf(theta);
		float y = r * sinf(theta);

		vertex_buffer_data_ci2[idx] = x;
		color_buffer_data_ci2[idx] = 1.0f;
		idx++;
		vertex_buffer_data_ci2[idx] = y;
		color_buffer_data_ci2[idx] = 1.0f;
		idx++;
		vertex_buffer_data_ci2[idx] = 0.9f;
		color_buffer_data_ci2[idx] = 0.0f;
		idx++;
	}

	//set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE2]);
	//Transfer vertices to OPENGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_ci2), vertex_buffer_data_ci2, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CIRCLE2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_ci2), color_buffer_data_ci2, GL_STATIC_DRAW);

	idx = 0;
	static GLfloat vertex_buffer_data_ci3[1080] =
	{
		0.0f, 0.0f, 0.0f,
	};

	// An array of 3 vectors which represents the colors of the 3 vertices
	static GLfloat color_buffer_data_ci3[1080] =
	{
		1.0f, 1.0f, 0.0f,
	};

	for (int i = 0; i < 360; i++)
	{
		float theta = 3.1415926 * float(i) / 180;
		float x = r * cosf(theta);
		float y = r * sinf(theta);

		vertex_buffer_data_ci3[idx] = x;
		color_buffer_data_ci3[idx] = 0.5f;
		idx++;
		vertex_buffer_data_ci3[idx] = y;
		color_buffer_data_ci3[idx] = 0.5f;
		idx++;
		vertex_buffer_data_ci3[idx] = 0.0f;
		color_buffer_data_ci3[idx] = 0.5f;
		idx++;
	}

	//set the current active buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE3]);
	//Transfer vertices to OPENGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data_ci3), vertex_buffer_data_ci3, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CIRCLE3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data_ci3), color_buffer_data_ci3, GL_STATIC_DRAW);
}

void Scene3::Update(double dt)
{
	//change so each one is not synced

	rotateAngle += (float)(100 * dt);

	if (translateX <= -13)
		translateX = 13;
	else
		translateX -= (float)(5 * dt);

	if (scaleAll >= 10)
		scaleAll = 1;
	else
		scaleAll += (float)(2 * dt);

	if (colour >= 1.0f)
		skySwitch = true;
	else if (colour <= 0.0f && skySwitch == true)
		skySwitch = false;

	if (skySwitch == true)
		colour -= (float)(0.5 * dt);
	else if (skySwitch == false)
		colour += (float)(0.5 * dt);
}

void Scene3::Render()
{
	// Render VBO here
	// Clear color buffer for every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set background colour to dark blue
	glClearColor(0.0f, 0.0f, colour, 0.0f);

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
	
	// Equaliteral Triangle
	scale.SetToScale(3, 3, 3);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX, 4, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[EQUALITERAL_TRIANGLE]);
	glVertexAttribPointer(
		0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
		3,          //size
		GL_FLOAT,   //type
		GL_FALSE,   //normalised?
		0,			//stride
		0			//array buffer offset
	);

	glEnableVertexAttribArray(1); //2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EQUALITERAL_TRIANGLE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 3); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	scale.SetToScale(0.5, 0.5, 0.5);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-7, 1.8, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[EQUALITERAL_TRIANGLE]);
	glVertexAttribPointer(
		0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
		3,          //size
		GL_FLOAT,   //type
		GL_FALSE,   //normalised?
		0,			//stride
		0			//array buffer offset
	);

	glEnableVertexAttribArray(1); //2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[EQUALITERAL_TRIANGLE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw the triangle
	glDrawArrays(GL_TRIANGLES, 0, 3); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	
	// Square
	scale.SetToScale(8, 8, 8);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-5, -9, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[SQUARE]);
	glVertexAttribPointer(
		0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
		3,          //size
		GL_FLOAT,   //type
		GL_FALSE,   //normalised?
		0,			//stride
		0			//array buffer offset
	);

	glEnableVertexAttribArray(1); //2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[SQUARE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	scale.SetToScale(8, 8, 8);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(5, -9, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[SQUARE]);
	glVertexAttribPointer(
		0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
		3,          //size
		GL_FLOAT,   //type
		GL_FALSE,   //normalised?
		0,			//stride
		0			//array buffer offset
	);

	glEnableVertexAttribArray(1); //2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[SQUARE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	scale.SetToScale(0.8, 0.8, 0.8);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-8, 0.5, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[SQUARE2]);
	glVertexAttribPointer(
		0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
		3,          //size
		GL_FLOAT,   //type
		GL_FALSE,   //normalised?
		0,			//stride
		0			//array buffer offset
	);

	glEnableVertexAttribArray(1); //2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[SQUARE2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	scale.SetToScale(0.8, 0.8, 0.8);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-7, 0.5, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[SQUARE2]);
	glVertexAttribPointer(
		0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
		3,          //size
		GL_FLOAT,   //type
		GL_FALSE,   //normalised?
		0,			//stride
		0			//array buffer offset
	);

	glEnableVertexAttribArray(1); //2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[SQUARE2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	scale.SetToScale(0.8, 0.8, 0.8);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-6, 0.5, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[SQUARE2]);
	glVertexAttribPointer(
		0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
		3,          //size
		GL_FLOAT,   //type
		GL_FALSE,   //normalised?
		0,			//stride
		0			//array buffer offset
	);

	glEnableVertexAttribArray(1); //2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[SQUARE2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	scale.SetToScale(0.4, 0.4, 0.4);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX, -0.6, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[SQUARE3]);
	glVertexAttribPointer(
		0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
		3,          //size
		GL_FLOAT,   //type
		GL_FALSE,   //normalised?
		0,			//stride
		0			//array buffer offset
	);

	glEnableVertexAttribArray(1); //2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[SQUARE3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	
	scale.SetToScale(0.4, 0.4, 0.4);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX, 0, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[SQUARE3]);
	glVertexAttribPointer(
		0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
		3,          //size
		GL_FLOAT,   //type
		GL_FALSE,   //normalised?
		0,			//stride
		0			//array buffer offset
	);

	glEnableVertexAttribArray(1); //2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[SQUARE3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	scale.SetToScale(0.4, 0.4, 0.4);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX, 0.4, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[SQUARE3]);
	glVertexAttribPointer(
		0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
		3,          //size
		GL_FLOAT,   //type
		GL_FALSE,   //normalised?
		0,			//stride
		0			//array buffer offset
	);

	glEnableVertexAttribArray(1); //2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[SQUARE3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	scale.SetToScale(0.4, 0.4, 0.4);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX, 0.8, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[SQUARE3]);
	glVertexAttribPointer(
		0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
		3,          //size
		GL_FLOAT,   //type
		GL_FALSE,   //normalised?
		0,			//stride
		0			//array buffer offset
	);

	glEnableVertexAttribArray(1); //2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[SQUARE3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	scale.SetToScale(0.4, 0.4, 0.4);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(translateX, 1.2, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[SQUARE3]);
	glVertexAttribPointer(
		0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
		3,          //size
		GL_FLOAT,   //type
		GL_FALSE,   //normalised?
		0,			//stride
		0			//array buffer offset
	);

	glEnableVertexAttribArray(1); //2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[SQUARE3]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw the triangle
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	// Circle
	scale.SetToScale(0.6, 0.6, 0.6);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(-8, -0.5, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE]);
	glVertexAttribPointer(
		0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
		3,          //size
		GL_FLOAT,   //type
		GL_FALSE,   //normalised?
		0,			//stride
		0			//array buffer offset
	);

	glEnableVertexAttribArray(1); //2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CIRCLE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw the triangle
	glDrawArrays(GL_TRIANGLE_FAN, 0, 360); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	scale.SetToScale(0.6, 0.6, 0.6);
	rotate.SetToRotation(rotateAngle, 0, 0, 1);
	translate.SetToTranslation(-6, -0.5, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE]);
	glVertexAttribPointer(
		0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
		3,          //size
		GL_FLOAT,   //type
		GL_FALSE,   //normalised?
		0,			//stride
		0			//array buffer offset
	);

	glEnableVertexAttribArray(1); //2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CIRCLE]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw the triangle
	glDrawArrays(GL_TRIANGLE_FAN, 0, 360); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	scale.SetToScale(0.2, 0.2, 0.2);
	rotate.SetToRotation(0, 0, 0, 1);
	translate.SetToTranslation(-5.6, 0.5, 0);
	model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
	MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

	glEnableVertexAttribArray(0); //1st attribute buffer: vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE2]);
	glVertexAttribPointer(
		0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
		3,          //size
		GL_FLOAT,   //type
		GL_FALSE,   //normalised?
		0,			//stride
		0			//array buffer offset
	);

	glEnableVertexAttribArray(1); //2nd attribute buffer: colors
	glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CIRCLE2]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Draw the triangle
	glDrawArrays(GL_TRIANGLE_FAN, 0, 360); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	if (colour >= 0.5 && colour <= 1.1)
	{
		scale.SetToScale(1, 1, 1);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(8, 8, 0);
		model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
		MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

		glEnableVertexAttribArray(0); //1st attribute buffer: vertices
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE2]);
		glVertexAttribPointer(
			0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
			3,          //size
			GL_FLOAT,   //type
			GL_FALSE,   //normalised?
			0,			//stride
			0			//array buffer offset
		);

		glEnableVertexAttribArray(1); //2nd attribute buffer: colors
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CIRCLE2]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Draw the triangle
		glDrawArrays(GL_TRIANGLE_FAN, 0, 360); //starting from vertex 0; 3 vertices = 1 triangle
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
	}

	else
	{
		scale.SetToScale(1, 1, 1);
		rotate.SetToRotation(0, 0, 0, 1);
		translate.SetToTranslation(8, 8, 0);
		model = translate * rotate * scale; //scale, followed by rotate, then lastly translate
		MVP = projection * view * model; //Remember, matrix multiplaction is the other way around
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with the new MVP

		glEnableVertexAttribArray(0); //1st attribute buffer: vertices
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer[CIRCLE3]);
		glVertexAttribPointer(
			0,          //attribute 0. Must match layout in the shader. Usually 0 is for vertex
			3,          //size
			GL_FLOAT,   //type
			GL_FALSE,   //normalised?
			0,			//stride
			0			//array buffer offset
		);

		glEnableVertexAttribArray(1); //2nd attribute buffer: colors
		glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer[CIRCLE3]);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		//Draw the triangle
		glDrawArrays(GL_TRIANGLE_FAN, 0, 360); //starting from vertex 0; 3 vertices = 1 triangle
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
	}
	
	
}

void Scene3::Exit()
{
	// Cleanup VBO here
	glDeleteBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glDeleteBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
