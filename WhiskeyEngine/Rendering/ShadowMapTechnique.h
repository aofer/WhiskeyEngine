#pragma once

#include "RenderingTechnique.h"
#include "../Core/Init/Common.h"
#include <glm/glm.hpp>

namespace Rendering
{
	class ShadowMapTechnique : public Technique {

	public:

		ShadowMapTechnique();

		virtual bool Init();

		void SetWVP(const glm::mat4& WVP);
		void SetTextureUnit(unsigned int TextureUnit);
	private:

		GLuint m_WVPLocation;
		GLuint m_textureLocation;
	};

}
