#pragma once

#include "RenderingTechnique.h"
#include <glm\glm.hpp>
#include "Materials.h"

namespace Rendering
{

	class SimplePBRFinalCompositionTechnique : public Technique {
	
	public:

		SimplePBRFinalCompositionTechnique();
		virtual ~SimplePBRFinalCompositionTechnique() {}

		virtual bool Init();

		void SetWVP(const glm::mat4& WVP);
		void SetEyeWorldPosition(const glm::vec3& eyeWorldPos);
		void SetPositionTextureUnit(unsigned int textureUnit);
		void SetDiffuseTextureUnit(unsigned int textureUnit);
		void SetMetRoughSpecTextureUnit(unsigned int textureUnit);
		void SetNormalTextureUnit(unsigned int textureUnit);


	private:
		GLuint m_wVPLocation;
		GLuint m_eyeWorldPosLocation;
		GLuint m_positionTextureLocation;
		GLuint m_diffuseTextureLocation;
		GLuint m_metRoughSpecTextureLocation;
		GLuint m_normalTextureLocation;
	

	
	};

}
