#pragma once

#include "RenderingTechnique.h"
#include <glm\glm.hpp>
#include "Materials.h"

namespace Rendering
{

	class SimplePBRGeometryPassTechnique : public Technique {
	
	public:

		SimplePBRGeometryPassTechnique();
		virtual ~SimplePBRGeometryPassTechnique() {}

		virtual bool Init();

		void SetWVP(const glm::mat4& WVP);
		void SetWorldMatrix(const glm::mat4& WVP);
		void SetMaterial(const SimplePBRMaterial& material);
		//void SetColorTextureUnit(unsigned int TextureUnit);

	private:
		GLuint m_wVPLocation;
		GLuint m_worldMatrixLocation;
		//GLuint m_colorTextureUnitLocation;

		struct
		{
			GLuint m_diffuseLocation;
			GLuint m_metallicLocation;
			GLuint m_roughnessLocation;
			GLuint m_specularLocation;
		} m_materialLocation;

	
	};

}
