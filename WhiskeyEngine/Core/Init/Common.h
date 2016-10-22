#pragma once
#include <iostream>
#include <fstream>
//#include <Windows.h>

#define INVALID_OGL_VALUE 0xffffffff
#define INVALID_UNIFORM_LOCATION 0xffffffff

#define GLCheckError() (glGetError() == GL_NO_ERROR)
#define GLCheckError2() glGetError()
#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;
#define SNPRINTF _snprintf_s


static std::string readFileIntoString(const std::string& filename)
{

	std::string content;
	std::ifstream file(filename, std::ios::in);

	if (!file.good()){
		std::cout << "Can't read file " << filename.c_str() << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	content.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&content[0], content.size());
	file.close();

	return content;
}