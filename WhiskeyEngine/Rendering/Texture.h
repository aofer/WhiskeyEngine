#pragma once

#include <string>
#include <GL/glew.h>

namespace Rendering 
{
	class Texture
	{
	public:
		Texture(){}
		Texture(const std::string& FileName, GLenum TextureTarget = GL_TEXTURE_2D);

		bool Load();

		void Bind(GLenum TextureUnit);

	private:
		std::string m_fileName;
		GLenum m_textureTarget;
		GLuint m_textureObj;

	};
}
