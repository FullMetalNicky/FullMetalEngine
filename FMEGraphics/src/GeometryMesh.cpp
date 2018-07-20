
#include "GeometryMesh.h"

using namespace FME::Graphics;


GeometryMesh::GeometryMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<std::string>& textureNames) : IMesh(vertices, indices, textureNames)
{

}


std::shared_ptr<GeometryMesh> GeometryMesh::GeneratePlane(const std::vector<std::string>& textureNames)
{
	float planeVertices[] = {
		// positions          // normal           // texture coords
		1.0f ,1.0f, 0.0f,    0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // top right
		1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f, // bottom right
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-1.0f, 1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f  // top left 
	};

	unsigned int planeIndices[] = {
		0, 2, 1, // first triangle
		3, 2, 0  // second triangle
	};

	std::vector<Vertex> vertices;
	std::vector<float> floatVec(planeVertices, planeVertices + sizeof(planeVertices) / sizeof(planeVertices[0]));
	std::vector<unsigned int > indices(planeIndices, planeIndices + sizeof(planeIndices) / sizeof(planeIndices[0]));
	IMesh::FloatsToVertices(floatVec, vertices);

	std::shared_ptr<GeometryMesh> mesh(new GeometryMesh(vertices, indices, textureNames));

	return mesh;
}


std::shared_ptr<GeometryMesh> GeometryMesh::GenerateCube(const std::vector<std::string>& textureNames)
{
	float cubeVertices[] = {
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f, -1.0f,  0.0f, 0.0f, -1.0f,  1.0f, 0.0f,
		1.0f, 1.0f, -1.0f,   0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,   0.0f, 0.0f, -1.0f,  1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,  0.0f, 0.0f, -1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f,  0.0f, 0.0f,

		-1.0f, -1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		1.0f, -1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,

		-1.0f, 1.0f, 1.0f,   -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		-1.0f, 1.0f, -1.0f,  -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,   -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

		1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		1.0f, 1.0f, -1.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		1.0f, -1.0f, 1.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
		1.0f, -1.0f, -1.0f,   0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,    0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		1.0f, -1.0f, 1.0f,    0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,   0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f, 0.0f,  0.0f, 1.0f,

		-1.0f, 1.0f, -1.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		1.0f, 1.0f, -1.0f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		-1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		-1.0f, 1.0f, -1.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f
	};

	unsigned int cubeIndices[] = {
		0, 1, 2,
		3, 4, 5,
		6 , 7, 8,
		9, 10, 11,
		12, 13, 14,
		15, 16, 17,
		18, 19, 20,
		21, 22, 23,
		24, 25, 26,
		27, 28, 29,
		30, 31, 32,
		33, 34, 35
	};

	std::vector<Vertex> vertices;
	std::vector<float> floatVec(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(cubeVertices[0]));
	std::vector<unsigned int > indices(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(cubeIndices[0]));
	IMesh::FloatsToVertices(floatVec, vertices);

	std::shared_ptr<GeometryMesh> mesh(new GeometryMesh(vertices, indices, textureNames));

	return mesh;
}


std::shared_ptr<GeometryMesh> GeometryMesh::GenerateMesh(glm::ivec3 gridDim, glm::vec3(*func)(glm::vec3, glm::vec3), const std::vector<std::string>& textureNames)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (int j = 0; j < gridDim.y; ++j)
	{
		for (int i = 0; i < gridDim.x; ++i)
		{
			float x = (float)i / (float)(gridDim.x - 1);
			float y = (float)j / (float)(gridDim.y - 1);
			float z = 0.0f;
			glm::vec3 res = func(glm::vec3(x, y, z), gridDim);
			Vertex v;
			v.Position = res;
			v.Normal = glm::vec3(1.0f);
			v.TexCoords = glm::vec2(x, y);
			vertices.push_back(v);
		}
	}

	for (int j = 0; j < gridDim.y - 1; ++j)
	{
		for (int i = 0; i < gridDim.x - 1; ++i)
		{
			int row1 = j * (gridDim.x);
			int row2 = (j + 1) * (gridDim.x);

			indices.push_back(row1 + i);
			indices.push_back(row1 + i + 1);
			indices.push_back(row2 + i + 1);

			indices.push_back(row1 + i);
			indices.push_back(row2 + i + 1);
			indices.push_back(row2 + i);
		}
	}

	std::shared_ptr<GeometryMesh> mesh(new GeometryMesh(vertices, indices, textureNames));

	return mesh;
}


GeometryMesh::~GeometryMesh()
{

}