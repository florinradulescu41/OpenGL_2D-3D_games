#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

#define ALL_min_SPEED 50
#define ALLTYPES_max_NUMBER 5
#define ARROW_half_LENGTH 62.5
#define BALOON_min_X 200
#define BALOON_max_X 1200
#define BALOON_radius_X 30
#define BALOON_radius_Y 50
#define BALOON_max_SPEED 500
#define RED_baloon_NUMBER 5
#define YELLOW_baloon_NUMBER 5
#define BOW_SPEED 100
#define LIVES_NUMBER 3
#define LIVES_Y 600
#define LIVES_min_X 100
#define LIVES_intern_DISTANCE 100
#define POWER_min_LEVEL 2
#define POWER_max_LEVEL 8
#define SCORE_bar_X 1200
#define SCORE_bar_Y 50
#define SHURIKEN_NUMBER 5
#define SHURIKEN_min_Y 120
#define SHURIKEN_max_Y 600
#define SHURIKEN_max_X 1100
#define SHURIKEN_max_SPEED 300


class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:

		Mesh* CreateMesh(const char *name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);

		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		glm::mat3 modelMatrix;
		bool arrowReleased;
		float score, squareRelativeCenter, arrowPowerFactor, powerScale, shurikenAngularSpeed, shurikenRelativeSize;
		float bowY, bowX, arrowY, arrowX, bowAngle, arrowAngle, Ystep, Xstep, angularStep;
		float redBaloonX[5];
		float yellowBaloonX[5];
		float shurikenY[5];
		float redBaloonSpeedY[5];
		float yellowBaloonSpeedY[5];
		float shurikenSpeedX[5];
		float shurikenTranslateFactorX[5];
		float yellowBaloonTranslateFactorY[5];
		float redBaloonTranslateFactorY[5];
		float lives[3];

};
