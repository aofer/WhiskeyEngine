#pragma once
#include "GameScene.h"
#include "../Rendering/SimplePBRGeometryPassTechnique.h"
#include "../Rendering/SimplePBRPointLightPassTechnique.h"
#include "../Rendering/LightingTechnique.h"
#include "../Rendering/SimplePBRGBuffer.h"

namespace Scene{


	class DeferredPBRTestScene : public GameScene
	{

	public:
		DeferredPBRTestScene();
		virtual ~DeferredPBRTestScene();

		virtual void Init() override;

		virtual void Update(float dt) override;
		virtual void Draw() override;

	private:


		Rendering::SimplePBRGeometryPassTechnique* m_geometryPassTech;
		Rendering::SimplePBRPointLightPassTechnique* m_pointLightTech;
		Rendering::LightingTechnique* m_lightingTech;
		Rendering::SimplePBRGBuffer* m_gBuffer;

		GameObject*						m_pQuad;
		GameObject*						m_pGround;
		GameObject*						m_spinningBox;


		void GeometryPass();
		void PointLightPass();
		void CompositionPass();
		void RenderGBufferToScreen();
	};
}