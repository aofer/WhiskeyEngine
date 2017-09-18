#pragma once
#include <GL/glew.h>

namespace Rendering
{

	class BlinnPhongGbuffer
	{
	public:

		enum GBUFFER_TEXTURE_TYPE
		{
			TEXTURE_POSITION,
			TEXTURE_DIFFUSE,
			TEXTURE_NORMAL,
			NUM_OF_TEXTURES
		};

		BlinnPhongGbuffer();

		~BlinnPhongGbuffer();

		bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

		void BindForGeometryPass();

		void BindForLightPass();

		void BindForFinalComposition();

		void BeginRender();

	private:
		GLuint m_fbo;
		GLuint m_outputTexture;
		GLuint m_depthMap;
		GLuint m_gPassTextures[NUM_OF_TEXTURES];

	};

}

