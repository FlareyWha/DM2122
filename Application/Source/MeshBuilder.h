#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static float sphereX(float p, float t);
	static float sphereY(float p, float t);
	static float sphereZ(float p, float t);
	static Mesh* GenerateOBJ(const std::string& meshName, const std::string& file_path);
	static Mesh* GenerateOBJMTL(const std::string& meshName, const std::string& file_path, const std::string& mtl_path);
	static Mesh* GenerateText(const std::string& meshName, unsigned numRow, unsigned numCol);
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, Color color, float size = 1.0f);
	static Mesh* GenerateCube(const std::string &meshName, Color color, float size = 1.0f);
	static Mesh* GenerateCircle(const std::string& meshName, Color color, float radius);
	static Mesh* GenerateOval(const std::string& meshName, Color color, float width, float height);
	static Mesh* GenerateRing(const std::string& meshName, Color color, float outerRadius, float innerRadius);
	static Mesh* GenerateSphere(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float radius);
	static Mesh* GenerateOvalSphere(const std::string& meshName, Color color, float length, float width, float height);
	static Mesh* GenerateHemisphere(const std::string& meshName, Color color, float radius);
	static Mesh* GenerateOvalHemisphere(const std::string& meshName, Color color, float length, float width, float height);
	static Mesh* GenerateCylinder(const std::string& meshName, Color color, int numStack, float radius, float height);
	static Mesh* GenerateCylinderNoBase(const std::string& meshName, Color color, int numStack, float radius, float height);
	static Mesh* GenerateCylinderHemisphere(const std::string& meshName, Color color, int numStack, float radius, float height);
	static Mesh* GenerateCone(const std::string& meshName, Color color, unsigned numSlice, float radius, float height); //to make slanted make the tip (0, something, something)
	static Mesh* GenerateConeRingBase(const std::string& meshName, Color color, unsigned numSlice, float radius, float innerRadius, float height); //to make slanted make the tip (0, something, something)
	static Mesh* GenerateShavedCone(const std::string& meshName, Color color, unsigned numSlice, float radius, float height);
	static Mesh* GenerateTorus(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float outerRadius, float innerRadius);
	static Mesh* GenerateQuarterTorus(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float outerRadius, float innerRadius);
	static Mesh* GenerateHead(const std::string& meshName, float width1, float length1, float width2, float length2, float height1, float height2);
	static Mesh* GenerateEye(const std::string& meshName);
	static Mesh* GenerateBlade(const std::string& meshName, Color color, float height);
};

#endif