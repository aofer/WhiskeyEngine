#pragma once

#include <GL/glew.h>
#include <glm\glm.hpp>

namespace Rendering 
{
	struct SimplePBRMaterial
	{
		glm::vec3	diffuseColor;
		float		metallic;
		float		specular;
		float		roughness;
	};
}
