#include <limits.h>
#include <string.h>
#include "../Core/Init/Common.h"

#include "SHTechnique.h"

using namespace Rendering;


SHTechnique::SHTechnique()
{
}

bool SHTechnique::Init()
{
	if (!Technique::Init()) {
		return false;
	}

	if (!AddShader(GL_VERTEX_SHADER, "Shaders\\SHLighting_vs.glsl")) 
	{
		return false;
	}

	if (!AddShader(GL_FRAGMENT_SHADER, "Shaders\\SHLighting_fs.glsl")) 
	{
		return false;
	}

	if (!Finalize()) 
	{
		return false;
	}

	m_WVPLocation = GetUniformLocation("gWVP");
	m_WorldMatrixLocation = GetUniformLocation("gWorld");
	//m_samplerLocation = GetUniformLocation("gSampler");

	m_matSpecularIntensityLocation = GetUniformLocation("gMatSpecularIntensity");
	m_eyeWorldPosLocation = GetUniformLocation("gEyeWorldPos");

	GLint data;
	glGetIntegerv(GL_MAX_UNIFORM_LOCATIONS, &data);

	m_numSpotLightsLocation = GetUniformLocation("gNumSpotLights");
	m_shCoeffLocation = GetUniformLocation("gCoef");
	m_materialLocation.diffuseColor = GetUniformLocation("mat.diffuseColor");
	m_materialLocation.specularColor = GetUniformLocation("mat.specColor");
	m_materialLocation.ambientColor = GetUniformLocation("mat.ambientColor");
	m_materialLocation.shininess = GetUniformLocation("mat.shininess");

	if (m_WVPLocation == INVALID_UNIFORM_LOCATION ||
		m_WorldMatrixLocation == INVALID_UNIFORM_LOCATION ||
		/*m_samplerLocation == INVALID_UNIFORM_LOCATION ||*/
		m_eyeWorldPosLocation == INVALID_UNIFORM_LOCATION ||
		m_matSpecularIntensityLocation == INVALID_UNIFORM_LOCATION ||
		//m_matSpecularPowerLocation == INVALID_UNIFORM_LOCATION ||
		m_numSpotLightsLocation == INVALID_UNIFORM_LOCATION || 
		m_shCoeffLocation == INVALID_UNIFORM_LOCATION) {
		return false;
	}

	for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_spotLightsLocation); i++) {
		char Name[128];
		memset(Name, 0, sizeof(Name));
		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Color", i);
		m_spotLightsLocation[i].Color = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].AmbientIntensity", i);
		m_spotLightsLocation[i].AmbientIntensity = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Position", i);
		m_spotLightsLocation[i].Position = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Direction", i);
		m_spotLightsLocation[i].Direction = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Cutoff", i);
		m_spotLightsLocation[i].Cutoff = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].DiffuseIntensity", i);
		m_spotLightsLocation[i].DiffuseIntensity = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Atten.Constant", i);
		m_spotLightsLocation[i].Atten.Constant = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Atten.Linear", i);
		m_spotLightsLocation[i].Atten.Linear = GetUniformLocation(Name);

		SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Atten.Exp", i);
		m_spotLightsLocation[i].Atten.Exp = GetUniformLocation(Name);

		if (m_spotLightsLocation[i].Color == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].AmbientIntensity == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].Position == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].Direction == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].Cutoff == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].Atten.Constant == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].Atten.Linear == INVALID_UNIFORM_LOCATION ||
			m_spotLightsLocation[i].Atten.Exp == INVALID_UNIFORM_LOCATION) {
			return false;
		}
	}

	return true;
}


void SHTechnique::SetWVP(const glm::mat4& WVP)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, &WVP[0][0]);
}


void SHTechnique::SetWorldMatrix(const glm::mat4& world)
{
	glUniformMatrix4fv(m_WorldMatrixLocation, 1, GL_FALSE, &world[0][0]);
}


void SHTechnique::SetTextureUnit(uint TextureUnit)
{
	glUniform1i(m_samplerLocation, TextureUnit);
}

void SHTechnique::SetCoefficients(glm::vec3 coeff[])
{
	glUniform3fv(m_shCoeffLocation, 9, &coeff[0][0]);
}


void SHTechnique::SetEyeWorldPos(const glm::vec3& EyeWorldPos)
{
	glUniform3f(m_eyeWorldPosLocation, EyeWorldPos.x, EyeWorldPos.y, EyeWorldPos.z);
}


void SHTechnique::SetMatSpecularIntensity(float Intensity)
{
	glUniform1f(m_matSpecularIntensityLocation, Intensity);
}

void SHTechnique::SetMatSpecularPower(float Power)
{
	glUniform1f(m_matSpecularPowerLocation, Power);
}

void SHTechnique::SetSpotLights(uint NumLights, const SpotLight* pLights)
{
	glUniform1i(m_numSpotLightsLocation, NumLights);

	for (uint i = 0; i < NumLights; i++) {
		glUniform3f(m_spotLightsLocation[i].Color, pLights[i].m_color.x, pLights[i].m_color.y, pLights[i].m_color.z);
		glUniform1f(m_spotLightsLocation[i].AmbientIntensity, pLights[i].m_ambientIntensity);
		glUniform1f(m_spotLightsLocation[i].DiffuseIntensity, pLights[i].m_diffuseIntensity);
		glUniform3f(m_spotLightsLocation[i].Position, pLights[i].m_position.x, pLights[i].m_position.y, pLights[i].m_position.z);
		glm::vec3 Direction = pLights[i].m_direction;
		glm::normalize(Direction);
		glUniform3f(m_spotLightsLocation[i].Direction, Direction.x, Direction.y, Direction.z);
		glUniform1f(m_spotLightsLocation[i].Cutoff, cosf(glm::radians(pLights[i].m_cutoff)));
		glUniform1f(m_spotLightsLocation[i].Atten.Constant, pLights[i].Attenuation.Constant);
		glUniform1f(m_spotLightsLocation[i].Atten.Linear, pLights[i].Attenuation.Linear);
		glUniform1f(m_spotLightsLocation[i].Atten.Exp, pLights[i].Attenuation.Exp);
	}
}

void SHTechnique::SetDiffuseColor(const glm::vec3& diffuseColor)
{
	glUniform3f(m_materialLocation.diffuseColor, diffuseColor.x, diffuseColor.y, diffuseColor.z);
}

void SHTechnique::SetSpecularColor(const glm::vec3& specularColor)
{
	glUniform3f(m_materialLocation.specularColor, specularColor.x, specularColor.y, specularColor.z);
}

void SHTechnique::SetAmbientColor(const glm::vec3& ambientColor)
{
	glUniform3f(m_materialLocation.ambientColor, ambientColor.x, ambientColor.y, ambientColor.z);
}

void SHTechnique::SetShininess(const float& shininess)
{
	glUniform1f(m_materialLocation.shininess, shininess);
}
