#pragma once
#include <string>

namespace Rendering
{
	namespace Models
	{
		class SimpleMesh;

		class IMeshFactory
		{

		public:

			virtual SimpleMesh* CreateMesh(const std::string& path) = 0;
		};

	}
}