#pragma once
#include "GameScene.h"
#include "../Managers/ModelsManager.h"
#include "../Managers/InputManager.h"
#include "../Rendering/Camera.h"


namespace Scene
{
	GameScene::GameScene(Managers::ModelsManager* modelsManager)
	{
		m_pModelsManager = modelsManager;
	}

	void GameScene::SetModelsManager(Managers::ModelsManager* manager)
	{
		m_pModelsManager = manager;
	}

	GameScene::GameScene()
	{
		m_pActiveCamera = new Camera();
		Managers::InputManager::getInstance().AddInputListener(m_pActiveCamera);
	}

	GameScene::~GameScene()
	{

	}

	const std::vector<Rendering::BaseLight*>& GameScene::GetLights() const
	{
		return m_lights;
	}

	void GameScene::AddLight(Rendering::BaseLight* light)
	{
		m_lights.push_back(light);
	}

	const std::vector<GameObject*>& GameScene::GetGameObjectsFlat() const
	{
		return m_gameObjectsFlat;
	}
}

