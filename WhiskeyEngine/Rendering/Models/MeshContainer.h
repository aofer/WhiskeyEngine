#pragma once
#include "../../Scene/Components/GameComponent.h"
#include <vector>
namespace Rendering
{
	namespace Models
	{
		class Mesh;

		class MeshContainer : public Scene::Components::GameComponent
		{
		private:

			std::vector<Mesh*> m_meshes;

		public:

			const std::vector<Mesh*>& GetMeshes() const;

		};
	}
}
