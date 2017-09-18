#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "../Rendering/Lighting.h"

namespace Managers
{
	class ModelsManager;
}

namespace Rendering
{
	class FPSCamera;
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

		const std::vector<Rendering::BaseLight*>& GetLights() const;
		const std::vector<GameObject*>& GetGameObjectsFlat() const;

	private:
		void AddLight(Rendering::BaseLight* light);

	protected:
		std::vector<GameObject*> m_gameObjectsFlat;
		std::vector<Rendering::BaseLight*>	m_lights;
		GameScene::GameObject* m_pRoot;
		Rendering::FPSCamera* m_pActiveCamera;
		Managers::ModelsManager*	m_pModelsManager;
	};
}