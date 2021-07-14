#include "Tema2.h"

static int LEVEL = 1, number_of_platforms = 0;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void loadMeshes(std::unordered_map<std::string, Mesh*>)
{
}

void loadShaders(std::unordered_map<std::string, Shader*>)
{
}

bool intersect(float sphereX, float sphereY, float sphereZ, Platform p)
{
	// Formulas from https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection

	float x = std::max(p.p_X - BOX_SCALE_X/2, std::min(sphereX, p.p_X + BOX_SCALE_X/2));
	float y = std::max(p.p_Y - BOX_SCALE_Y/2, std::min(sphereY, p.p_Y + BOX_SCALE_Y/2));
	float z = std::max(p.p_Z - p.p_scale_Z/2, std::min(sphereZ, p.p_Z + p.p_scale_Z/2));

	float distance = sqrt((x - sphereX) * (x - sphereX) + (y - sphereY) * (y - sphereY) + z * z);
	return distance < SPHERE_RADIUS;
}

void generatePlatform(int i, Platform* box)
{
	int tip = 1 + (std::rand() % MAGIC_NUMBER);
	number_of_platforms += (MAX_PLATFORM_INCREMENT);
	LEVEL = 1 + (number_of_platforms / PLATFORMS_TO_NEXT_LEVEL);
	box[i].p_scale_Z = MIN_BOX_SCALE_Z * LEVEL + (std::rand() % MAX_BOX_SCALE_Z) * LEVEL;

	if (i % (MAX_PLATFORMS / ROWS) == 0) box[i].p_Z = box[i + ROWS - 1].p_Z - box[i + ROWS - 1].p_scale_Z - box[i].p_scale_Z / 2;
	else box[i].p_Z = box[i - 1].p_Z - box[i - 1].p_scale_Z - box[i].p_scale_Z / 2;

	if (LEVEL == 1)
		if (tip % 11 == 0) box[i].type = Orange;
		else if (tip % 7 == 0) box[i].type = Green;
		else if (tip % 9 == 0) box[i].type = Yellow;
		else box[i].type = Default_Blue;
	else if (LEVEL == 2)
		if ((tip % 13 == 0)) box[i].type = Red;
		else if (tip % 11 == 0) box[i].type = Orange;
		else if (tip % 9 == 0) box[i].type = Green;
		else if (tip % 7 == 0) box[i].type = Yellow;
		else box[i].type = Default_Blue;
	else if (LEVEL > 2)
		if ((tip % (MAGIC_NUMBER / (LEVEL + 1)) == 0)) box[i].type = Red;
		else if (tip % 13 == 0) box[i].type = Orange;
		else if (tip % (7 + LEVEL/2) == 0) box[i].type = Green;
		else if (tip % (7 - LEVEL/2) == 0) box[i].type = Yellow;
		else box[i].type = Default_Blue;
}

void Tema2::Init()
{
	// Set default camera for Third Person View

	camera = new Laborator::Camera();
	camera->Set(DEFAULT_CAMERA_3);

	// Load meshes for player - sphere and platforms - box

	loadMeshes(SimpleScene::meshes);

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// At first, 3 platforms on the first row will be generated
	// then 3 on the second row and then 3 on the third row

	for (int i = 0; i < ROWS; i++)
	{
		// All platforms on a row have the same box_X
		// initial_box_X is the value for the first row (i = 0)

		Platforms[ROWS * i].p_X = initial_box_X;
		Platforms[ROWS * i + 1].p_X = initial_box_X;
		Platforms[ROWS * i + 2].p_X = initial_box_X;

		initial_box_X += ROWS_GAP;
	}

	// Load shaders

	loadShaders(SimpleScene::shaders);

	{
		Shader* shader_default = new Shader("Blue");
		shader_default->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader_default->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderBlue.glsl", GL_FRAGMENT_SHADER);
		shader_default->CreateAndLink();
		shaders[shader_default->GetName()] = shader_default; 
	
	}

	{
		Shader* shader_purple = new Shader("Purple");
		shader_purple->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader_purple->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderPurple.glsl", GL_FRAGMENT_SHADER);
		shader_purple->CreateAndLink();
		shaders[shader_purple->GetName()] = shader_purple; 
	}

	{
		Shader* shader_green = new Shader("Green");
		shader_green->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader_green->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderGreen.glsl", GL_FRAGMENT_SHADER);
		shader_green->CreateAndLink();
		shaders[shader_green->GetName()] = shader_green;
	}

	{
		Shader* shader_yellow = new Shader("Yellow");
		shader_yellow->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader_yellow->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderYellow.glsl", GL_FRAGMENT_SHADER);
		shader_yellow->CreateAndLink();
		shaders[shader_yellow->GetName()] = shader_yellow;
	}

	{
		Shader* shader_orange = new Shader("Orange");
		shader_orange->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader_orange->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderOrange.glsl", GL_FRAGMENT_SHADER);
		shader_orange->CreateAndLink();
		shaders[shader_orange->GetName()] = shader_orange;
	}

	{
		Shader* shader_red = new Shader("Red");
		shader_red->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader_red->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderRed.glsl", GL_FRAGMENT_SHADER);
		shader_red->CreateAndLink();
		shaders[shader_red->GetName()] = shader_red;
	}

	{
		Shader* shader_white = new Shader("WhiteBar");
		shader_white->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader2D.glsl", GL_VERTEX_SHADER);
		shader_white->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderWhite.glsl", GL_FRAGMENT_SHADER);
		shader_white->CreateAndLink();
		shaders[shader_white->GetName()] = shader_white;
	}

	{
		Shader* shader_black = new Shader("BlackBar");
		shader_black->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader2D.glsl", GL_VERTEX_SHADER);
		shader_black->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderBlack.glsl", GL_FRAGMENT_SHADER);
		shader_black->CreateAndLink();
		shaders[shader_black->GetName()] = shader_black;
	}

	{
		Shader* shader_noise = new Shader("NoiseSphere");
		shader_noise->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShaderNoise.glsl", GL_VERTEX_SHADER);
		shader_noise->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShaderNoise.glsl", GL_FRAGMENT_SHADER);
		shader_noise->CreateAndLink();
		shaders[shader_noise->GetName()] = shader_noise;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}

void Tema2::FrameStart()
{
	// Set background colors for different scenarios
	// Red for gameOver, random shades of blue for warp, black as default

	if (gameOver) glClearColor(1, 0, 0, 1);
	else if (warp) glClearColor(0.3 + 1 / (1 + std::rand() % 3), 0.3 + 1 / (1 + std::rand() % 3), 1, 1); 
	else glClearColor(0, 0, 0, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	// Set camera for First Person View and Third Person View
	// For information about cameras, check Laborator5.h and LabCamera.h

	if (FirstPerson_ON) camera->Set(DEFAULT_CAMERA_1);
	else camera->Set(DEFAULT_CAMERA_3);

	glm::mat4 modelMatrix = glm::mat4(1);

	// If fuel is consumed, the game stops
	// At higher levels, fuel is consumed faster
	// When warp is active, fuel is not consumed

	if (fuel <= 0) {
		gameOver = true;
		FirstPerson_ON = false;
	}
	else if (!gameOver && !warp) fuel -= LEVEL * deltaTimeSeconds / FUEL_MODIFIER;

	// The sphere rotates in different patters to simulate rolling

	playerRotation -= 
		(gameOver) ? deltaTimeSeconds : 
			(warp) ? deltaTimeSeconds * MAX_PLATFORM_INCREMENT : 
			(onGreen) ? deltaTimeSeconds * FUEL_MODIFIER : deltaTimeSeconds * MAX_PLATFORM_INCREMENT * LEVEL;
	modelMatrix *= Transform3D::Translate(playerX, playerY + SPHERE_RADIUS, playerZ);
	modelMatrix *= Transform3D::RotateOX(playerRotation);
	if (warp) { modelMatrix *= Transform3D::RotateOZ(playerRotation); }

	// If in First Person View, don't render the sphere

	if (!FirstPerson_ON)
		if (warp) RenderMesh(meshes["sphere"], shaders["NoiseSphere"], modelMatrix);
		else RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);

	// Set and render every platform in the Platforms vector

	for (int i = 0; i < MAX_PLATFORMS; i++)
	{
		// If the sphere touches a platform, set is as occupied
		// For each platform type, set the corresponding effect

		if (intersect(playerX, playerY, playerZ, Platforms[i]) && !gameOver)
		{
			// If found = true, the sphere did not fall yet or is jumping
			// If the sphere touches a Red platform and is not in warp mode, the game ends
			// Orange platform activate acceleration and warp mode for a duration
			// Green and Yellow platforms raise or lower the fuel by a constant multiplied with level

			Platforms[i].occupied = true; found = true;
			if (Platforms[i].type == Red && !warp) gameOver = true;
			if (Platforms[i].type == Orange) acceleration ++;
			if (Platforms[i].type == Green) { fuel += (deltaTimeSeconds / (FUEL_MODIFIER / 10)) * LEVEL; onGreen = true; }
			else onGreen = false;
			if (Platforms[i].type == Yellow && !warp) fuel -= (deltaTimeSeconds / (FUEL_MODIFIER / 10)) * LEVEL;
		}
		else { Platforms[i].occupied = false; }
		
		// Activate warp for the orange platform
		// Warp grants constant high speed and immunity to fuel loss and Red platforms
		// But warp does not protect from falling off the platforms

		if (acceleration > 0 && !gameOver)
		{
			Platforms[i].p_Z += (VITEZA_MAX / 2) * deltaTimeSeconds;
			acceleration += deltaTimeSeconds * LEVEL;
			warp = true;
			if (acceleration > (10 * VITEZA_MIN) * LEVEL) {
				warp = false;
				acceleration = 0;
			}
		}

		// If a platform gets out of screen, regenerate its parameters and translate it as a new one

		if (Platforms[i].p_Z > (2 * MIN_BOX_SCALE_Z) * LEVEL) generatePlatform(i, Platforms);
		Platforms[i].modelMatrix = glm::mat4(1);
		Platforms[i].modelMatrix *= Transform3D::Translate(Platforms[i].p_X, Platforms[i].p_Y, Platforms[i].p_Z);
		Platforms[i].modelMatrix *= Transform3D::Scale(BOX_SCALE_X, BOX_SCALE_Y, Platforms[i].p_scale_Z);

		// While game is running, move the platforms with a speed proportional with current level

		if(!gameOver) Platforms[i].p_Z += game_speed * deltaTimeSeconds * LEVEL;

		// Render the platforms with corresponding settings

		if (Platforms[i].occupied) RenderMesh(meshes["box"], shaders["Purple"], Platforms[i].modelMatrix);
		else {
			if (Platforms[i].type == Default_Blue) RenderMesh(meshes["box"], shaders["Blue"], Platforms[i].modelMatrix);
			if (Platforms[i].type == Green) RenderMesh(meshes["box"], shaders["Green"], Platforms[i].modelMatrix);
			if (Platforms[i].type == Yellow) RenderMesh(meshes["box"], shaders["Yellow"], Platforms[i].modelMatrix);
			if (Platforms[i].type == Orange) RenderMesh(meshes["box"], shaders["Orange"], Platforms[i].modelMatrix);
			if (Platforms[i].type == Red) RenderMesh(meshes["box"], shaders["Red"], Platforms[i].modelMatrix);
		}

		// If the player falls of the platforms, move the camera to create a falling effect

		if (std::abs(playerX) >= (2 * BOX_SCALE_X - SPHERE_RADIUS) || (!found && playerY == SPHERE_RADIUS))
		{
			gameOver = true;
			playerY -= VITEZA_MIN * deltaTimeSeconds;
			FirstPerson_ON = true;
			camera->Set(glm::vec3(0, playerY + 3, 5), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
		}

	}

	// Render the fuel bars

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0, 0.8, 0);
	modelMatrix *= Transform3D::Translate(-0.5, 0, 0);
	modelMatrix *= Transform3D::Scale(fuel, 0.2, 0.001);
	modelMatrix *= Transform3D::Translate(0.5 , 0, 0);
	RenderMesh(meshes["box"], shaders["WhiteBar"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0, 0.8, 0);
	modelMatrix *= Transform3D::Translate(-0.5, 0, 0);
	modelMatrix *= Transform3D::Scale(1, 0.2, 0.001);
	modelMatrix *= Transform3D::Translate(0.5, 0, 0);
	RenderMesh(meshes["box"], shaders["BlackBar"], modelMatrix);
}

void Tema2::FrameEnd()
{
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// Render an object using the specified shader and the specified position

	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void Tema2::OnInputUpdate(float deltaTime, int mods) {

	int isJumping = 0;

	// Move the player right or left

	if (window->KeyHold(GLFW_KEY_D) && !gameOver) playerX += deltaTime * VITEZA_MIN;
	if (window->KeyHold(GLFW_KEY_A) && !gameOver) playerX -= deltaTime * VITEZA_MIN;

	// Change the speed if the game is not over or in warp mode

	if (window->KeyHold(GLFW_KEY_W) && acceleration == 0 && !gameOver)
		if (game_speed < VITEZA_MAX * LEVEL) game_speed += (VITEZA_MAX / 2) * deltaTime;

	if (window->KeyHold(GLFW_KEY_S) && acceleration == 0 && !gameOver)
		if (game_speed > VITEZA_MIN * LEVEL) game_speed -= (VITEZA_MIN * 2) * deltaTime;

	// Mechanics for the jump

	if (window->KeyHold(GLFW_KEY_SPACE) && playerY <= (6 * SPHERE_RADIUS) && !gameOver) isJumping ++;

	if (isJumping > 0 && !gameOver)
	{
		playerY += deltaTime * (5 * SPHERE_RADIUS);
		isJumping += deltaTime;
		if (isJumping > (MIN_BOX_SCALE_Z * 2)) isJumping = 0;
	}
	 
	if (isJumping == 0 && playerY > SPHERE_RADIUS) {
		playerY -= deltaTime * (6 * SPHERE_RADIUS);
		if (playerY < SPHERE_RADIUS) playerY = SPHERE_RADIUS;
	}

}

void Tema2::OnKeyPress(int key, int mods)
{
	// Comute the camera 
	if (key == GLFW_KEY_C) FirstPerson_ON = !FirstPerson_ON;
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
