#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "GameScene.h"
#include "../Rendering/ShadowMapLightingTechnique.h"
#include "../Rendering/ShadowMapTechnique.h"
#include "../Rendering/ShadowMapFbo.h"
#include "../Rendering/Lighting.h"
#include "../Rendering/Camera.h"
#include "../Core/Init/IInputListener.h"


namespace Scene{


	class ShadowMapScene : public GameScene, Core::IInputListener
	{

	public:
		ShadowMapScene();
		virtual ~ShadowMapScene();

		virtual void init() override;

		virtual void update(float dt) override;
		virtual void draw() override;

		//support keyboard controls
		virtual void onKeyPressed(int key, int scancode);
		virtual void onKeyReleased(int key, int scancode);

	private:
		Rendering::ShadowMapLightingTechnique	m_lightingTech;
		Rendering::ShadowMapTechnique	m_shadowMapTech;
		ShadowMapFBO					m_shadowMapFBO;

		Rendering::SpotLight			m_spotLight;
		Rendering::Camera				m_spotCamera;
		GameObject*						m_pQuad;
		GameObject*						m_pGround;
		GameObject*						m_spinningBox;
		bool							m_drawShadowMap;

		void shadowMapPass();
		void renderPass();
		void renderShadowMap();
	};
}