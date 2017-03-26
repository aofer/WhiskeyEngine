#pragma once
#include "GameScene.h"
#include "../Rendering/SimplePBRGeometryPassTechnique.h"
#include "../Rendering/LightingTechnique.h"
#include "../Rendering/SimplePBRGBuffer.h"

namespace Scene{


	class GeometryPassTestScene : public GameScene
	{

	public:
		GeometryPassTestScene();
		virtual ~GeometryPassTestScene();

		virtual void Init() override;

		virtual void Update(float dt) override;
		virtual void Draw() override;

	private:


		Rendering::SimplePBRGeometryPassTechnique* m_geometryPassTech;
		Rendering::LightingTechnique* m_lightingTech;
		Rendering::SimplePBRGBuffer* m_gBuffer;

		GameObject*						m_pQuad;
		GameObject*						m_pGround;
		GameObject*						m_spinningBox;


		void GeometryPass();
		void RenderGBufferToScreen();
	};
}