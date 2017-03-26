#include "SimplePBRPointLightPassTechnique.h"
#include <limits.h>
#include <string.h>
#include "../Core/Init/Common.h"
#include "Lighting.h"

namespace Rendering
{
	SimplePBRPointLightPassTechnique::SimplePBRPointLightPassTechnique()
	{
	}

	bool SimplePBRPointLightPassTechnique::Init()
	{
		if (!Technique::Init()) {
			return false;
		}

		if (!AddShader(GL_VERTEX_SHADER, "Shaders\\PBRLightPass_vs.glsl")) {
			return false;
		}

		if (!AddShader(GL_FRAGMENT_SHADER, "Shaders\\PBRPointLightPass_fs.glsl")) {
			return false;
		}

		if (!Finalize()) {
			return false;
		}

		m_wVPLocation = GetUniformLocation("gWVP");
		m_eyeWorldPosLocation = GetUniformLocation("gEyeWorldPos");
		m_positionTextureLocation = GetUniformLocation("gPosMap");
		m_diffuseTextureLocation = GetUniformLocation("gDiffuseMap");
		m_metRoughSpecTextureLocation = GetUniformLocation("gMetRoughSpecMap");
		m_normalTextureLocation = GetUniformLocation("gNormalMap");
		m_screenSize = GetUniformLocation("gScreenSize");
		//TODO this should really go into a uniform buffer object
		m_pointLightsLocation.position = GetUniformLocation("gPointLight.position");
		m_pointLightsLocation.color = GetUniformLocation("gPointLight.color");
		m_pointLightsLocation.ambientIntensity = GetUniformLocation("gPointLight.ambientIntensity");
		m_pointLightsLocation.diffuseIntensity = GetUniformLocation("gPointLight.diffuseIntensity");
		m_pointLightsLocation.attenuation.constant = GetUniformLocation("gPointLight.atten.constant");
		m_pointLightsLocation.attenuation.linear = GetUniformLocation("gPointLight.atten.linear");
		m_pointLightsLocation.attenuation.exp = GetUniformLocation("gPointLight.atten.expo");

		//if (m_wVPLocation == INVALID_UNIFORM_LOCATION ||
		//	m_eyeWorldPosLocation == INVALID_UNIFORM_LOCATION ||
		//	m_positionTextureLocation == INVALID_UNIFORM_LOCATION ||
		//	m_diffuseTextureLocation == INVALID_UNIFORM_LOCATION ||
		//	m_metRoughSpecTextureLocation == INVALID_UNIFORM_LOCATION ||
		//	m_normalTextureLocation == INVALID_UNIFORM_LOCATION ||
		//	m_pointLightsLocation.position == INVALID_UNIFORM_LOCATION ||
		//	m_pointLightsLocation.color == INVALID_UNIFORM_LOCATION ||
		//	m_pointLightsLocation.ambientIntensity == INVALID_UNIFORM_LOCATION ||
		//	m_pointLightsLocation.diffuseIntensity == INVALID_UNIFORM_LOCATION ||
		//	m_pointLightsLocation.attenuation.constant == INVALID_UNIFORM_LOCATION ||
		//	m_pointLightsLocation.attenuation.linear == INVALID_UNIFORM_LOCATION ||
		//	m_pointLightsLocation.attenuation.exp == INVALID_UNIFORM_LOCATION )
		//{
		//	return false;
		//}

		return true;
	}

	void SimplePBRPointLightPassTechnique::SetWVP(const glm::mat4& WVP)
	{
		glUniformMatrix4fv(m_wVPLocation,1, GL_FALSE, &WVP[0][0]);
	}

	void SimplePBRPointLightPassTechnique::SetEyeWorldPosition(const glm::vec3& eyeWorldPos)
	{
		glUniform3fv(m_eyeWorldPosLocation, 1, &eyeWorldPos[0]);
	}

	void SimplePBRPointLightPassTechnique::SetPositionTextureUnit(unsigned int textureUnit)
	{
		glUniform1i(m_positionTextureLocation, textureUnit);
	}

	void SimplePBRPointLightPassTechnique::SetDiffuseTextureUnit(unsigned int textureUnit)
	{
		glUniform1i(m_diffuseTextureLocation, textureUnit);
	}

	void SimplePBRPointLightPassTechnique::SetMetRoughSpecTextureUnit(unsigned int textureUnit)
	{
		glUniform1i(m_metRoughSpecTextureLocation, textureUnit);
	}

	void SimplePBRPointLightPassTechnique::SetNormalTextureUnit(unsigned int textureUnit)
	{
		glUniform1i(m_normalTextureLocation, textureUnit);
	}

	void SimplePBRPointLightPassTechnique::SetPointLightParams(PointLight* pointLight)
	{
		glUniform3fv(m_pointLightsLocation.color, 1, &pointLight->m_color[0]);
		glUniform3fv(m_pointLightsLocation.position, 1, &pointLight->m_position[0]);
		glUniform1f(m_pointLightsLocation.ambientIntensity, pointLight->m_ambientIntensity);
		glUniform1f(m_pointLightsLocation.diffuseIntensity, pointLight->m_diffuseIntensity);
		glUniform1f(m_pointLightsLocation.attenuation.constant, pointLight->Attenuation.Constant);
		glUniform1f(m_pointLightsLocation.attenuation.linear, pointLight->Attenuation.Linear);
		glUniform1f(m_pointLightsLocation.attenuation.exp, pointLight->Attenuation.Exp);
	}

	void SimplePBRPointLightPassTechnique::SetScreenSize(unsigned int width, unsigned int height)
	{
		glUniform2f(m_screenSize, (float)width, (float)height);
	}

}

