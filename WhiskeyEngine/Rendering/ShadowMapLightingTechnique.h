#pragma once

#include "LightingTechnique.h"
#include "Lighting.h"
#include "ShadowMapFbo.h"
#include "../Core/Init/Common.h"
//#include "shadow_map_technique.h"

namespace Rendering
{

	class ShadowMapLightingTechnique : public LightingTechnique {
	public:


		ShadowMapLightingTechnique();

		virtual bool Init();

		void SetShadowMapTextureUnit(uint TextureUnit);
		void SetLightWVP(const glm::mat4& LightWVP);

	private:

		GLuint m_shadowMapLocation;
		GLuint m_LightWVPLocation;

	};

}
