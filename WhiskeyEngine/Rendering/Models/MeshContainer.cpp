#include "MeshContainer.h"
#include "Mesh.h"
namespace Rendering
{
	namespace Models
	{
		const std::vector<Mesh*>& Rendering::Models::MeshContainer::GetMeshes() const
		{
			return m_meshes;
		}

	}
}
