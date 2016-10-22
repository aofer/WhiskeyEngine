#pragma once
#include "ShaderManager.h"
#include "ModelsManager.h"
#include "../Core/Init/IListener.h"
#include "../Rendering/Camera.h"
#include "../Rendering/LightingTechnique.h"

namespace Scene
{
	class GameObject;
	class GameScene;
}

namespace Managers
{
	class SceneManager : public Core::IListener

	{
	public:
		SceneManager();
		~SceneManager();

		virtual void NotifyBeginFrame();
		virtual void NotifyDisplayFrame();
		virtual void NotifyEndFrame();
		virtual void NotifyReshape(int width, int height, int previos_width, int previous_height);

	private:
		Managers::ShaderManager* shaderManager;
		Managers::ModelsManager* modelsManager;
		Scene::GameScene*			 m_activeScene;
		LightingTechnique m_lighting;
	};

}