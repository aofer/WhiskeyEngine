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

	void GameScene::setModelsManager(Managers::ModelsManager* manager)
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
}

