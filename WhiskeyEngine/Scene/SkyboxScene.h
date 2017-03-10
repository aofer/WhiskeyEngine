#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "GameScene.h"
#include "../Rendering/LightingTechnique.h"
#include "Components/SkyBox.h"

namespace Scene{


	class SkyboxScene : public GameScene
	{

	public:
		SkyboxScene();
		virtual ~SkyboxScene();

		virtual void Init() override;

		virtual void Update(float dt) override;
		virtual void Draw() override;

	private:
		Rendering::LightingTechnique m_lighting;
		Scene::Components::SkyBox* m_pSkybox;
		GameObject*				m_tempSkyBoxObject;
	};
}