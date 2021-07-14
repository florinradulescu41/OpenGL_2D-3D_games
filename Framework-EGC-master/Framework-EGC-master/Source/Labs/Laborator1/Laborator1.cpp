#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

// Global variables

// initial background color values
int red = 0; 
int green = 0;
int blue = 0;

// for the objects vector
int index = 0;

// initial position of the object to be moved
float pozZ = 3;
float pozX = 0.5f;
float pozY = -2;

// objects to cycle on
vector<string> objects{ {"teapot", "box", "sphere"} };

Laborator1::Laborator1() {}

Laborator1::~Laborator1() {}

void Laborator1::Init() {

	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;

	// Ex 2 -- Load a new 3D object

		Mesh* mesh2 = new Mesh("teapot");
		mesh2->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh2->GetMeshID()] = mesh2;

		Mesh* mesh3 = new Mesh("sphere");
		mesh3->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh3->GetMeshID()] = mesh3;

	}
}

void Laborator1::FrameStart() {}

void Laborator1::Update(float deltaTimeSeconds) {

	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(red, green, blue, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

	// Ex 2 -- render the teapot in a different spot from the boxes
	RenderMesh(meshes["teapot"], glm::vec3(-3, 0.5f, 2), glm::vec3(0.5f));

	// Ex 4 -- object changing at key press & Ex 5 -- object moving at key holding
	RenderMesh(meshes[objects.at(index%3)], glm::vec3(pozZ, pozX, pozY));

}

void Laborator1::FrameEnd() {

	DrawCoordinatSystem();

}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods) {

	// treat continuous update based on input

	// Ex 5 - move object by holding key

	// ignore the key if mouse is pressed for camera moving

	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {

		if (window->KeyHold(GLFW_KEY_W)) {
			pozZ += deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			pozZ -= deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			pozX += deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			pozX -= deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			pozY += deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			pozY -= deltaTime;
		}
	}

};

void Laborator1::OnKeyPress(int key, int mods) {

	// add key press event

	// Ex 3 -- change colours by pressing a key

	if (key == GLFW_KEY_F) {
		// for red to switch between 0 and 1;
		red = abs(red - 1);
	}
	if (key == GLFW_KEY_G) {
		// for blue to switch between 0 and 1;
		blue = abs(blue - 1);
	}
	if (key == GLFW_KEY_H) {
		// for green to switch between 0 and 1;
		green = abs(green - 1);
	}

	// Ex 4 -- change an object by pressing a key

	// cycle through objects by index

	if (key == GLFW_KEY_B) {

		// if the index is too high, reset it
		if (index == 30)
			index = 0;

		index++;
	}

};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event

};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
