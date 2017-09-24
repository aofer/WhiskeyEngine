#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "GameScene.h"
#include "../Rendering/SHTechnique.h"
#include "../Rendering/CubeMapCamera.h"
#include "../Core/Init/IInputListener.h"

namespace Scene{

	
	class SphericalHarmonicsScene : public GameScene, public Core::IInputListener
	{



	public:
		SphericalHarmonicsScene();
		virtual ~SphericalHarmonicsScene();

		virtual void Init() override;

		virtual void Update(float dt) override;
		virtual void Draw() override;

		void renderScene(glm::vec3 camPosition, glm::mat4 viewProjection, unsigned int coeffIndex);

		//overrides
		virtual void onKeyPressed(int key, int scancode);
		virtual void onKeyReleased(int key, int scancode);
		virtual void onKeyRepeated(int key, int scancode);
		void handleKey(int key);


	private:
		Rendering::SHTechnique m_shTech;
		GLuint m_EnvMapTexture;
		GLuint m_fboId;
		Rendering::CubeMapCamera* m_cubeCam;
		std::vector<glm::vec3> m_shCoeff[4];
		unsigned int m_numOfBounces;

	
		void sphericalHarmonicsFromTexture(GLuint cubeTexture,
			std::vector<glm::vec3> & output, const unsigned int order);

		void sphericalHarmonicsAdd(float * result, int order,
			const float * inputA, const float * inputB);

		void sphericalHarmonicsScale(float * result, int order,
			const float * input, float scale);
		
		void sphericalHarmonicsEvaluateDirection(float * result, int order,
			const glm::vec3 & dir);
		
		void initEnvironmentMapTexture();

		void initEnvironmentRendering();

		void renderEnvironmentMap(unsigned int coeffIndex);
		void bakeSphericalHarmonics();
	};
}