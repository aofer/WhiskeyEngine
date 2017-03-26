#pragma once



#include "RenderingTechnique.h"
#include "Lighting.h"
#include "ShadowMapFbo.h"
//#include "shadow_map_technique.h"

namespace Rendering
{

	class LightingTechnique : public Technique {
	public:

		static const unsigned int MAX_POINT_LIGHTS = 2;
		static const unsigned int MAX_SPOT_LIGHTS = 2;

		LightingTechnique();

		virtual bool Init();

		void SetWVP(const glm::mat4& WVP);
	//	void SetLightWVP(const glm::mat4& LightWVP);
		void SetWorldMatrix(const glm::mat4& world);
		void SetTextureUnit(unsigned int TextureUnit);
		void SetDirectionalLight(const DirectionalLight& Light);
		void SetPointLights(unsigned int NumLights, const PointLight* pLights);
		void SetSpotLights(unsigned int NumLights, const SpotLight* pLights);
		void SetEyeWorldPos(const glm::vec3& EyeWorldPos);
		void SetMatSpecularIntensity(float Intensity);
		void SetMatSpecularPower(float Power);

	protected:

		GLuint m_WVPLocation;
		//GLuint m_LightWVPLocation;
		GLuint m_WorldMatrixLocation;
		GLuint m_samplerLocation;
		GLuint m_eyeWorldPosLocation;
		GLuint m_matSpecularIntensityLocation;
		GLuint m_matSpecularPowerLocation;
		GLuint m_numPointLightsLocation;
		GLuint m_numSpotLightsLocation;

		struct {
			GLuint Color;
			GLuint AmbientIntensity;
			GLuint DiffuseIntensity;
			GLuint Direction;
		} m_dirLightLocation;

		struct {
			GLuint Color;
			GLuint AmbientIntensity;
			GLuint DiffuseIntensity;
			GLuint Position;
			struct {
				GLuint Constant;
				GLuint Linear;
				GLuint Exp;
			} Atten;
		} m_pointLightsLocation[MAX_POINT_LIGHTS];

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
	};

}
