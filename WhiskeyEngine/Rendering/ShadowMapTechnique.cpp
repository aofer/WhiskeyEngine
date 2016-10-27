#include "ShadowMapTechnique.h"

using namespace Rendering;

ShadowMapTechnique::ShadowMapTechnique()
{
}

bool ShadowMapTechnique::Init()
{
	if (!Technique::Init()) {
		return false;
	}

	if (!AddShader(GL_VERTEX_SHADER, "Shaders\\ShadowMap_vs.glsl")) {
		return false;
	}

	if (!AddShader(GL_FRAGMENT_SHADER, "Shaders\\ShadowMap_fs.glsl")) {
		return false;
	}

	if (!Finalize()) {
		return false;
	}

	m_WVPLocation = GetUniformLocation("gWVP");
	m_textureLocation = GetUniformLocation("gShadowMap");
	m_WorldMatrixLocation = GetUniformLocation("gWorld");

	if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
		m_textureLocation == INVALID_UNIFORM_LOCATION ||
		m_WorldMatrixLocation == INVALID_UNIFORM_LOCATION) {
		return false;
	}

	return true;
}

void ShadowMapTechnique::SetWVP(const glm::mat4& WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, &WVP[0][0]);
}

void ShadowMapTechnique::SetTextureUnit(unsigned int TextureUnit)
{
	glUniform1i(m_textureLocation, TextureUnit);
}


void ShadowMapTechnique::SetWorldMatrix(const glm::mat4& WorldInverse)
{
	glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_FALSE, &WorldInverse[0][0]);
}
