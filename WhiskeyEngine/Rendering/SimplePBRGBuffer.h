#pragma once
#include <GL/glew.h>

namespace Rendering
{

	class SimplePBRGBuffer
	{
	public:

		enum PBR_GBUFFER_TEXTURE_TYPE
		{
			TEXTURE_POSITION,
			TEXTURE_DIFFUSE,
			TEXTURE_METALLIC_ROUGHNESS_SPECULAR,
			TEXTURE_NORMAL,
			NUM_OF_TEXTURES
		};

		SimplePBRGBuffer();

		~SimplePBRGBuffer();

		bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

		void BindForGeometryPass();

		void BindForLightPass();

		void BindForFinalComposition();

		void BeginRender();

		//For testing
		void SetReadBuffer(PBR_GBUFFER_TEXTURE_TYPE type);

	private:
		GLuint m_fbo;
		GLuint m_outputTexture;
		GLuint m_depthMap;
		GLuint m_gPassTextures[NUM_OF_TEXTURES];

	};

}

