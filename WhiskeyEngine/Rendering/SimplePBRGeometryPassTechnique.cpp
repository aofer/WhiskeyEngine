#include <limits.h>
#include <string.h>
#include "../Core/Init/Common.h"
#include "SimplePBRGeometryPassTechnique.h"

namespace Rendering
{
	SimplePBRGeometryPassTechnique::SimplePBRGeometryPassTechnique()
	{
	}

	bool SimplePBRGeometryPassTechnique::Init()
	{
		if (!Technique::Init()) {
			return false;
		}

		if (!AddShader(GL_VERTEX_SHADER, "Shaders\\PBRGPass_vs.glsl")) {
			return false;
		}

		if (!AddShader(GL_FRAGMENT_SHADER, "Shaders\\PBRGPass_fs.glsl")) {
			return false;
		}

		if (!Finalize()) {
			return false;
		}

		m_wVPLocation = GetUniformLocation("gWVP");
		m_worldMatrixLocation = GetUniformLocation("gWorld");
		m_materialLocation.m_diffuseLocation = GetUniformLocation("gMaterial.diffuse");
		m_materialLocation.m_metallicLocation = GetUniformLocation("gMaterial.metallic");
		m_materialLocation.m_roughnessLocation = GetUniformLocation("gMaterial.roughness");
		m_materialLocation.m_specularLocation = GetUniformLocation("gMaterial.specular");
		//m_colorTextureUnitLocation = GetUniformLocation("gColorMap");

		if (m_wVPLocation == INVALID_UNIFORM_LOCATION ||
			m_worldMatrixLocation == INVALID_UNIFORM_LOCATION ||
			m_materialLocation.m_diffuseLocation == INVALID_UNIFORM_LOCATION ||
			m_materialLocation.m_metallicLocation == INVALID_UNIFORM_LOCATION ||
			m_materialLocation.m_roughnessLocation == INVALID_UNIFORM_LOCATION ||
			m_materialLocation.m_specularLocation == INVALID_UNIFORM_LOCATION
			/*m_colorTextureUnitLocation == INVALID_UNIFORM_LOCATION*/) {
			return false;
		}
		return true;
	}

	void SimplePBRGeometryPassTechnique::SetWVP(const glm::mat4& WVP)
	{
		glUniformMatrix4fv(m_wVPLocation, 1, GL_FALSE, &WVP[0][0]);
	}


	void SimplePBRGeometryPassTechnique::SetWorldMatrix(const glm::mat4& WorldInverse)
	{
		glUniformMatrix4fv(m_worldMatrixLocation, 1, GL_FALSE, &WorldInverse[0][0]);
	}


	void SimplePBRGeometryPassTechnique::SetMaterial(const SimplePBRMaterial& material)
	{
		glUniform3fv(m_materialLocation.m_diffuseLocation, 1, &material.diffuseColor[0]);
		//glUniform3f(m_materialLocation.m_diffuseLocation, material.diffuseColor.x, material.diffuseColor.y, material.diffuseColor.z);
		glUniform1f(m_materialLocation.m_metallicLocation, material.metallic);
		glUniform1f(m_materialLocation.m_roughnessLocation, material.roughness);
		glUniform1f(m_materialLocation.m_specularLocation, material.specular);
	}

	//void SimplePBRGeometryPassTechnique::SetColorTextureUnit(unsigned int TextureUnit)
	//{
	//	glUniform1i(m_colorTextureUnitLocation, TextureUnit);
	//}


}

