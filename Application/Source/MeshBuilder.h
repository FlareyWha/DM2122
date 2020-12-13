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
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, Color color, float size = 1.0f);
	static Mesh* GenerateCube(const std::string &meshName, Color color, float size = 1.0f);
	static Mesh* GenerateCircle(const std::string& meshName, Color color, float radius);
	static Mesh* GenerateOval(const std::string& meshName, Color color, float width, float height);
	static Mesh* GenerateRing(const std::string& meshName, Color color, float outerRadius, float innerRadius);
	static Mesh* GenerateEye(const std::string& meshName);
	static Mesh* GenerateSphere(const std::string& meshName, Color color, float radius);
	static Mesh* GenerateOvalSphere(const std::string& meshName, Color color, float length, float width, float height);
	static Mesh* GenerateHemisphere(const std::string& meshName, Color color, float radius);
	static Mesh* GenerateOvalHemisphere(const std::string& meshName, Color color, float length, float width, float height);
	static Mesh* GenerateHead(const std::string& meshName, float width1, float length1, float width2, float length2, float height1, float height2);
	static Mesh* GenerateCylinder(const std::string& meshName, Color color, int numStack, float radius, float height);
	static Mesh* GenerateCylinderNoBase(const std::string& meshName, Color color, int numStack, float radius, float height);
	static Mesh* GenerateCylinderHemisphere(const std::string& meshName, Color color, int numStack, float radius, float height);
	static Mesh* GenerateCone(const std::string& meshName, Color color, unsigned numSlice, float radius, float height); //to make slanted make the tip (0, something, something)
	static Mesh* GenerateConeRingBase(const std::string& meshName, Color color, unsigned numSlice, float radius, float innerRadius, float height); //to make slanted make the tip (0, something, something)
	static Mesh* GenerateShavedCone(const std::string& meshName, Color color, unsigned numSlice, float radius, float height);
	static Mesh* GenerateTorus(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float outerRadius, float innerRadius);
	static Mesh* GenerateQuarterTorus(const std::string& meshName, Color color, unsigned numStack, unsigned numSlice, float outerRadius, float innerRadius);
	static Mesh* GenerateFrontScarf(const std::string& meshName, Color color, unsigned numSlice, unsigned startLength, unsigned endLength);
	static Mesh* GenerateBlade(const std::string& meshName, Color color, float height);
	static Mesh* GenerateBag(const std::string& meshName, Color color, float size);
};

#endif