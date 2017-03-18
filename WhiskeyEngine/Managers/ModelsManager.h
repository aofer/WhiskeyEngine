#pragma once
#include <unordered_map>
#include "ShaderManager.h"
#include "../Rendering/IRenderable.h"
#include "../Rendering/Models/Triangle.h"
#include "../Rendering/Models/Quad.h"
#include "../Rendering/Models/Cube.h"

//TODO turn into meshes cache

using namespace Rendering;

namespace Managers
{
	class ModelsManager
	{
	public:
		ModelsManager();
		~ModelsManager();

		void Update();
		void DeleteModel(const std::string& gameModelName);
		void AddModel(const std::string& gameModelName, IRenderable* gameObject);
		const IRenderable& GetModel(const std::string& gameModelName) const;

	private:
		std::map<std::string, IRenderable*> gameModelList;

	};
}
