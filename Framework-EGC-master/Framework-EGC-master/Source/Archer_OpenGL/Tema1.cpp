#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	// camera stuff - magic - don't touch!
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// initial values for variables
	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;
	squareRelativeCenter = 50;
	shurikenRelativeSize = 25;

	bowY = window->GetResolution().y / 2;
	bowX = 40;
	arrowY = 0;
	arrowX = 0;

	shurikenAngularSpeed = 0;
	arrowPowerFactor = 0;
	powerScale = 0;
	score = 0;

	arrowReleased = false;

	for (int i = 0; i < LIVES_NUMBER; i++) lives[i] = 0.4;	// initial lives scale

	for (int i = 0; i < ALLTYPES_max_NUMBER; i++) {

		//	initial random target spawning points
		yellowBaloonX[i] = (BALOON_min_X + (std::rand() % (BALOON_max_X - BALOON_min_X + 1)));
		redBaloonX[i] = (BALOON_min_X + (std::rand() % (BALOON_max_X - BALOON_min_X + 1)));
		shurikenY[i] = (SHURIKEN_min_Y + (std::rand() % (SHURIKEN_max_Y - SHURIKEN_min_Y + 1)));

		// initial random target speed
		yellowBaloonSpeedY[i] = (ALL_min_SPEED + (std::rand() % (BALOON_max_SPEED - ALL_min_SPEED + 1)));
		redBaloonSpeedY[i] = (ALL_min_SPEED + (std::rand() % (BALOON_max_SPEED - ALL_min_SPEED + 1)));
		shurikenSpeedX[i] = (ALL_min_SPEED + (std::rand() % (SHURIKEN_max_SPEED - ALL_min_SPEED + 1)));

		// initial target translate factor
		yellowBaloonTranslateFactorY[i] = 0;
		redBaloonTranslateFactorY[i] = 0;
		shurikenTranslateFactorX[i] = 0;
	}
	
	// initialize angularStep
	angularStep = 0;
	
	Mesh* square = Object2D::CreateSquare("square", corner, squareSide);
	AddMeshToList(square);

	Mesh* sc1 = Object2D::CreateScorebar("sc1", corner, squareSide);
	AddMeshToList(sc1);

	Mesh* circle1 = Object2D::CreateArch("bow");
	AddMeshToList(circle1);

	Mesh* shuriken1 = Object2D::CreateShuriken("shuriken1");
	AddMeshToList(shuriken1);

	Mesh* baloon1 = Object2D::CreateBaloonBody("baloon1", glm::vec3(1, 1, 0)); // yellow
	Mesh* baloon2 = Object2D::CreateBaloonBody("baloon2", glm::vec3(1, 0, 0));	//red
	Mesh* tail1 = Object2D::CreateBaloonTail("tail1", glm::vec3(1, 0, 1));
	AddMeshToList(baloon1);
	AddMeshToList(baloon2);
	AddMeshToList(tail1);

	Mesh* arrow = Object2D::CreateArrow("arrow");
	AddMeshToList(arrow);

}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{

	{	// Bow

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(bowX, bowY);
		modelMatrix *= Transform2D::Rotate(bowAngle);
		RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);
	}

	{	// Arrow

		modelMatrix = glm::mat3(1);
		if (!arrowReleased){	// while the arrow is nor released, it follows the position of the bow 
			modelMatrix *= Transform2D::Translate(bowX, bowY);
			modelMatrix *= Transform2D::Rotate(bowAngle);
			arrowX = bowX;
			arrowY = bowY;
			arrowAngle = bowAngle;
		}
		if (arrowReleased) {	// after the arrow is released, it's movement is based on the aim
			if (powerScale > POWER_min_LEVEL) {	// while power is over 2 (out of 10), speed increases by power
				arrowX += deltaTimeSeconds * Xstep * powerScale;
				arrowY += deltaTimeSeconds * Ystep * powerScale;
			}
			else {	// if power is too low, the minimum velocity is applied (x2)
				arrowX += deltaTimeSeconds * Xstep * POWER_min_LEVEL;
				arrowY += deltaTimeSeconds * Ystep * POWER_min_LEVEL;
			}
			modelMatrix *= Transform2D::Translate(arrowX, arrowY); // the arrow takes its own coordinates
			modelMatrix *= Transform2D::Rotate(arrowAngle);	// and it's own angle
															// so the bow changes won't apply to mid-air arrow
		}

		RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);

		// if the arrows gets over the screen space, a new arrow is created, with initial attributes
		if (arrowX > window->GetResolution().x || arrowY > window->GetResolution().y || arrowY < 0 || arrowX < 0) {
			arrowReleased = false; powerScale = 0; arrowX = 0; arrowY = 0;
		}

	}

	{	// Power Bar

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(bowX, bowY - 100);
		modelMatrix *= Transform2D::Scale(0.1, 0.1);
		if (powerScale < POWER_max_LEVEL) {	// limit so the powerScale stops at a maximum value
			powerScale += arrowPowerFactor * deltaTimeSeconds;		// the power increases in MouseBtnPress
			modelMatrix *= Transform2D::Scale(powerScale, 1);	// power bar's scaling depends on power
		} else 
			modelMatrix *= Transform2D::Scale(POWER_max_LEVEL, 1);	// the amplitude of scaling
		RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);
	}

	{ // Score bar

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(SCORE_bar_X, SCORE_bar_Y);
		modelMatrix *= Transform2D::Scale(0.4, 0.4);
		modelMatrix *= Transform2D::Scale(1, score / 2);	// the scaling is score dependant
		RenderMesh2D(meshes["sc1"], shaders["VertexColor"], modelMatrix);
	}


	for (int i = 0; i < SHURIKEN_NUMBER; i ++)
	{	// Shuriken

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(SHURIKEN_max_X, shurikenY[i]);	// initial spawning point
		shurikenTranslateFactorX[i] -= deltaTimeSeconds * shurikenSpeedX[i];	// initial X-translation factor
		modelMatrix *= Transform2D::Translate(shurikenTranslateFactorX[i], 0);
		shurikenAngularSpeed += deltaTimeSeconds;	// rotation factor
		modelMatrix *= Transform2D::Rotate(shurikenAngularSpeed);
		RenderMesh2D(meshes["shuriken1"], shaders["VertexColor"], modelMatrix);

		// if out of screen, respawn at new random coordinates, with new random translation speed
		if (shurikenTranslateFactorX[i] < - window->GetResolution().x + 100) {
			shurikenTranslateFactorX[i] = SHURIKEN_max_X;
			shurikenY[i] = SHURIKEN_min_Y + (std::rand() % (SHURIKEN_max_Y - SHURIKEN_min_Y + 1));
			shurikenSpeedX[i] = ALL_min_SPEED + (std::rand() % (SHURIKEN_max_SPEED - ALL_min_SPEED + 1));
		}

		// if hit by arrow's edge (collision), respawn and increase score
		if ((arrowY > shurikenY[i] - shurikenRelativeSize) &&
			(arrowY < shurikenY[i] + shurikenRelativeSize) && 
			(arrowX + ARROW_half_LENGTH < SHURIKEN_max_X + shurikenTranslateFactorX[i] + shurikenRelativeSize) &&
			(arrowX + ARROW_half_LENGTH > SHURIKEN_max_X + shurikenTranslateFactorX[i] - shurikenRelativeSize) &&
			arrowReleased) {
				shurikenTranslateFactorX[i] = SHURIKEN_max_X;
				shurikenY[i] = SHURIKEN_min_Y + (std::rand() % (SHURIKEN_max_Y - SHURIKEN_min_Y + 1));
				shurikenSpeedX[i] = ALL_min_SPEED + (std::rand() % (SHURIKEN_max_SPEED - ALL_min_SPEED + 1));
				score++;
		}

	}

	for (int i = 0; i < RED_baloon_NUMBER; i++)
	{	// Red Baloon
		
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(redBaloonX[i], 0);	// spawning point
		redBaloonTranslateFactorY[i] += deltaTimeSeconds * redBaloonSpeedY[i];		// Y-Translate factor
		modelMatrix *= Transform2D::Translate(0, redBaloonTranslateFactorY[i]);
		RenderMesh2D(meshes["baloon2"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["tail1"], shaders["VertexColor"], modelMatrix);

		// if out of screen, respawn at new random coordinates with random velocity
		if (redBaloonTranslateFactorY[i] > window->GetResolution().y) {
			 redBaloonTranslateFactorY[i] = 0;
			 redBaloonX[i] = BALOON_min_X + (std::rand() % (BALOON_max_X - BALOON_min_X + 1));
			 redBaloonSpeedY[i] = ALL_min_SPEED + (std::rand() % (BALOON_max_SPEED - ALL_min_SPEED + 1));
		}

		// if hit by arrow (collision), respawn and increase score
		if ((arrowY > redBaloonTranslateFactorY[i] - BALOON_radius_Y) &&
			(arrowY < redBaloonTranslateFactorY[i] + BALOON_radius_Y) &&
			(arrowX + ARROW_half_LENGTH < redBaloonX[i] + BALOON_radius_X) &&
			(arrowX + ARROW_half_LENGTH > redBaloonX[i] - BALOON_radius_X)) {
				//TODO scaling factor hit animation
				redBaloonTranslateFactorY[i] = 0;
				redBaloonX[i] = BALOON_min_X + (std::rand() % (BALOON_max_X - BALOON_min_X + 1));
				redBaloonSpeedY[i] = ALL_min_SPEED + (std::rand() % (BALOON_max_SPEED - ALL_min_SPEED + 1));
				score++;
		}

	}

	for (int i = 0; i < YELLOW_baloon_NUMBER; i++)
	{	// Yellow Baloon -- same as the red one, but decreases score when hit

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(yellowBaloonX[i], 0);
		yellowBaloonTranslateFactorY[i] += deltaTimeSeconds * yellowBaloonSpeedY[i];
		modelMatrix *= Transform2D::Translate(0, yellowBaloonTranslateFactorY[i]);
		RenderMesh2D(meshes["baloon1"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["tail1"], shaders["VertexColor"], modelMatrix);

		if (yellowBaloonTranslateFactorY[i] > window->GetResolution().y) {
			 yellowBaloonTranslateFactorY[i] = 0;
			 yellowBaloonX[i] = BALOON_min_X + (std::rand() % (BALOON_max_X - BALOON_min_X + 1));
			 yellowBaloonSpeedY[i] = ALL_min_SPEED + (std::rand() % (BALOON_max_SPEED - ALL_min_SPEED + 1));
		}

		if ((arrowY > yellowBaloonTranslateFactorY[i] - BALOON_radius_Y) &&
			(arrowY < yellowBaloonTranslateFactorY[i] + BALOON_radius_Y) &&
			(arrowX + ARROW_half_LENGTH < yellowBaloonX[i] + BALOON_radius_X) &&
			(arrowX + ARROW_half_LENGTH > yellowBaloonX[i] - BALOON_radius_X)) {
				yellowBaloonTranslateFactorY[i] = 0;
				yellowBaloonX[i] = BALOON_min_X + (std::rand() % (BALOON_max_X - BALOON_min_X + 1));
				yellowBaloonSpeedY[i] = ALL_min_SPEED + (std::rand() % (BALOON_max_SPEED - ALL_min_SPEED + 1));
				if (score > 0) score -= 2;
		}
		
	}

	for (int i = 0; i < LIVES_NUMBER; i++)
	{	// Lives

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(LIVES_min_X + LIVES_intern_DISTANCE * i, LIVES_Y);
		modelMatrix *= Transform2D::Scale(lives[i], lives[i]);	// if a life is lost, is scales to 0
		RenderMesh2D(meshes["sc1"], shaders["VertexColor"], modelMatrix);

		// create animation for the lives
		angularStep += deltaTimeSeconds / 2;
		modelMatrix *= Transform2D::Translate(squareRelativeCenter, squareRelativeCenter);
		modelMatrix *= Transform2D::Rotate(angularStep);
		modelMatrix *= Transform2D::Translate(-squareRelativeCenter, -squareRelativeCenter);
		RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);
	}

}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	// bow moving at key press
	if (window->KeyHold(GLFW_KEY_W)) bowY += deltaTime * BOW_SPEED;
	if (window->KeyHold(GLFW_KEY_S)) bowY -= deltaTime * BOW_SPEED;

}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// computing the bow rotation angle based on mouse coordinates
	bowAngle = atan2(window->GetResolution().y - mouseY - bowY, mouseX - bowX);
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// computing the direction and the power for the arrow to be released
	Xstep = (mouseX - bowX);
	Ystep = (window->GetResolution().y - bowY - mouseY);
	if (!arrowReleased) arrowPowerFactor += 2;
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// release the arrow, reset power
	arrowReleased = true;
	arrowPowerFactor = 0;
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
