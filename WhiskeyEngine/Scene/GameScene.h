#pragma once
#include <vector>
#include <glm\glm.hpp>

namespace Managers
{
	class ModelsManager;
}

namespace Rendering
{
	class Camera;
}
namespace Scene{

	class GameObject;

	class GameScene 
	{

	public:
		GameScene(Managers::ModelsManager* modelsManager);
		GameScene();
		void SetModelsManager(Managers::ModelsManager* manager);
		virtual ~GameScene();

		virtual void Init() = 0;

		virtual void Update(float dt) = 0;
		virtual void Draw() = 0;

	protected:
		std::vector<GameObject*> m_gameObjectsFlat;
		GameScene::GameObject* m_pRoot;
		Rendering::Camera* m_pActiveCamera;
		Managers::ModelsManager*	m_pModelsManager;
	};
}