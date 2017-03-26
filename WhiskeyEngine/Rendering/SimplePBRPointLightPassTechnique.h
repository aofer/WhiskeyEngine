#pragma once

#include "RenderingTechnique.h"
#include <glm\glm.hpp>
#include "Materials.h"

namespace Rendering
{
	struct PointLight;

	class SimplePBRPointLightPassTechnique : public Technique {
	
	public:

		SimplePBRPointLightPassTechnique();
		virtual ~SimplePBRPointLightPassTechnique() {}

		virtual bool Init();

		void SetWVP(const glm::mat4& WVP);
		void SetEyeWorldPosition(const glm::vec3& eyeWorldPos);
		void SetPositionTextureUnit(unsigned int textureUnit);
		void SetDiffuseTextureUnit(unsigned int textureUnit);
		void SetMetRoughSpecTextureUnit(unsigned int textureUnit);
		void SetNormalTextureUnit(unsigned int textureUnit);
		void SetPointLightParams(PointLight* pointLight);
		void SetScreenSize(unsigned int width, unsigned int height);

	private:
		GLuint m_wVPLocation;
		GLuint m_eyeWorldPosLocation;
		GLuint m_positionTextureLocation;
		GLuint m_diffuseTextureLocation;
		GLuint m_metRoughSpecTextureLocation;
		GLuint m_normalTextureLocation;
		GLuint m_screenSize;

		struct {
			GLuint color;
			GLuint ambientIntensity;
			GLuint diffuseIntensity;
			GLuint position;
			struct {
				GLuint constant;
				GLuint linear;
				GLuint exp;
			} attenuation;
		} m_pointLightsLocation;
	

	
	};

}
