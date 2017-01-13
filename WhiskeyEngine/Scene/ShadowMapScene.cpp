#include "ShadowMapScene.h"
#include "../Core/Init/Common.h"

#include "../Rendering/Models/Mesh.h"
#include "GameObject.h"
#include "../Managers/ModelsManager.h"
#include "../Rendering/Pipeline.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW\glfw3.h> //TODO remove this dependency
#include "../Managers/InputManager.h"

using namespace Rendering;

namespace Scene
{
	ShadowMapScene::ShadowMapScene() : GameScene(), m_drawShadowMap(false)
	{
		m_pQuad = nullptr;
		Managers::InputManager::getInstance().AddInputListener(this); //TODO do it more elgenatly 
	}
	ShadowMapScene::~ShadowMapScene()
	{
		
	}

	void ShadowMapScene::init()
	{

		m_pActiveCamera->setPosition(glm::vec3(0.0, 2.0f, -8.0));
		m_pActiveCamera->setLookAt(glm::vec3(0.0, 2.0, 0.0));

		int test = GLCheckError();
		if (!m_lightingTech.Init())
		{
			printf("Error initializing lighting technique\n");
		}

		if (!m_shadowMapFBO.Init(WINDOW_WIDTH, WINDOW_HEIGHT)) {
			printf("Error initializing shadowMapFBO \n");
		}

		if (!m_shadowMapTech.Init()) {
			printf("Error initializing the shadow map technique\n");
		}

		m_lightingTech.Enable();

		m_lightingTech.SetTextureUnit(0);
		m_lightingTech.SetShadowMapTextureUnit(1);

		PointLight pl[1];
		pl[0].DiffuseIntensity = 0.055f;
		pl[0].AmbientIntensity = 0.05f;
		pl[0].Color = glm::vec3(0.8f, 0.7f, 1.0f);
		pl[0].Position = glm::vec3(2.0f, 2.0f, 0.0f);
		pl[0].Attenuation.Linear = 0.1f;

		m_lightingTech.SetPointLights(1, pl);


		m_spotLight.Color = glm::vec3(1.0, 1.0, 1.0);
		m_spotLight.DiffuseIntensity = 0.03f;
		m_spotLight.Direction = glm::vec3(-0.5, -10.0, -2.0);
		m_spotLight.Attenuation.Linear = 0.1f;
		m_spotLight.AmbientIntensity = 0.001f;
		m_spotLight.Cutoff = 40.5f;
		m_spotLight.Position = glm::vec3(0.5, 8.0, 2.0);


		m_spotCamera.setPosition(m_spotLight.Position);
		m_spotCamera.setLookAt(glm::vec3(m_spotLight.Position + m_spotLight.Direction));


		m_lightingTech.SetSpotLights(1, &m_spotLight);


		Models::Mesh* quad = new Models::Mesh();

		if (!quad->Create("Assets\\quad.obj")) {
			printf("Error loading screen space quad");
		}
		m_pModelsManager->AddModel("quad", quad);
		m_pQuad = new GameObject();
		m_pQuad->setModel(quad);
		m_pQuad->setPosition(glm::vec3(0.0, 0.0, 1.0));
		m_pQuad->setScale(5.0f);

		Models::Mesh* groundMesh = new Models::Mesh();
		groundMesh->Create("Assets\\ground.obj");
		m_pModelsManager->AddModel("ground", groundMesh);
		m_pGround = new GameObject();
		m_pGround->setModel(groundMesh);
		m_pGround->setPosition(glm::vec3(0.0, 0.0, 0.0));
		m_pGround->setScale(1.0f);
		//m_gameObjectsFlat.push_back(m_pGround);

		Models::Mesh* spinningMesh = new Models::Mesh();
		spinningMesh->Create("Assets\\deer-obj.obj");
		m_pModelsManager->AddModel("spinning", spinningMesh);
		m_spinningBox = new GameObject();
		m_spinningBox->setModel(spinningMesh);
		m_spinningBox->setPosition(glm::vec3(0.0, 2.0, 0.0));
		m_spinningBox->setScale(0.15f);
		m_gameObjectsFlat.push_back(m_spinningBox);

		Models::Mesh* boxMesh = new Models::Mesh();
		boxMesh->Create("Assets\\box.obj");
		m_pModelsManager->AddModel("box", boxMesh);
		Scene::GameObject* box2 = new GameObject();
		box2->setModel(boxMesh);
		box2->setPosition(glm::vec3(3.0, 1.0, 0.0));
		box2->setScale(0.8f);
		m_gameObjectsFlat.push_back(box2);



	}

	void ShadowMapScene::update(float dt)
	{
		m_spinningBox->setOrientation(m_spinningBox->getOrientation()  *  glm::angleAxis(glm::degrees(0.5f* dt), glm::vec3(0.0f, 1.f, 0.f)));
	}

	void ShadowMapScene::draw()
	{
		shadowMapPass();

		renderPass();

		if (m_drawShadowMap)
		{
			renderShadowMap();
		}
	}


	void ShadowMapScene::shadowMapPass()
	{
		m_shadowMapFBO.BindForWriting();
		glClear(GL_DEPTH_BUFFER_BIT);

		m_shadowMapTech.Enable();

		m_shadowMapTech.SetWVP(m_spotCamera.getProjection() * m_spotCamera.getView());

		for (auto nodeIter = m_gameObjectsFlat.begin(); nodeIter != m_gameObjectsFlat.end(); nodeIter++)
		{
			m_shadowMapTech.SetWorldMatrix((*nodeIter)->getModelMatrix());
			(*nodeIter)->getModel()->Draw(m_pActiveCamera->getProjection(), m_pActiveCamera->getView());
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void ShadowMapScene::renderPass()
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_lightingTech.Enable();


		m_lightingTech.SetWVP(m_pActiveCamera->getViewProjection());

		m_shadowMapFBO.BindForReading(GL_TEXTURE1);
		m_lightingTech.SetEyeWorldPos(m_pActiveCamera->getPosition());
		m_lightingTech.SetMatSpecularIntensity(0.0f);
		m_lightingTech.SetMatSpecularPower(0);
		m_lightingTech.SetLightWVP(m_spotCamera.getProjection() * m_spotCamera.getView());


		for (auto nodeIter = m_gameObjectsFlat.begin(); nodeIter != m_gameObjectsFlat.end(); nodeIter++)
		{
			m_lightingTech.SetWorldMatrix((*nodeIter)->getModelMatrix());
			(*nodeIter)->getModel()->Draw(m_pActiveCamera->getProjection(), m_pActiveCamera->getView());
		}
		m_lightingTech.SetWorldMatrix(m_pGround->getModelMatrix());
		m_pGround->getModel()->Draw(m_pActiveCamera->getProjection(), m_pActiveCamera->getView());

	}

	void ShadowMapScene::renderShadowMap()
	{
		m_shadowMapTech.Enable();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_shadowMapTech.SetTextureUnit(0);
		m_shadowMapFBO.BindForReading(GL_TEXTURE0);

		m_shadowMapTech.SetWVP(m_pActiveCamera->getProjection() * m_pActiveCamera->getView());

		m_shadowMapTech.SetWorldMatrix(m_pQuad->getModelMatrix());
		m_pQuad->getModel()->Draw(m_pActiveCamera->getProjection(), m_pActiveCamera->getView());
	}

	void ShadowMapScene::onKeyPressed(int key, int scancode)
	{
		if (key == GLFW_KEY_1)
		{
			m_drawShadowMap = !m_drawShadowMap;
		}
	}
	void ShadowMapScene::onKeyReleased(int key, int scancode)
	{

	}



}
