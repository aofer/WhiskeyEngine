#pragma once
#include <glm\glm.hpp>

	namespace Rendering
	{
		struct VertexFormat
		{

			glm::vec3 position;
			glm::vec4 color;
			glm::vec2 uv;
			glm::vec3 normal;

			VertexFormat(const glm::vec3 &iPos, const glm::vec4 &iColor)
			{
				position = iPos;
				color = iColor;
			}

			VertexFormat(const glm::vec3 &iPos, const glm::vec2 &iUV)
			{
				position = iPos;
				uv = iUV;
			}

			VertexFormat(const glm::vec3 &iPos, const glm::vec4 &iColor, const glm::vec2 &iUv)
			{
				position = iPos;
				color = iColor;
				uv = iUv;
			}

			VertexFormat(const glm::vec3 &iPos, const glm::vec4 &iColor, const glm::vec2 &iUv, const glm::vec3 &iNormal)
			{
				position = iPos;
				color = iColor;
				uv = iUv;
				normal = iNormal;
			}

			VertexFormat(const glm::vec3 &iPos, const glm::vec2 &iUv, const glm::vec3 &iNormal)
			{
				position = iPos;
				uv = iUv;
				normal = iNormal;
			}

			VertexFormat()
			{

			}

		};
	}
