#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h> 
#include "LabCamera.h"
#include "Transform3D.h"
#include "Transform2D.h"          
#include <stdlib.h>
#include <stdio.h>
#include <random>

// Camera macros

#define DEFAULT_CAMERA_1 glm::vec3(playerX, playerY + 1, playerZ), glm::vec3(playerX, playerY, -5), glm::vec3(0, 1, 0)
#define DEFAULT_CAMERA_3 glm::vec3(0, 3, 5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0)

// Int macros

#define PLATFORMS_TO_NEXT_LEVEL 1000
#define MAX_PLATFORM_INCREMENT 10
#define MAX_BOX_SCALE_Z 15
#define MIN_BOX_SCALE_Z 5
#define FUEL_MODIFIER 100
#define MAGIC_NUMBER 42
#define MAX_PLATFORMS 9
#define VITEZA_MAX 20
#define VITEZA_MIN 5
#define ROWS 3

// Float macros
#define SPHERE_RADIUS 0.5f
#define BOX_SCALE_X 2.0f
#define BOX_SCALE_Y 0.2f
#define ROWS_GAP 2.5f

// Platform (Box) Types

enum Platform_Type { Default_Blue, Green, Yellow, Orange, Red };

// Platform Class

class Platform {
	public:
		glm::mat4 modelMatrix = glm::mat4(1);
		float p_X = 0.0f;
		float p_Y = 0.0f;
		float p_Z = 0.0f;
		float p_scale_Z = 1.5;
		bool occupied = false;
		Platform_Type type = Default_Blue;
};


class Tema2 : public SimpleScene
{
	public:
		Tema2();
		~Tema2();
		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;
		void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		Laborator::Camera* camera;
		glm::mat4 projectionMatrix;

		Platform Platforms[9];

		bool FirstPerson_ON = false;
		bool gameOver = false;
		bool onGreen = false;
		bool found = true;
		bool warp = false;

		float playerX = 0, playerY = 0.5f, playerZ = 0.0f;
		float initial_box_X = -2.5f;
		float playerRotation = 0;
		float acceleration = 0;
		float game_speed = 10;
		float falling = 0;
		float fuel = 0.5;
};
