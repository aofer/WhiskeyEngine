#pragma once

#include "RenderingTechnique.h"
#include "Lighting.h"

namespace Rendering
{

	class SHTechnique : public Technique {
	public:

		static const unsigned int MAX_SPOT_LIGHTS = 2;

		SHTechnique();

		virtual bool Init();

		void SetWVP(const glm::mat4& WVP);
		void SetWorldMatrix(const glm::mat4& world);
		void SetTextureUnit(unsigned int TextureUnit);
		void SetSpotLights(unsigned int NumLights, const SpotLight* pLights);
		void SetEyeWorldPos(const glm::vec3& EyeWorldPos);
		void SetMatSpecularIntensity(float Intensity);
		void SetMatSpecularPower(float Power);
		void SetCoefficients(glm::vec3 coeff[]);

		void SetDiffuseColor(const glm::vec3& diffuseColor);
		void SetSpecularColor(const glm::vec3& specularColor);
		void SetAmbientColor(const glm::vec3& ambientColor);
		void SetShininess(const float& shininess);



	protected:

		GLuint m_WVPLocation;

		GLuint m_WorldMatrixLocation;
		GLuint m_samplerLocation;
		GLuint m_eyeWorldPosLocation;
		GLuint m_matSpecularIntensityLocation;
		GLuint m_matSpecularPowerLocation;
		GLuint m_numSpotLightsLocation;
		GLuint m_shCoeffLocation;

		struct {
			GLuint Color;
			GLuint AmbientIntensity;
			GLuint DiffuseIntensity;
			GLuint Position;
			GLuint Direction;
			GLuint Cutoff;
			struct {
				GLuint Constant;
				GLuint Linear;
				GLuint Exp;
			} Atten;
		} m_spotLightsLocation[MAX_SPOT_LIGHTS];

		struct 
		{
			GLuint diffuseColor;
			GLuint specularColor;
			GLuint ambientColor;
			GLuint shininess;
		} m_materialLocation;

	};

}
