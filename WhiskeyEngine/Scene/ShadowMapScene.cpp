#include "ShadowMapScene.h"
#include "../Core/Init/Common.h"

#include "../Rendering/Models/Mesh.h"
#include "GameObject.h"
#include "../Managers/ModelsManager.h"
#include "../Rendering/Pipeline.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace Rendering;

namespace Scene
{
	ShadowMapScene::ShadowMapScene() : GameScene()
	{

	}
	ShadowMapScene::~ShadowMapScene()
	{

	}

	void ShadowMapScene::init()
	{

		m_pActiveCamera->setPosition(glm::vec3(0.0, 2.0f, -8.0));
		m_pActiveCamera->setLookAt(glm::vec3(0.0, 2.0, -9.0));

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
		pl[0].DiffuseIntensity = 0.25f;
		pl[0].AmbientIntensity = 0.1f;
		pl[0].Color = glm::vec3(1.0f, 1.0f, 1.0f);
		pl[0].Position = glm::vec3(2.0f, 3.0f, 0.0f);
		pl[0].Attenuation.Linear = 0.1f;
		//pl[1].DiffuseIntensity = 0.25f;
		//pl[1].Color = glm::vec3(0.0f, 0.5f, 1.0f);
		//pl[1].Position = glm::vec3(7.0f, 1.0f, 0.5f);
		//pl[1].Attenuation.Linear = 0.1f;
		//m_lightingTech.SetPointLights(1, pl);


		m_spotLight.Color = glm::vec3(1.0, 1.0, 1.0);
		m_spotLight.DiffuseIntensity = 0.3f;
		m_spotLight.Direction = glm::vec3(0.0, -1.0, 0.0);
		m_spotLight.Attenuation.Linear = 0.1f;
		m_spotLight.AmbientIntensity = 0.2f;
		m_spotLight.Cutoff = 40.5f;
		m_spotLight.Position = glm::vec3(0.0, 10.0, 0.0);
		//spotLights[0].

		m_lightingTech.SetSpotLights(1, &m_spotLight);


		m_spotCamera.setPosition(m_spotLight.Position);
		m_spotCamera.setLookAt(glm::vec3(m_spotLight.Position + m_spotLight.Direction));


		//m_lighting.SetPointLights()
		/*
		cam = new Camera(45.0f, 640 / 480, 0.1f, 100.0f);
		cam->setPosition(Vector3(0, 1.5f, 6.0));
		cam->setLookAt(Vector3(0, 1.5f, 0));
		*/


		//Models::Mesh* tankMesh = new Models::Mesh();
		//tankMesh->Create("Assets\\phoenix_ugv.md2");
		//m_pModelsManager->AddModel("tank", tankMesh);
		//Scene::GameObject* tank = new GameObject();
		//tank->setModel(tankMesh);
		//tank->setPosition(glm::vec3(0.0, 0.0, 0.0));
		//tank->setScale(0.1f);
		//m_gameObjectsFlat.push_back(tank);

		Models::Mesh* groundMesh = new Models::Mesh();
		groundMesh->Create("Assets\\ground.obj");
		m_pModelsManager->AddModel("ground", groundMesh);
		Scene::GameObject* ground = new GameObject();
		ground->setModel(groundMesh);
		ground->setPosition(glm::vec3(0.0, 0.0, 1.0));
		ground->setScale(1.0f);
		m_gameObjectsFlat.push_back(ground);

		Models::Mesh* boxMesh = new Models::Mesh();
		boxMesh->Create("Assets\\box.obj");
		m_pModelsManager->AddModel("box", boxMesh);
		Scene::GameObject* box = new GameObject();
		box->setModel(boxMesh);
		box->setPosition(glm::vec3(0.0, 2.0, 0.0));
		box->setScale(1.0f);
		m_gameObjectsFlat.push_back(box);

		Scene::GameObject* box2 = new GameObject();
		box2->setModel(boxMesh);
		box2->setPosition(glm::vec3(3.0, 1.0, 0.0));
		box2->setScale(0.8f);
		m_gameObjectsFlat.push_back(box2);


		//Models::Mesh* groundMesh = new Models::Mesh();
		//groundMesh->Create("Assets\\ground.obj");
		//m_pModelsManager->AddModel("ground", groundMesh);
		//Scene::GameObject* ground = new GameObject();
		//ground->setModel(groundMesh);
		//ground->setPosition(glm::vec3(0.0, 0.0, 0.0));
		//ground->setScale(1.0f);
		//ground->addChild(box);
		//m_gameObjectsFlat.push_back(ground);
	}

	void ShadowMapScene::update(float dt)
	{

	}

	void ShadowMapScene::draw()
	{
		shadowMapPass();
		renderPass();
	}


	void ShadowMapScene::shadowMapPass()
	{
		m_shadowMapFBO.BindForWriting();
		glClear(GL_DEPTH_BUFFER_BIT);

		m_shadowMapTech.Enable();

		//TODO remove later
		PersProjInfo persProjInfo;
		persProjInfo.FOV = 60.0f;
		persProjInfo.aspectRatio = WINDOW_WIDTH / WINDOW_HEIGHT;
		persProjInfo.zNear = 1.0f;
		persProjInfo.zFar = 50.0f;

		//m_shadowMapTech.SetWVP(p.GetWVPTrans());

		//m_shadowMapTech.SetWVP(m_pActiveCamera->getProjection() * m_pActiveCamera->getView()); //todo this should be from light direction
		m_shadowMapTech.SetWVP(glm::perspective(persProjInfo.FOV, persProjInfo.aspectRatio, persProjInfo.zNear, persProjInfo.zFar) * glm::lookAt(m_spotLight.Position, m_spotLight.Direction, glm::vec3(1.0f, 0.0f, 0.0f)));
		//m_shadowMapTech.SetWVP(m_spotCamera.getProjection() * m_spotCamera.getView());

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

		//TODO remove later
		PersProjInfo persProjInfo;
		persProjInfo.FOV = 60.0f;
		persProjInfo.aspectRatio = WINDOW_WIDTH / WINDOW_HEIGHT;
		persProjInfo.zNear = 1.0f;
		persProjInfo.zFar = 50.0f;

		/*m_pActiveCamera->lookAt(glm::vec3(0.0, 0.0, 0.0));
		m_pActiveCamera->setPosition(glm::vec3(0.0, 10.0, 0.0));*/
		m_lightingTech.SetWVP(m_pActiveCamera->getViewProjection());
		//m_spotCamera.lookAt(glm::vec3(0.0, 0.0, 0.0));
		//m_lightingTech.SetWVP(m_pActiveCamera->getProjection() * m_spotCamera.getView());


		m_lightingTech.SetEyeWorldPos(m_pActiveCamera->getPosition());
		m_lightingTech.SetMatSpecularIntensity(0.0f);
		m_lightingTech.SetMatSpecularPower(0);
		//m_lightingTech.SetLightWVP(glm::perspective(persProjInfo.FOV, persProjInfo.aspectRatio, persProjInfo.zNear, persProjInfo.zFar) * glm::lookAt(m_spotLight.Position, m_spotLight.Direction, glm::vec3(1.0f, 0.0f, 0.0f)));
		m_lightingTech.SetLightWVP(m_spotCamera.getProjection() * m_spotCamera.getView());


		for (auto nodeIter = m_gameObjectsFlat.begin(); nodeIter != m_gameObjectsFlat.end(); nodeIter++)
		{
			m_lightingTech.SetWorldMatrix((*nodeIter)->getModelMatrix());
			(*nodeIter)->getModel()->Draw(m_pActiveCamera->getProjection(), m_pActiveCamera->getView());
		}
	}

}

