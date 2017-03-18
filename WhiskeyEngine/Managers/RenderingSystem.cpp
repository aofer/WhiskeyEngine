#include "RenderingSystem.h"
#include "ModelsManager.h"
//TODO remove later
#include "../Scene/LightingScene.h"
#include "../Scene/ShadowMapDebugScene.h"
#include "../Scene/ShadowMapScene.h"
#include "../Scene/SkyboxScene.h"

using namespace Scene;

namespace Managers
{
	void RenderingSystem::Init(void)
	{
		modelsManager = new ModelsManager();
		m_activeScene = new SkyboxScene();
		m_activeScene->SetModelsManager(modelsManager);
		m_activeScene->Init();
	}

	void RenderingSystem::Update(float dt)
	{
		for (const auto& go : m_activeScene->GetGameObjectsFlat())
		{
			//RenderingGameComponent* rgc = go->GetComponent(Components::FamilyType::RENDERING);
			//rgc->Render();
		}
		
	}
}