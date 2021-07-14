#include "Object2D.h"

#include <Core/Engine.h>
#include <math.h>

Mesh* Object2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length)
{
	glm::vec3 corner = leftBottomCorner;


	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, glm::vec3(1, 0, 0)),
		VertexFormat(corner + glm::vec3(length, 0, 0), glm::vec3(0, 1, 0)),
		VertexFormat(corner + glm::vec3(length, length, 0), glm::vec3(0, 1, 0)),
		VertexFormat(corner + glm::vec3(0, length, 0), glm::vec3(1, 0, 0))
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	
	// draw 2 triangles. Add the remaining 2 indices
	indices.push_back(0);
	indices.push_back(2);

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateScorebar(std::string name, glm::vec3 leftBottomCorner, float length)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, glm::vec3(0, 1, 1)),
		VertexFormat(corner + glm::vec3(length, 0, 0), glm::vec3(0, 1, 1)),
		VertexFormat(corner + glm::vec3(length, length, 0), glm::vec3(1, 0, 1)),
		VertexFormat(corner + glm::vec3(0, length, 0), glm::vec3(1, 0, 1))
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	// draw 2 triangles. Add the remaining 2 indices
	indices.push_back(0);
	indices.push_back(2);

	square->InitFromData(vertices, indices);
	return square;
}

// Create a mesh arch

Mesh* Object2D::CreateArch(std::string name)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;
	float arg;
	Mesh* arch = new Mesh(name);

	for (unsigned short i = 0; i < 100; i++)
	{
		arg = 2* M_PI * i / 200;
		
		vertices.emplace_back(glm::vec3(-25 * cos(arg + M_PI/2), -50 * sin(arg + M_PI/2), 0), glm::vec3(1, 1, 1));
		indices.push_back(i);
	}

	//Complete the arch

	indices.push_back(100);
	indices.push_back(1);

	arch->SetDrawMode(GL_LINE_LOOP);

	arch->InitFromData(vertices, indices);
	return arch;
}

Mesh* Object2D::CreateShuriken(std::string name)
{

	float shuriken_size = 25;
	glm::vec3 center = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(center, glm::vec3(1, 1, 1)),
		VertexFormat(center + glm::vec3(shuriken_size, 0, 0), glm::vec3(1, 1, 1)),
		VertexFormat(center + glm::vec3(shuriken_size, shuriken_size, 0), glm::vec3(1, 1, 1)),
		VertexFormat(center + glm::vec3(0, shuriken_size, 0), glm::vec3(1, 1, 1)),
		VertexFormat(center + glm::vec3(-shuriken_size, shuriken_size, 0), glm::vec3(1, 1, 1)),
		VertexFormat(center + glm::vec3(-shuriken_size, 0, 0), glm::vec3(1, 1, 1)),
		VertexFormat(center + glm::vec3(-shuriken_size, -shuriken_size, 0), glm::vec3(1, 1, 1)),
		VertexFormat(center + glm::vec3(0, -shuriken_size, 0), glm::vec3(1, 1, 1)),
		VertexFormat(center + glm::vec3(shuriken_size, -shuriken_size, 0), glm::vec3(1, 1, 1))
	};

	Mesh* shuriken = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 0, 3, 4, 0, 5, 6, 0, 7, 8, 0};
	
	shuriken->SetDrawMode(GL_LINE_LOOP);
	

	shuriken->InitFromData(vertices, indices);
	return shuriken;
}


Mesh* Object2D::CreateBaloonBody(std::string name, glm::vec3 color) {
	float numTriangles = 15;
	float arg;
	float bodyradiusX = 30;
	float bodyradiusY = 30;

	std::vector<VertexFormat> vertices;
	std::vector<GLushort> indices;

	vertices.emplace_back(
		glm::vec3(0.f, 0.f, 0.f), color);

	for (GLushort i = 0; i < numTriangles; ++i)
	{
		arg = 2.0f * (GLfloat)M_PI * i / numTriangles;

		vertices.emplace_back(
			glm::vec3(cos(arg) * bodyradiusX, 1.2 * sin(arg) * bodyradiusY, 0), color);
		indices.push_back(i);
	}
	indices.push_back(numTriangles);
	indices.push_back(1);

	Mesh* body = new Mesh(name);

	body->SetDrawMode(GL_TRIANGLE_FAN);

	body->InitFromData(vertices, indices);
	return body;
}

Mesh* Object2D::CreateBaloonTail(std::string name, glm::vec3 color) {
	Mesh* tail = new Mesh(name);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(10.f, -30.f, 0.f), color),
		VertexFormat(glm::vec3(0.f, -30.f, 0.f), color),
		VertexFormat(glm::vec3(-10.f, -40.f, 0.f), color),
		VertexFormat(glm::vec3(0.f, -50.f, 0.f), color),
		VertexFormat(glm::vec3(-10.f, -60.f, 0.f), color),
		VertexFormat(glm::vec3(0.f, -60.f, 0.f), color),
		VertexFormat(glm::vec3(10.f, -50.f, 0.f), color),
		VertexFormat(glm::vec3(0.f, -40.f, 0.f), color),
		VertexFormat(glm::vec3(10.f, -50.f, 0.f), color),
		VertexFormat(glm::vec3(0.f, -40.f, 0.f), color),

	};
	std::vector<GLushort> indices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

	tail->SetDrawMode(GL_LINE_LOOP);

	tail->InitFromData(vertices, indices);
	return tail;
}

Mesh* Object2D::CreateBaloonHitBox(std::string name, glm::vec3 color) {
		Mesh* hitbox = new Mesh(name);
		float numTrianglesHBox = 15;
		float arg = 0;
		float hitBoxradiusX = 30;
		float hitBoxradiusY = 30;

		std::vector<VertexFormat> vertices;
		std::vector<GLushort> indices;

		vertices.emplace_back(
			glm::vec3(0.f, 0.f, 0.f), color);

		for (GLushort i = 0; i < numTrianglesHBox; ++i)
		{
			arg = 2.0f * (GLfloat)M_PI * i / numTrianglesHBox;

			vertices.emplace_back(
				glm::vec3(cos(arg) * hitBoxradiusX, sin(arg) * hitBoxradiusY, 0), color);
			indices.push_back(i);
	
		}

		indices.push_back(numTrianglesHBox);
		indices.push_back(1);

		hitbox->SetDrawMode(GL_TRIANGLE_FAN);
		hitbox->InitFromData(vertices, indices);
		return hitbox;
}

Mesh* Object2D::CreateArrow(std::string name) {
	Mesh* arrow = new Mesh(name);

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-50.f, 10.f, 0.f), glm::vec3(0.f, 0.f, 1.f)),
		VertexFormat(glm::vec3(50.f, 10.f, 0.f), glm::vec3(0.f, 0.f, 1.f)),
		VertexFormat(glm::vec3(55.f, 20.f, 0.f), glm::vec3(0.f, 0.f, 1.f)),
		VertexFormat(glm::vec3(75.f, 5.f, 0.f), glm::vec3(0.f, 0.f, 1.f)),
		VertexFormat(glm::vec3(55.f, -10.f, 0.f), glm::vec3(0.f, 0.f, 1.f)),
		VertexFormat(glm::vec3(50.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f)),
		VertexFormat(glm::vec3(-50.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f))
	};
	std::vector<GLushort> indices = { 0, 1, 5, 0, 6, 5, 1, 2, 3, 3, 4, 5};

	arrow->InitFromData(vertices, indices);
	return arrow;
}

	