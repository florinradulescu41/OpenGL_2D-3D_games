#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length);
	Mesh* CreateScorebar(std::string name, glm::vec3 leftBottomCorner, float length);

	Mesh* CreateArch(std::string name);
	Mesh* CreateShuriken(std::string name);

	Mesh* CreateBaloonBody(std::string name, glm::vec3 color);
	Mesh* CreateBaloonTail(std::string name, glm::vec3 color);
	Mesh* CreateBaloonHitBox(std::string name, glm::vec3 color);
	Mesh* CreateBaloon(std::string name);
	Mesh* CreateArrow(std::string name);

}



