#pragma once


namespace Scene
{
	class GameScene;
}

namespace Managers
{
	class ShaderManager;
	class ModelsManager;

	class RenderingSystem
	{
	private:
		Scene::GameScene*			 m_activeScene;
		//These will turn into shader\material cache and model cache
		Managers::ShaderManager* shaderManager;
		Managers::ModelsManager* modelsManager;

	public:

		void Init(void);
		void Update(float dt);
	};
}