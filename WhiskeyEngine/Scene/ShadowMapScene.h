#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "GameScene.h"
#include "../Rendering/ShadowMapLightingTechnique.h"
#include "../Rendering/ShadowMapTechnique.h"
#include "../Rendering/ShadowMapFbo.h"
#include "../Rendering/Lighting.h"
#include "../Rendering/Camera.h"

namespace Scene{


	class ShadowMapScene : public GameScene
	{

	public:
		ShadowMapScene();
		virtual ~ShadowMapScene();

		virtual void init() override;

		virtual void update(float dt) override;
		virtual void draw() override;

	private:
		Rendering::ShadowMapLightingTechnique	m_lightingTech;
		Rendering::ShadowMapTechnique	m_shadowMapTech;
		ShadowMapFBO					m_shadowMapFBO;

		Rendering::SpotLight			m_spotLight;
		Rendering::Camera				m_spotCamera;

		void shadowMapPass();
		void renderPass();
	};
}