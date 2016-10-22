#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "GameScene.h"
#include "../Rendering/LightingTechnique.h"
#include "../Rendering/ShadowMapTechnique.h"
#include "../Rendering/ShadowMapFbo.h"

namespace Rendering
{
	namespace Models
	{
		class Mesh;
	}
}

namespace Scene{


	class ShadowMapDebugScene : public GameScene
	{

	public:
		ShadowMapDebugScene();
		virtual ~ShadowMapDebugScene();

		virtual void init() override;

		virtual void update(float dt) override;
		virtual void draw() override;

	private:
		Rendering::ShadowMapTechnique	m_shadowMapTech;
		ShadowMapFBO					m_shadowMapFBO;
		GameObject*						m_pQuad;

		Rendering::SpotLight			m_spotLight;

		void shadowMapPass();
		void renderPass();
	};
}