#include "SkyboxTechnique.h"

namespace Rendering
{
	Rendering::SkyboxTechnique::SkyboxTechnique()
	{

	}

	bool SkyboxTechnique::Init()
	{
		if (!Technique::Init()) {
			return false;
		}

		if (!AddShader(GL_VERTEX_SHADER, "Shaders\\Skybox_vs.glsl")) {
			return false;
		}

		if (!AddShader(GL_FRAGMENT_SHADER, "Shaders\\Skybox_fs.glsl")) {
			return false;
		}

		if (!Finalize()) {
			return false;
		}

		m_WVPLocation = GetUniformLocation("gWVP");
		m_textureLocation = GetUniformLocation("gCubeMapSampler");

		if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
			m_textureLocation == INVALID_UNIFORM_LOCATION) {
			return false;
		}

		return true;
	}

	void SkyboxTechnique::SetWVP(const glm::mat4& WVP)
	{
		glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, (const GLfloat*)&WVP[0][0]);
	}

	void SkyboxTechnique::SetTextureUnit(unsigned int TextureUnit)
	{
		glUniform1i(m_textureLocation, TextureUnit);
	}

}

