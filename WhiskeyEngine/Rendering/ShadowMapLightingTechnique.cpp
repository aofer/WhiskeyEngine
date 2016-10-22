#include "ShadowMapLightingTechnique.h"


namespace Rendering
{
	ShadowMapLightingTechnique::ShadowMapLightingTechnique()
	{

	}

	bool ShadowMapLightingTechnique::Init()
	{
		if (!Technique::Init()) {
			return false;
		}

		if (!AddShader(GL_VERTEX_SHADER, "Shaders\\ShadowMapLighting_vs.glsl")) {
			return false;
		}

		if (!AddShader(GL_FRAGMENT_SHADER, "Shaders\\ShadowMapLighting_fs.glsl")) {
			return false;
		}

		if (!Finalize()) {
			return false;
		}

		m_WVPLocation = GetUniformLocation("gWVP");
		m_WorldMatrixLocation = GetUniformLocation("gWorld");
		m_samplerLocation = GetUniformLocation("gSampler");
		m_shadowMapLocation = GetUniformLocation("gShadowMap");
		m_eyeWorldPosLocation = GetUniformLocation("gEyeWorldPos");
		m_dirLightLocation.Color = GetUniformLocation("gDirectionalLight.Base.Color");
		m_dirLightLocation.AmbientIntensity = GetUniformLocation("gDirectionalLight.Base.AmbientIntensity");
		m_dirLightLocation.Direction = GetUniformLocation("gDirectionalLight.Direction");
		m_dirLightLocation.DiffuseIntensity = GetUniformLocation("gDirectionalLight.Base.DiffuseIntensity");
		m_matSpecularIntensityLocation = GetUniformLocation("gMatSpecularIntensity");
		m_matSpecularPowerLocation = GetUniformLocation("gSpecularPower");
		m_numPointLightsLocation = GetUniformLocation("gNumPointLights");
		m_numSpotLightsLocation = GetUniformLocation("gNumSpotLights");

		if (m_dirLightLocation.AmbientIntensity == INVALID_UNIFORM_LOCATION ||
			m_WVPLocation == INVALID_UNIFORM_LOCATION ||
			m_WorldMatrixLocation == INVALID_UNIFORM_LOCATION ||
			m_samplerLocation == INVALID_UNIFORM_LOCATION ||
			m_shadowMapLocation == INVALID_UNIFORM_LOCATION ||
			m_eyeWorldPosLocation == INVALID_UNIFORM_LOCATION ||
			m_dirLightLocation.Color == INVALID_UNIFORM_LOCATION ||
			m_dirLightLocation.DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
			m_dirLightLocation.Direction == INVALID_UNIFORM_LOCATION ||
			m_matSpecularIntensityLocation == INVALID_UNIFORM_LOCATION ||
			m_matSpecularPowerLocation == INVALID_UNIFORM_LOCATION ||
			m_numPointLightsLocation == INVALID_UNIFORM_LOCATION ||
			m_numSpotLightsLocation == INVALID_UNIFORM_LOCATION) {
			return false;
		}

		for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_pointLightsLocation); i++) {
			char Name[128];
			memset(Name, 0, sizeof(Name));
			SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.Color", i);
			m_pointLightsLocation[i].Color = GetUniformLocation(Name);

			SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.AmbientIntensity", i);
			m_pointLightsLocation[i].AmbientIntensity = GetUniformLocation(Name);

			SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Position", i);
			m_pointLightsLocation[i].Position = GetUniformLocation(Name);

			SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Base.DiffuseIntensity", i);
			m_pointLightsLocation[i].DiffuseIntensity = GetUniformLocation(Name);

			SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Constant", i);
			m_pointLightsLocation[i].Atten.Constant = GetUniformLocation(Name);

			SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Linear", i);
			m_pointLightsLocation[i].Atten.Linear = GetUniformLocation(Name);

			SNPRINTF(Name, sizeof(Name), "gPointLights[%d].Atten.Exp", i);
			m_pointLightsLocation[i].Atten.Exp = GetUniformLocation(Name);

			if (m_pointLightsLocation[i].Color == INVALID_UNIFORM_LOCATION ||
				m_pointLightsLocation[i].AmbientIntensity == INVALID_UNIFORM_LOCATION ||
				m_pointLightsLocation[i].Position == INVALID_UNIFORM_LOCATION ||
				m_pointLightsLocation[i].DiffuseIntensity == INVALID_UNIFORM_LOCATION ||
				m_pointLightsLocation[i].Atten.Constant == INVALID_UNIFORM_LOCATION ||
				m_pointLightsLocation[i].Atten.Linear == INVALID_UNIFORM_LOCATION ||
				m_pointLightsLocation[i].Atten.Exp == INVALID_UNIFORM_LOCATION) {
				return false;
			}
		}

		for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_spotLightsLocation); i++) {
			char Name[128];
			memset(Name, 0, sizeof(Name));
			SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.Color", i);
			m_spotLightsLocation[i].Color = GetUniformLocation(Name);

			SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.AmbientIntensity", i);
			m_spotLightsLocation[i].AmbientIntensity = GetUniformLocation(Name);

			SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Position", i);
			m_spotLightsLocation[i].Position = GetUniformLocation(Name);

			SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Direction", i);
			m_spotLightsLocation[i].Direction = GetUniformLocation(Name);

			SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Cutoff", i);
			m_spotLightsLocation[i].Cutoff = GetUniformLocation(Name);

			SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Base.DiffuseIntensity", i);
			m_spotLightsLocation[i].DiffuseIntensity = GetUniformLocation(Name);

			SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Constant", i);
			m_spotLightsLocation[i].Atten.Constant = GetUniformLocation(Name);

			SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Linear", i);
			m_spotLightsLocation[i].Atten.Linear = GetUniformLocation(Name);

			SNPRINTF(Name, sizeof(Name), "gSpotLights[%d].Base.Atten.Exp", i);
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

	void ShadowMapLightingTechnique::SetShadowMapTextureUnit(uint TextureUnit)
	{
		glUniform1i(m_shadowMapLocation, TextureUnit);
	}


}
