#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "GameScene.h"
#include "../Rendering/LightingTechnique.h"

namespace Scene{


	class SphericalHarmonicsScene : public GameScene
	{

	public:
		SphericalHarmonicsScene();
		virtual ~SphericalHarmonicsScene();

		virtual void Init() override;

		virtual void Update(float dt) override;
		virtual void Draw() override;

	private:
		Rendering::LightingTechnique m_lighting;
		GLuint m_EnvMapTexture;

		void createEnvironmentMapTexture();
	};
}