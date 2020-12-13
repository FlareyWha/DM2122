#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include "Vertex.h"
#include "MyMath.h"

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	v.pos.Set(1.0f * lengthX, 0.0f * lengthY, 0.0f * lengthZ); v.color.Set(1, 0, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(-1.0f * lengthX, 0.0f * lengthY, 0.0f * lengthZ); v.color.Set(1, 0, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(0.0f * lengthX, 1.0f * lengthY, 0.0f * lengthZ); v.color.Set(0, 1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(0.0f * lengthX, -1.0f * lengthY, 0.0f * lengthZ); v.color.Set(0, 1, 0); vertex_buffer_data.push_back(v);
	v.pos.Set(0.0f * lengthX, 0.0f * lengthY, 1.0f * lengthZ); v.color.Set(0, 0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(0.0f * lengthX, 0.0f * lengthY, -1.0f * lengthZ); v.color.Set(0, 0, 1); vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0); 
	index_buffer_data.push_back(1); 
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3); 
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_LINES;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string& meshName, Color color, float size)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	v.pos.Set(0.5f * size, 0.5f * size, 0.0f); v.color = color; v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * size, 0.5f * size, 0.0f); v.color = color; v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * size, -0.5f * size, 0.0f); v.color = color; v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * size, -0.5f * size, 0.0f); v.color = color; v.normal.Set(0, 0, 1); vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0); index_buffer_data.push_back(1); index_buffer_data.push_back(2);
	index_buffer_data.push_back(0); index_buffer_data.push_back(2); index_buffer_data.push_back(3);

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color, float size)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	v.color = color;

	//v.pos.Set(0.5f * size, 0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //0
	//v.pos.Set(-0.5f * size, 0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //1 
	//v.pos.Set(-0.5f * size, -0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //2 
	//v.pos.Set(0.5f * size, -0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //3
	//v.pos.Set(0.5f * size, 0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //4
	//v.pos.Set(-0.5f * size, 0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //5
	//v.pos.Set(-0.5f * size, -0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //6
	//v.pos.Set(0.5f * size, -0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //7

	v.normal.Set(0, 0, 1);
	v.pos.Set(0.5f * size, 0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //0
	v.pos.Set(-0.5f * size, 0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //1 
	v.pos.Set(-0.5f * size, -0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //2 
	v.pos.Set(0.5f * size, 0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //0
	v.pos.Set(-0.5f * size, -0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //2 
	v.pos.Set(0.5f * size, -0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //3

	v.normal.Set(-1, 0, 0);
	v.pos.Set(0.5f * size, 0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //4
	v.pos.Set(0.5f * size, 0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //0
	v.pos.Set(0.5f * size, -0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //3
	v.pos.Set(0.5f * size, 0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //4
	v.pos.Set(0.5f * size, -0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //3
	v.pos.Set(0.5f * size, -0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //7

	v.normal.Set(0, 0, -1);
	v.pos.Set(-0.5f * size, 0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //5
	v.pos.Set(0.5f * size, 0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //4
	v.pos.Set(0.5f * size, -0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //7
	v.pos.Set(-0.5f * size, 0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //5
	v.pos.Set(0.5f * size, -0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //7
	v.pos.Set(-0.5f * size, -0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //6
	
	v.normal.Set(1, 0, 0);
	v.pos.Set(-0.5f * size, 0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //1 
	v.pos.Set(-0.5f * size, 0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //5
	v.pos.Set(-0.5f * size, -0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //6
	v.pos.Set(-0.5f * size, 0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //1 
	v.pos.Set(-0.5f * size, -0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //6
	v.pos.Set(-0.5f * size, -0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //2 

	v.normal.Set(0, 1, 0);
	v.pos.Set(0.5f * size, 0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //4
	v.pos.Set(-0.5f * size, 0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //5
	v.pos.Set(-0.5f * size, 0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //1 
	v.pos.Set(0.5f * size, 0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //4
	v.pos.Set(-0.5f * size, 0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //1 
	v.pos.Set(0.5f * size, 0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //0

	v.normal.Set(0, -1, 0);
	v.pos.Set(0.5f * size, -0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //3
	v.pos.Set(-0.5f * size, -0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //2 
	v.pos.Set(-0.5f * size, -0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //6
	v.pos.Set(0.5f * size, -0.5f * size, 0.5f * size); vertex_buffer_data.push_back(v); //3
	v.pos.Set(-0.5f * size, -0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //6
	v.pos.Set(0.5f * size, -0.5f * size, -0.5f * size); vertex_buffer_data.push_back(v); //7

	//index_buffer_data.push_back(0); index_buffer_data.push_back(1); index_buffer_data.push_back(2);//
	//index_buffer_data.push_back(0); index_buffer_data.push_back(2); index_buffer_data.push_back(3);//
	//index_buffer_data.push_back(4); index_buffer_data.push_back(0); index_buffer_data.push_back(3);//
	//index_buffer_data.push_back(4); index_buffer_data.push_back(3); index_buffer_data.push_back(7);//
	//index_buffer_data.push_back(5); index_buffer_data.push_back(4); index_buffer_data.push_back(7);//
	//index_buffer_data.push_back(5); index_buffer_data.push_back(7); index_buffer_data.push_back(6);//
	//index_buffer_data.push_back(1); index_buffer_data.push_back(5); index_buffer_data.push_back(6);//
	//index_buffer_data.push_back(1); index_buffer_data.push_back(6); index_buffer_data.push_back(2);//
	//index_buffer_data.push_back(4); index_buffer_data.push_back(5); index_buffer_data.push_back(1);//
	//index_buffer_data.push_back(4); index_buffer_data.push_back(1); index_buffer_data.push_back(0);//
	//index_buffer_data.push_back(3); index_buffer_data.push_back(2); index_buffer_data.push_back(6);//
	//index_buffer_data.push_back(3); index_buffer_data.push_back(6); index_buffer_data.push_back(7);//

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateCircle(const std::string& meshName, Color color, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;


	for (int i = 0; i <= 360; i += 10)
	{
		float theta = (i * Math::PI) / 180.0f;
		float x = radius * cosf(theta);
		float z = radius * sinf(theta);

		v.pos.Set(x, 0, z); 
		v.color = color; 
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(0, 0, 0); 
		v.color = color; 
		v.normal.Set(0, -1, 0); 
		vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateOval(const std::string& meshName, Color color, float width, float height)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	for (int i = 0; i <= 360; i += 10)
	{
		float theta = (i * Math::PI) / 180.0f;
		float x = width / 2 * cosf(theta);
		float z = height / 2 * sinf(theta);

		v.pos.Set(x, 0, z);
		v.color = color;
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(0, 0, 0);
		v.color = color;
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateRing(const std::string& meshName, Color color, float outerRadius, float innerRadius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;


	for (int i = 0; i <= 360; i += 10)
	{
		float theta = (i * Math::PI) / 180.0f;
		v.pos.Set(outerRadius * cosf(theta), 0, outerRadius * sinf(theta)); 
		v.color = color; 
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(innerRadius * cosf(theta), 0, innerRadius * sinf(theta)); 
		v.color = color; 
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateEye(const std::string& meshName)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	//1.0f, 1.5f, 0.8f, 1.2f, 0.65f, 1.f, 0.1f, 0.6f, 0.1f

	//black oval
	for (int i = 0; i <= 360; i += 10)
	{
		float theta = (i * Math::PI) / 180.0f;
		v.pos.Set(0, 0, 0);
		v.color.Set(0, 0, 0);
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(0.1f * cosf(theta), 0, 0.6f * sinf(theta));
		v.color.Set(0, 0, 0);
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);

	}

	//blue ring
	for (int i = 0; i <= 360; i += 10)
	{
		float theta = (i * Math::PI) / 180.0f;
		v.pos.Set(0.1f * cosf(theta), 0, 0.6f * sinf(theta));
		v.color.Set(0, 0, 1);
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(0.65f * cosf(theta), 0, 1.f * sinf(theta));
		v.color.Set(0, 0, 1);
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
	}

	//light blue ring
	for (int i = 0; i <= 360; i += 10)
	{
		float theta = (i * Math::PI) / 180.0f;
		v.pos.Set(0.65f * cosf(theta), 0, 1.f * sinf(theta));
		v.color.Set(0.68, 0.85, 0.90);
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(0.8f * cosf(theta), 0, 1.2f * sinf(theta));
		v.color.Set(0.68, 0.85, 0.90);
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
	}

	//white ring
	for (int i = 0; i <= 360; i += 10)
	{
		float theta = (i * Math::PI) / 180.0f;
		v.pos.Set(0.8f * cosf(theta), 0, 1.2f * sinf(theta));
		v.color.Set(1, 1, 1);
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(1.0f * cosf(theta), 0, 1.5f * sinf(theta));
		v.color.Set(1, 1, 1);
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < 90; i += 10)
	{
		float phi = (i * Math::PI) / 180.0f;
		float newPhi = (i + 10) * Math::PI / 180.0f;

		for (int j = 0; j <= 360; j += 10)
		{
			float theta = (j * Math::PI) / 180.0f;
			v.pos.Set(1.0f * (cosf(phi) * cosf(theta)), 0.3f * sinf(phi), 1.5f * (cosf(phi) * sinf(theta)));
			v.color.Set(1, 1, 1);
			v.normal.Set(cosf(phi) * cosf(theta), sinf(phi), cosf(phi) * sinf(theta));
			vertex_buffer_data.push_back(v);

			v.pos.Set(1.0f * cosf(newPhi) * cosf(theta), 0.3f * sinf(newPhi), 1.5f * cosf(newPhi) * sinf(theta));
			v.color.Set(1, 1, 1);
			v.normal.Set(cosf(newPhi) * cosf(theta), sinf(newPhi), cosf(newPhi) * sinf(theta));
			vertex_buffer_data.push_back(v);
		}
	}

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateSphere(const std::string& meshName, Color color, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	for (int i = -90; i < 90; i += 10)
	{
		float phi = (i * Math::PI) / 180.0f;
		float newPhi = (i + 10) * Math::PI / 180.0f;

		for (int j = 0; j <= 360; j += 10)
		{
			float theta = (j * Math::PI) / 180.0f;
			v.pos.Set(radius * (cosf(phi) * cosf(theta)), radius * sinf(phi), radius * (cosf(phi) * sinf(theta))); 
			v.color = color; 
			v.normal.Set(cosf(phi) * cosf(theta), sinf(phi), cosf(phi) * sinf(theta)); 
			vertex_buffer_data.push_back(v);

			v.pos.Set(radius * cosf(newPhi) * cosf(theta), radius * sinf(newPhi), radius * cosf(newPhi) * sinf(theta)); 
			v.color = color; 
			v.normal.Set(cosf(newPhi) * cosf(theta), sinf(newPhi), cosf(newPhi) * sinf(theta)); 
			vertex_buffer_data.push_back(v);
		}
	}

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateOvalSphere(const std::string& meshName, Color color, float length, float width, float height)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	for (int i = -90; i < 90; i += 10)
	{
		float phi = (i * Math::PI) / 180.0f;
		float newPhi = (i + 10) * Math::PI / 180.0f;

		for (int j = 0; j <= 360; j += 10)
		{
			float theta = (j * Math::PI) / 180.0f;
			v.pos.Set((width / 2) * (cosf(phi) * cosf(theta)), height * sinf(phi), (length / 2) * (cosf(phi) * sinf(theta)));
			v.color = color;
			v.normal.Set(cosf(phi) * cosf(theta), sinf(phi), cosf(phi) * sinf(theta));
			vertex_buffer_data.push_back(v);

			v.pos.Set((width / 2) * cosf(newPhi) * cosf(theta), height * sinf(newPhi), (length / 2) * cosf(newPhi) * sinf(theta));
			v.color = color;
			v.normal.Set(cosf(newPhi) * cosf(theta), sinf(newPhi), cosf(newPhi) * sinf(theta));
			vertex_buffer_data.push_back(v);
		}
	}

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateHemisphere(const std::string& meshName, Color color, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	for (int i = 0; i < 90; i += 10)
	{
		float phi = (i * Math::PI) / 180.0f;
		float newPhi = (i + 10) * Math::PI / 180.0f;

		for (int j = 0; j <= 360; j += 10)
		{
			float theta = (j * Math::PI) / 180.0f;
			v.pos.Set(radius * (cosf(phi) * cosf(theta)), radius * sinf(phi), radius * (cosf(phi) * sinf(theta))); 
			v.color = color; 
			v.normal.Set(cosf(phi) * cosf(theta), sinf(phi), cosf(phi) * sinf(theta));
			vertex_buffer_data.push_back(v);

			v.pos.Set(radius * cosf(newPhi) * cosf(theta), radius * sinf(newPhi), radius * cosf(newPhi) * sinf(theta)); 
			v.color = color; 
			v.normal.Set(cosf(newPhi) * cosf(theta), sinf(newPhi), cosf(newPhi) * sinf(theta));
			vertex_buffer_data.push_back(v);
		}
	}

	for (int i = 0; i <= 360; i += 10)
	{
		float theta = (i * Math::PI) / 180.0f;
		v.pos.Set(0, 0, 0); 
		v.color = color; 
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(radius * cosf(theta), 0, radius * sinf(theta)); 
		v.color = color; 
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
	}


	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateOvalHemisphere(const std::string& meshName, Color color, float length, float width, float height)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	for (int i = 0; i <= 360; i += 10)
	{
		float theta = (i * Math::PI) / 180.0f;
		float x = width / 2 * cosf(theta);
		float z = length / 2 * sinf(theta);

		v.pos.Set(0, 0, 0);
		v.color = color;
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(x, 0, z);
		v.color = color;
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < 90; i += 10)
	{
		float phi = (i * Math::PI) / 180.0f;
		float newPhi = (i + 10) * Math::PI / 180.0f;

		for (int j = 0; j <= 360; j += 10)
		{
			float theta = (j * Math::PI) / 180.0f;
			v.pos.Set((width / 2) * (cosf(phi) * cosf(theta)), height * sinf(phi), (length / 2) * (cosf(phi) * sinf(theta)));
			v.color = color;
			v.normal.Set(cosf(phi) * cosf(theta), sinf(phi), cosf(phi) * sinf(theta));
			vertex_buffer_data.push_back(v);

			v.pos.Set((width / 2) * cosf(newPhi) * cosf(theta), height * sinf(newPhi), (length / 2) * cosf(newPhi) * sinf(theta));
			v.color = color;
			v.normal.Set(cosf(newPhi) * cosf(theta), sinf(newPhi), cosf(newPhi) * sinf(theta));
			vertex_buffer_data.push_back(v);
		}
	}

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateHead(const std::string& meshName, float width1, float length1, float width2, float length2, float height1, float height2)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	Color color;

	for (int i = -90; i < 0; i += 10)
	{
		float phi = (i * Math::PI) / 180.0f;
		float newPhi = (i + 10) * Math::PI / 180.0f;

		for (int j = 0; j <= 360; j += 10)
		{
			float theta = (j * Math::PI) / 180.0f;
			if (j >= 100 && j <= 260)
				color.Set(1, 1, 1);
			else
				color.Set(0, 0, 0);

			v.pos.Set(width2 * (cosf(phi) * cosf(theta)), height2 * sinf(phi), length2 * (cosf(phi) * sinf(theta)));
			v.color = color;
			v.normal.Set(cosf(phi) * cosf(theta), sinf(phi), cosf(phi) * sinf(theta));
			vertex_buffer_data.push_back(v);

			v.pos.Set(width2 * cosf(newPhi) * cosf(theta), height2 * sinf(newPhi), length2 * cosf(newPhi) * sinf(theta));
			v.color = color;
			v.normal.Set(cosf(newPhi) * cosf(theta), sinf(newPhi), cosf(newPhi) * sinf(theta));
			vertex_buffer_data.push_back(v);
		}
	}

	for (int i = 0; i <= 360; i += 10)
	{
		float theta = (i * Math::PI) / 180.0f;

		v.pos.Set(width2 * cosf(theta), 0, length2 * sinf(theta));
		v.color.Set(0, 0, 0);
		v.normal.Set(0, -1, 0);

		vertex_buffer_data.push_back(v);
		v.pos.Set(width1 * cosf(theta), 0, length1 * sinf(theta));
		v.color.Set(0, 0, 0);
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < 90; i += 10)
	{
		float phi = (i * Math::PI) / 180.0f;
		float newPhi = (i + 10) * Math::PI / 180.0f;

		for (int j = 0; j <= 360; j += 10)
		{
			float theta = (j * Math::PI) / 180.0f;
			v.pos.Set(width1 * (cosf(phi) * cosf(theta)), height1 * sinf(phi), length1 * (cosf(phi) * sinf(theta)));
			v.color.Set(0, 0, 0);
			v.normal.Set(cosf(phi) * cosf(theta), sinf(phi), cosf(phi) * sinf(theta));
			vertex_buffer_data.push_back(v);

			v.pos.Set(width1 * cosf(newPhi) * cosf(theta), height1 * sinf(newPhi), length1 * cosf(newPhi) * sinf(theta));
			v.color.Set(0, 0, 0);
			v.normal.Set(cosf(newPhi) * cosf(theta), sinf(newPhi), cosf(newPhi) * sinf(theta));
			vertex_buffer_data.push_back(v);
		}
	}

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateCylinder(const std::string& meshName, Color color, int numStack, float radius, float height)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	float stackHeight = height / numStack;


	for (int i = 0; i <= 360; i += 10)
	{
		float theta = (i * Math::PI) / 180.0f;

		v.normal.Set(0, -1, 0);
		v.pos.Set(0, -height / 2, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);

		v.normal.Set(0, -1, 0);
		v.pos.Set(radius * cosf(theta), -height / 2, radius * sinf(theta));
		v.color = color;
		vertex_buffer_data.push_back(v);
	}

	for (int stack = 0; stack < numStack; ++stack)
	{
		for (int i = 0; i <= 360; i += 10)
		{
			float theta = (i * Math::PI) / 180.0f;
			v.normal.Set(cosf(theta), 0, sinf(theta));
			v.pos.Set(radius * cosf(theta), -height / 2 + stack * stackHeight, radius * sinf(theta)); 
			v.color = color; 
			vertex_buffer_data.push_back(v);

			v.normal.Set(cosf(theta), 0, sinf(theta));
			v.pos.Set(radius * cosf(theta), -height / 2 + (stack + 1) * stackHeight, radius * sinf(theta)); 
			v.color = color; 
			vertex_buffer_data.push_back(v);
		}
	}

	for (int i = 0; i <= 360; i += 10)
	{
		float theta = (i * Math::PI) / 180.0f;

		v.normal.Set(0, 1, 0);
		v.pos.Set(radius * cosf(theta), height / 2, radius * sinf(theta)); 
		v.color = color; 
		vertex_buffer_data.push_back(v);

		v.normal.Set(0, 1, 0);
		v.pos.Set(0, height / 2, 0); 
		v.color = color; 
		vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateCylinderNoBase(const std::string& meshName, Color color, int numStack, float radius, float height)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	float stackHeight = height / numStack;

	for (int stack = 0; stack < numStack; ++stack)
	{
		for (int i = 0; i <= 360; i += 10)
		{
			float theta = (i * Math::PI) / 180.0f;
			v.normal.Set(cosf(theta), 0, sinf(theta));
			v.pos.Set(radius * cosf(theta), -height / 2 + stack * stackHeight, radius * sinf(theta));
			v.color = color;
			vertex_buffer_data.push_back(v);

			v.normal.Set(cosf(theta), 0, sinf(theta));
			v.pos.Set(radius * cosf(theta), -height / 2 + (stack + 1) * stackHeight, radius * sinf(theta));
			v.color = color;
			vertex_buffer_data.push_back(v);
		}
	}

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateCylinderHemisphere(const std::string& meshName, Color color, int numStack, float radius, float height)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	float stackHeight = height / numStack;

	for (int stack = 0; stack < numStack; ++stack)
	{
		for (int i = 0; i <= 360; i += 10)
		{
			float theta = (i * Math::PI) / 180.0f;
			v.normal.Set(cosf(theta), 0, sinf(theta));
			v.pos.Set(radius * cosf(theta), -height / 2 + stack * stackHeight, radius * sinf(theta));
			v.color = color;
			vertex_buffer_data.push_back(v);

			v.normal.Set(cosf(theta), 0, sinf(theta));
			v.pos.Set(radius * cosf(theta), -height / 2 + (stack + 1) * stackHeight, radius * sinf(theta));
			v.color = color;
			vertex_buffer_data.push_back(v);
		}
	}

	for (int i = 0; i < 90; i += 10)
	{
		float phi = (i * Math::PI) / 180.0f;
		float newPhi = (i + 10) * Math::PI / 180.0f;

		for (int j = 0; j <= 360; j += 10)
		{
			float theta = (j * Math::PI) / 180.0f;
			v.pos.Set(radius * cosf(phi) * cosf(theta), radius * sinf(phi) + height/2, radius * cosf(phi) * sinf(theta));
			v.color = color;
			v.normal.Set(cosf(phi) * cosf(theta), sinf(phi), cosf(phi) * sinf(theta));
			vertex_buffer_data.push_back(v);

			v.pos.Set(radius * cosf(newPhi) * cosf(theta), radius * sinf(newPhi) + height/2, radius * cosf(newPhi) * sinf(theta));
			v.color = color;
			v.normal.Set(cosf(newPhi) * cosf(theta), sinf(newPhi), cosf(newPhi) * sinf(theta));
			vertex_buffer_data.push_back(v);
		}
	}

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateCone(const std::string& meshName, Color color, unsigned numSlice, float radius, float height)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	float degreePerSlice = Math::DegreeToRadian(360.f / numSlice);

	for (unsigned slice = 0; slice < numSlice + 1; slice++)
	{
		float theta = slice * degreePerSlice;

		v.normal.Set(0, -1, 0);
		v.pos.Set(0, -height / 2, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);

		v.normal.Set(0, -1, 0);
		v.pos.Set(radius * cosf(theta), -height / 2, radius * sinf(theta));
		v.color = color;
		vertex_buffer_data.push_back(v);
	}

	for (unsigned slice = 0; slice < numSlice + 1; slice++)
	{
		float theta = slice * degreePerSlice;

		v.normal.Set(height * cosf(theta), radius, height * sinf(theta));
		v.normal.Normalize();
		v.pos.Set(radius * cosf(theta), -height / 2, radius * sinf(theta));
		v.color = color;
		vertex_buffer_data.push_back(v);

		v.normal.Set(height * cosf(theta), radius, height * sinf(theta));
		v.normal.Normalize();
		v.pos.Set(0, height / 2, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateConeRingBase(const std::string& meshName, Color color, unsigned numSlice, float radius, float innerRadius, float height)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	float degreePerSlice = Math::DegreeToRadian(360.f / numSlice);

	for (unsigned slice = 0; slice < numSlice + 1; slice++)
	{
		float theta = slice * degreePerSlice;

		v.normal.Set(0, -1, 0);
		v.pos.Set(innerRadius * cosf(theta), -height / 2, innerRadius * sinf(theta));
		v.color = color;
		vertex_buffer_data.push_back(v);

		v.normal.Set(0, -1, 0);
		v.pos.Set(radius * cosf(theta), -height / 2, radius * sinf(theta));
		v.color = color;
		vertex_buffer_data.push_back(v);
	}

	for (unsigned slice = 0; slice < numSlice + 1; slice++)
	{
		float theta = slice * degreePerSlice;

		v.normal.Set(height * cosf(theta), radius, height * sinf(theta));
		v.normal.Normalize();
		v.pos.Set(radius * cosf(theta), -height / 2, radius * sinf(theta));
		v.color = color;
		vertex_buffer_data.push_back(v);

		v.normal.Set(height * cosf(theta), radius, height * sinf(theta));
		v.normal.Normalize();
		v.pos.Set(0, height / 2, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateShavedCone(const std::string& meshName, Color color, unsigned numSlice, float radius, float height)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	float degreePerSlice = Math::DegreeToRadian(360.f / numSlice);

	for (unsigned slice = 0; slice < numSlice + 1; slice++)
	{
		float theta = slice * degreePerSlice;

		v.normal.Set(0, -1, 0);
		v.pos.Set(0, -height / 2, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);

		v.normal.Set(0, -1, 0);
		v.pos.Set(radius * cosf(theta), -height / 2, radius * sinf(theta));
		v.color = color;
		vertex_buffer_data.push_back(v);
	}

	for (unsigned slice = 0; slice < numSlice + 1; slice++)
	{
		float theta = slice * degreePerSlice;

		v.normal.Set(height * cosf(theta), radius, height * sinf(theta));
		v.normal.Normalize();
		v.pos.Set(radius * cosf(theta), -height / 2, radius * sinf(theta));
		v.color = color;
		vertex_buffer_data.push_back(v);

		v.normal.Set(height * cosf(theta), radius, height * sinf(theta));
		v.normal.Normalize();
		v.pos.Set(radius / 3 * cosf(theta), height / 2, radius / 3 * sinf(theta));
		v.color = color;
		vertex_buffer_data.push_back(v);
	}

	for (unsigned slice = 0; slice < numSlice + 1; slice++)
	{
		float theta = slice * degreePerSlice;

		v.normal.Set(0, 1, 0);
		v.pos.Set(radius / 3 * cosf(theta), height / 2, radius / 3 * sinf(theta));
		v.color = color;
		vertex_buffer_data.push_back(v);

		v.normal.Set(0, 1, 0);
		v.pos.Set(0, height / 2, 0);
		v.color = color;
		vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateTorus(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float outerRadius, float innerRadius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	float degreePerStack = Math::DegreeToRadian(360.f / numStack);
	float degreePerSlice = Math::DegreeToRadian(360.f / numSlice);
	float x1, z1; //y1 is always zero
	float x2, y2, z2;

	for (unsigned stack = 0; stack < numStack + 1; stack++)
	{
		for (unsigned slice = 0; slice < numSlice + 1; slice++)
		{
			z1 = outerRadius * cosf(stack * degreePerStack);
			x1 = outerRadius * sinf(stack * degreePerStack);
			z2 = (outerRadius + innerRadius * cosf(slice * degreePerSlice)) * cosf(stack * degreePerStack);
			y2 = innerRadius * sinf(slice * degreePerSlice);
			x2 = (outerRadius + innerRadius * cosf(slice * degreePerSlice)) * sinf(stack * degreePerStack);
			v.pos.Set(x2, y2, z2);
			v.color = color;
			v.normal.Set(x2 - x1, y2, z2 - z1);
			v.normal.Normalize();
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned stack = 0; stack < numStack; stack++)
	{
		for (unsigned slice = 0; slice < numSlice + 1; slice++)
		{
			index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
		}
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateQuarterTorus(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float outerRadius, float innerRadius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	float degreePerStack = Math::DegreeToRadian(90.f / numStack);
	float degreePerSlice = Math::DegreeToRadian(360.f / numSlice);
	float x1, z1; //y1 is always zero
	float x2, y2, z2;

	for (unsigned stack = 0; stack < numStack + 1; stack++)
	{
		for (unsigned slice = 0; slice < numSlice + 1; slice++)
		{
			z1 = outerRadius * cosf(stack * degreePerStack);
			x1 = outerRadius * sinf(stack * degreePerStack);
			z2 = (outerRadius + innerRadius * cosf(slice * degreePerSlice)) * cosf(stack * degreePerStack);
			y2 = innerRadius * sinf(slice * degreePerSlice);
			x2 = (outerRadius + innerRadius * cosf(slice * degreePerSlice)) * sinf(stack * degreePerStack);
			v.pos.Set(x2, y2, z2);
			v.color = color;
			v.normal.Set(x2 - x1, y2, z2 - z1);
			v.normal.Normalize();
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned stack = 0; stack < numStack; stack++)
	{
		for (unsigned slice = 0; slice < numSlice + 1; slice++)
		{
			index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
		}
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateFrontScarf(const std::string& meshName, Color color, unsigned numSlice, unsigned startLength, unsigned endLength)
{
	/*Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;

	float degreePerSlice = Math::DegreeToRadian(360.f / numSlice);
	float startDegree = startLength / numSlice;
	float endDegree = endLength / numSlice;

	for (unsigned slice = 0; slice < numSlice + 1; slice++)
	{
		z1 = outerRadius * cosf(stack * degreePerStack);
		x1 = outerRadius * sinf(stack * degreePerStack);
		z2 = (outerRadius + innerRadius * cosf(slice * degreePerSlice)) * cosf(stack * degreePerStack);
		y2 = innerRadius * sinf(slice * degreePerSlice);
		x2 = (outerRadius + innerRadius * cosf(slice * degreePerSlice)) * sinf(stack * degreePerStack);
		v.pos.Set(x2, y2, z2);
		v.color = color;
		v.normal.Set(x2 - x1, y2, z2 - z1);
		v.normal.Normalize();
		vertex_buffer_data.push_back(v);
	}

	for (unsigned stack = 0; stack < numStack; stack++)
	{
		for (unsigned slice = 0; slice < numSlice + 1; slice++)
		{
			index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
		}
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	mesh->indexSize = index_buffer_data.size();

	return mesh;*/
	return nullptr;
}

Mesh* MeshBuilder::GenerateBlade(const std::string& meshName, Color color, float height)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<unsigned> index_buffer_data;
	int bladeHeight;
	v.color = color;
	
	//base
	v.normal.Set(0, -1, 0);
	v.pos.Set(0.1f, 0, 0.5f); vertex_buffer_data.push_back(v); //3
	v.pos.Set(-0.1f, 0, 0.5f); vertex_buffer_data.push_back(v); //2 
	v.pos.Set(-0.1f, 0, -0.5f); vertex_buffer_data.push_back(v); //6
	v.pos.Set(0.1f, 0, 0.5f); vertex_buffer_data.push_back(v); //3
	v.pos.Set(-0.1f, 0, -0.5f); vertex_buffer_data.push_back(v); //6
	v.pos.Set(0.1f, 0, -0.5f); vertex_buffer_data.push_back(v); //7

	for (float i = -10.0; i < 10.0; i += 0.1)
	{
		if (i <= 0.0)
			bladeHeight = 0;
		else
			bladeHeight = height;

		float theta = (i * 10 * Math::PI) / 180.0f;

		v.normal.Set(0, 0, 1);
		v.pos.Set(0.1f , i + 0.1f, 0.5f + bladeHeight * sinf(theta)); vertex_buffer_data.push_back(v); //0
		v.pos.Set(-0.1f , i + 0.1f, 0.5f + bladeHeight * sinf(theta)); vertex_buffer_data.push_back(v); //1 
		v.pos.Set(-0.1f , i, 0.5f + bladeHeight * sinf(theta)); vertex_buffer_data.push_back(v); //2 
		v.pos.Set(0.1f , i + 0.1f, 0.5f + bladeHeight * sinf(theta)); vertex_buffer_data.push_back(v); //0
		v.pos.Set(-0.1f , i, 0.5f + bladeHeight * sinf(theta)); vertex_buffer_data.push_back(v); //2 
		v.pos.Set(0.1f , i, 0.5f + bladeHeight * sinf(theta)); vertex_buffer_data.push_back(v); //3

		v.normal.Set(-1, 0, 0);
		v.pos.Set(0.1f , i + 0.1f, -0.5f + (bladeHeight / 2) * sinf(theta)); vertex_buffer_data.push_back(v); //4
		v.pos.Set(0.1f , i + 0.1f, 0.5f + bladeHeight * sinf(theta)); vertex_buffer_data.push_back(v); //0
		v.pos.Set(0.1f , i, 0.5f + bladeHeight * sinf(theta)); vertex_buffer_data.push_back(v); //3
		v.pos.Set(0.1f , i + 0.1f, -0.5f + (bladeHeight / 2) * sinf(theta)); vertex_buffer_data.push_back(v); //4
		v.pos.Set(0.1f , i, 0.5f + bladeHeight * sinf(theta)); vertex_buffer_data.push_back(v); //3
		v.pos.Set(0.1f , i, -0.5f + (bladeHeight / 2) * sinf(theta)); vertex_buffer_data.push_back(v); //7

		v.normal.Set(0, 0, -1);
		v.pos.Set(-0.1f , i + 0.1f, -0.5f + (bladeHeight / 2) * sinf(theta)); vertex_buffer_data.push_back(v); //5
		v.pos.Set(0.1f , i + 0.1f, -0.5f + (bladeHeight / 2) * sinf(theta)); vertex_buffer_data.push_back(v); //4
		v.pos.Set(0.1f , i, -0.5f + (bladeHeight / 2) * sinf(theta)); vertex_buffer_data.push_back(v); //7
		v.pos.Set(-0.1f , i + 0.1f, -0.5f + (bladeHeight / 2) * sinf(theta)); vertex_buffer_data.push_back(v); //5
		v.pos.Set(0.1f , i, -0.5f + (bladeHeight / 2) * sinf(theta)); vertex_buffer_data.push_back(v); //7
		v.pos.Set(-0.1f , i, -0.5f + (bladeHeight / 2) * sinf(theta)); vertex_buffer_data.push_back(v); //6

		v.normal.Set(1, 0, 0);
		v.pos.Set(-0.1f , i + 0.1f, 0.5f + bladeHeight * sinf(theta)); vertex_buffer_data.push_back(v); //1 
		v.pos.Set(-0.1f , i + 0.1f, -0.5f + (bladeHeight / 2) * sinf(theta)); vertex_buffer_data.push_back(v); //5
		v.pos.Set(-0.1f , i, -0.5f + (bladeHeight / 2) * sinf(theta)); vertex_buffer_data.push_back(v); //6
		v.pos.Set(-0.1f , i + 0.1f, 0.5f + bladeHeight * sinf(theta)); vertex_buffer_data.push_back(v); //1 
		v.pos.Set(-0.1f , i, -0.5f + (bladeHeight / 2) * sinf(theta)); vertex_buffer_data.push_back(v); //6
		v.pos.Set(-0.1f , i, 0.5f + bladeHeight* sinf(theta)); vertex_buffer_data.push_back(v); //2 
	}

	float theta = (10 * 10 * Math::PI) / 180.0f;

	v.normal.Set(0, 1, 0);
	v.pos.Set(0.1f, 10, -0.5f + (bladeHeight / 2) * sinf(theta)); vertex_buffer_data.push_back(v); //4
	v.pos.Set(-0.1f, 10, -0.5f + (bladeHeight / 2) * sinf(theta)); vertex_buffer_data.push_back(v); //5
	v.pos.Set(-0.1f, 10, 0.5f + bladeHeight * sinf(theta)); vertex_buffer_data.push_back(v); //1 
	v.pos.Set(0.1f, 10, -0.5f + (bladeHeight / 2) * sinf(theta)); vertex_buffer_data.push_back(v); //4
	v.pos.Set(-0.1f, 10, 0.5f + bladeHeight * sinf(theta)); vertex_buffer_data.push_back(v); //1 
	v.pos.Set(0.1f, 10, 0.5f + bladeHeight * sinf(theta)); vertex_buffer_data.push_back(v); //0

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLES;
	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateBag(const std::string& meshName, Color color, float size)
{
	return nullptr;
}

