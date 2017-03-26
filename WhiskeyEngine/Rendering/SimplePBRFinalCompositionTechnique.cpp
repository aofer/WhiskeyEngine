#include <limits.h>
#include <string.h>
#include "../Core/Init/Common.h"
#include "SimplePBRFinalCompositionTechnique.h"

namespace Rendering
{
	SimplePBRFinalCompositionTechnique::SimplePBRFinalCompositionTechnique()
	{
	}

	bool SimplePBRFinalCompositionTechnique::Init()
	{
		if (!Technique::Init()) {
			return false;
		}

		if (!AddShader(GL_VERTEX_SHADER, "Shaders\\PBRLightPass_vs.glsl")) {
			return false;
		}

		if (!AddShader(GL_FRAGMENT_SHADER, "Shaders\\PBRCompositionPass_fs.glsl")) {
			return false;
		}

		if (!Finalize()) {
			return false;
		}

		m_wVPLocation = GetUniformLocation("gWVP");
		m_eyeWorldPosLocation = GetUniformLocation("gEyeWorldPos");
		m_positionTextureLocation = GetUniformLocation("gPosTexture");
		m_diffuseTextureLocation = GetUniformLocation("gDiffuseTexture");
		m_metRoughSpecTextureLocation = GetUniformLocation("gMetRoughSpecTexture");
		m_normalTextureLocation = GetUniformLocation("gNormalTexture");

		if (m_wVPLocation == INVALID_UNIFORM_LOCATION ||
			m_eyeWorldPosLocation == INVALID_UNIFORM_LOCATION ||
			m_positionTextureLocation == INVALID_UNIFORM_LOCATION ||
			m_diffuseTextureLocation == INVALID_UNIFORM_LOCATION ||
			m_metRoughSpecTextureLocation == INVALID_UNIFORM_LOCATION ||
			m_normalTextureLocation == INVALID_UNIFORM_LOCATION)
		{
			return false;
		}

		return true;
	}

	void SimplePBRFinalCompositionTechnique::SetWVP(const glm::mat4& WVP)
	{
		glUniformMatrix4fv(m_wVPLocation,1, GL_FALSE, &WVP[0][0]);
	}

	void SimplePBRFinalCompositionTechnique::SetEyeWorldPosition(const glm::vec3& eyeWorldPos)
	{
		glUniform3fv(m_eyeWorldPosLocation, 3, &eyeWorldPos[0]);
	}

	void SimplePBRFinalCompositionTechnique::SetPositionTextureUnit(unsigned int textureUnit)
	{
		glUniform1i(m_positionTextureLocation, textureUnit);
	}

	void SimplePBRFinalCompositionTechnique::SetDiffuseTextureUnit(unsigned int textureUnit)
	{
		glUniform1i(m_diffuseTextureLocation, textureUnit);
	}

	void SimplePBRFinalCompositionTechnique::SetMetRoughSpecTextureUnit(unsigned int textureUnit)
	{
		glUniform1i(m_metRoughSpecTextureLocation, textureUnit);
	}

	void SimplePBRFinalCompositionTechnique::SetNormalTextureUnit(unsigned int textureUnit)
	{
		glUniform1i(m_normalTextureLocation, textureUnit);
	}

}

