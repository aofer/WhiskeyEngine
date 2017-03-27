#include "SimplePBRGBuffer.h"
#include "../Core/Init/Common.h"

namespace Rendering
{
	SimplePBRGBuffer::SimplePBRGBuffer()
	{
		m_fbo = 0;
		m_depthMap = 0;
		m_outputTexture = 0;
		memset(m_gPassTextures, 0, sizeof(m_gPassTextures));
	}

	bool SimplePBRGBuffer::Init(unsigned int WindowWidth, unsigned int WindowHeight)
	{
		// Create the FBO
		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

		// Create the depth buffer
		glGenTextures(1, &m_depthMap);
		glBindTexture(GL_TEXTURE_2D, m_depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, WindowWidth, WindowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthMap, 0);

		// final composition
		glGenTextures(1, &m_outputTexture);
		glBindTexture(GL_TEXTURE_2D, m_outputTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WindowWidth, WindowHeight, 0, GL_RGB, GL_FLOAT, nullptr);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, m_outputTexture, 0);

		//generate the textures
		glGenTextures(NUM_OF_TEXTURES, m_gPassTextures);

		for (unsigned int i = 0; i < NUM_OF_TEXTURES; i++) {
			glBindTexture(GL_TEXTURE_2D, m_gPassTextures[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, WindowWidth, WindowHeight, 0, GL_RGB, GL_FLOAT, nullptr);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_gPassTextures[i], 0);
		}

		GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if (Status != GL_FRAMEBUFFER_COMPLETE) {
			printf("FB error, status: 0x%x\n", Status);
			return false;
		}

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		return true;
	}

	void SimplePBRGBuffer::BindForGeometryPass()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
		GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0,
			GL_COLOR_ATTACHMENT1,
			GL_COLOR_ATTACHMENT2,
			GL_COLOR_ATTACHMENT3};
		glDrawBuffers(4, drawBuffers);
	}

	void SimplePBRGBuffer::BindForLightPass()
	{
		glDrawBuffer(GL_COLOR_ATTACHMENT4);

		for (int i = 0; i < NUM_OF_TEXTURES; ++i)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_gPassTextures[TEXTURE_POSITION + i]);
		}
	}

	void SimplePBRGBuffer::BindForFinalComposition()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
		glReadBuffer(GL_COLOR_ATTACHMENT4);
	}

	void SimplePBRGBuffer::BeginRender()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
		glDrawBuffer(GL_COLOR_ATTACHMENT4);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void SimplePBRGBuffer::SetReadBuffer(PBR_GBUFFER_TEXTURE_TYPE type)
	{
		glReadBuffer(GL_COLOR_ATTACHMENT0 + type);
	}

}