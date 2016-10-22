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

		virtual void init() override;

		virtual void update(float dt) override;
		virtual void draw() override;

	private:
		Rendering::LightingTechnique m_lighting;
	};
}