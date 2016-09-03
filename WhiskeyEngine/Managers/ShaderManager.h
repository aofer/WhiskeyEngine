#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <GL\glew.h>


namespace Managers
{

	class ShaderManager
	{

	public:

		ShaderManager(void);
		~ShaderManager(void);

		void CreateProgram(const std::string& shaderName,
			const std::string& VertexShaderFilename,
			const std::string& FragmentShaderFilename);

		static const GLuint GetShader(const std::string&);
		void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);

	private:

		std::string ReadShader(const std::string& filename);
		GLuint CreateShader(GLenum shaderType,
			const std::string& source,
			const std::string& shaderName);

		static std::map<std::string, GLuint> programs;
	};
}