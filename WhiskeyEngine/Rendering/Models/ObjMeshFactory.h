#pragma once
#include "IMeshFactory.h"
#include <Importer.hpp> 
#include <scene.h>       // Output data structure
#include <postprocess.h> // Post processing flags

namespace Rendering
{
	namespace Models
	{
		class ObjMeshFactory : public IMeshFactory
		{
			friend class SimpleMesh;
		public:
			virtual SimpleMesh* CreateMesh(const std::string& path);

		private:
			SimpleMesh* InitFromScene(const aiScene* pScene, const std::string& Filename);
			void InitMesh(unsigned int Index, const aiMesh* paiMesh, SimpleMesh* mesh);
		};
	}
}

