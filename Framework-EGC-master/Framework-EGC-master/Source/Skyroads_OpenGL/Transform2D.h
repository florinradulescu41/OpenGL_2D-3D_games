#pragma once

#include <include/glm.h>
// Code taken from Tema1

namespace Transform2D
{
	// Translate matrix
	inline glm::mat3 Translate(float translateX, float translateY)
	{
		return glm::mat3(1, 0, 0, 0, 1, 0, translateX, translateY, 1);
	}

	// Scale matrix
	inline glm::mat3 Scale(float scaleX, float scaleY)
	{
		return glm::mat3(scaleX, 0, 0, 0, scaleY, 0, 0, 0, 1);
	}

	// Rotate matrix
	inline glm::mat3 Rotate(float radians)
	{
		float c = cos(radians);
		float s = sin(radians);
		return glm::mat3(c, s, 0, -s, c, 0, 0, 0, 1);
	}
}
