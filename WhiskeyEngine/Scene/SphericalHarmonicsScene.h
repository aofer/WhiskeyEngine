#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "GameScene.h"
#include "../Rendering/LightingTechnique.h"
#include "../Rendering/CubeMapCamera.h"

namespace Scene{


	class SphericalHarmonicsScene : public GameScene
	{

	public:
		SphericalHarmonicsScene();
		virtual ~SphericalHarmonicsScene();

		virtual void Init() override;

		virtual void Update(float dt) override;
		virtual void Draw() override;

		void renderScene();


	private:
		Rendering::LightingTechnique m_lighting;
		GLuint m_EnvMapTexture;
		GLuint m_fboId;
		Rendering::CubeMapCamera* m_cubeCam;

		void initEnvironmentMapTexture();

		void initEnvironmentRendering();

		void renderEnvironmentMap();
	};
}