#pragma once
#include <vector>
#include <iostream>
#include <GL\glew.h>
#include "VertexFormat.h"

namespace Rendering
{

	class IRenderable
	{
	public:
		virtual ~IRenderable() = 0;

		virtual void Draw() = 0;
		virtual void Update() = 0;
		virtual void SetProgram(GLuint shaderName) = 0;
		virtual void Destroy() = 0;

		virtual GLuint GetVao() const = 0;
		virtual const std::vector<GLuint> GetVbos() const = 0;

	};

	inline IRenderable::~IRenderable()
	{
	}
}
