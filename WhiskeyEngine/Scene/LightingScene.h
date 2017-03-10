#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "GameScene.h"
#include "../Rendering/LightingTechnique.h"

namespace Scene{


	class LightingScene : public GameScene
	{

	public:
		LightingScene();
		virtual ~LightingScene();

		virtual void Init() override;

		virtual void Update(float dt) override;
		virtual void Draw() override;

	private:
		Rendering::LightingTechnique m_lighting;
	};
}