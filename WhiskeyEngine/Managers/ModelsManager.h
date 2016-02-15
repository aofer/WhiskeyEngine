#pragma once
#include <unordered_map>
#include "ShaderManager.h"
#include "../Rendering/IGameObject.h"
#include "../Rendering/Models/Triangle.h"
#include "../Rendering/Models/Quad.h"
#include "../Rendering/Models/Cube.h"

using namespace Rendering;

namespace Managers
{
	class ModelsManager
	{
	public:
		ModelsManager();
		~ModelsManager();

		void Draw();
		virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);
		void Update();
		void DeleteModel(const std::string& gameModelName);
		const IGameObject& GetModel(const std::string& gameModelName) const;

	private:
		std::map<std::string, IGameObject*> gameModelList;

	};
}
