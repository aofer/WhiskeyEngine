#include "ShadowMapDebugScene.h"
#include "../Core/Init/Common.h"
#include "../Rendering/Models/Mesh.h"
#include "../Rendering/Lighting.h"
#include "GameObject.h"
#include "../Managers/ModelsManager.h"
#include "../Rendering/Pipeline.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace Rendering;

namespace Scene
{
	ShadowMapDebugScene::ShadowMapDebugScene() : GameScene()
	{
		m_pQuad = nullptr;
	}
	ShadowMapDebugScene::~ShadowMapDebugScene()
	{
		SAFE_DELETE(m_pQuad);
	}

	void ShadowMapDebugScene::Init()
	{
		m_pActiveCamera->setPosition(glm::vec3(0.0, 2.0f, -8.0));
		m_pActiveCamera->setLookAt(glm::vec3(0.0, 2.0, 0.0));

		Models::Mesh* quad = new Models::Mesh();

		if (!quad->Create("Assets\\quad.obj")) {
			printf("Error loading screen space quad");
		}
		m_pModelsManager->AddModel("quad", quad);
		m_pQuad = new GameObject();
		m_pQuad->SetModel(quad);
		m_pQuad->SetPosition(glm::vec3(0.0, 0.0, 1.0));
		m_pQuad->SetScale(5.0f);

		int test = GLCheckError();

		if (!m_shadowMapFBO.Init(WINDOW_WIDTH, WINDOW_HEIGHT)) {
			printf("Error initializing shadowMapFBO \n");
		}

		if (!m_shadowMapTech.Init()) {
			printf("Error initializing the shadow map technique\n");
		}

		m_spotLight.Color = glm::vec3(1.0, 1.0, 1.0);
		m_spotLight.DiffuseIntensity = 0.3f;
		m_spotLight.Direction = glm::vec3(-0.5, -10.0, -2.0);
		m_spotLight.Attenuation.Linear = 0.1f;
		m_spotLight.AmbientIntensity = 0.1f;
		m_spotLight.Cutoff = 40.5f;
		m_spotLight.Position = glm::vec3(0.5, 10.0, 2.0);

		m_spotCamera.setPosition(m_spotLight.Position);
		m_spotCamera.setLookAt(glm::vec3(m_spotLight.Position + m_spotLight.Direction));

		Models::Mesh* boxMesh = new Models::Mesh();
		boxMesh->Create("Assets\\box.obj");
		m_pModelsManager->AddModel("box", boxMesh);
		Scene::GameObject* box = new GameObject();
		box->SetModel(boxMesh);
		box->SetPosition(glm::vec3(1.0, 1.0, 0.0));
		box->SetScale(1.0f);
		m_gameObjectsFlat.push_back(box);

		Scene::GameObject* box2 = new GameObject();
		box2->SetModel(boxMesh);
		box2->SetPosition(glm::vec3(3.0, 1.0, 0.0));
		box2->SetScale(0.8f);
		m_gameObjectsFlat.push_back(box2);


		//Models::Mesh* tankMesh = new Models::Mesh();
		//tankMesh->Create("Assets\\phoenix_ugv.md2");
		//m_pModelsManager->AddModel("tank", tankMesh);
		//Scene::GameObject* tank = new GameObject();
		//tank->setModel(tankMesh);
		//tank->setPosition(glm::vec3(0.0, 0.0, 0.0));
		//tank->setScale(0.08f);
		//m_gameObjectsFlat.push_back(tank);


		Models::Mesh* groundMesh = new Models::Mesh();
		groundMesh->Create("Assets\\ground.obj");
		m_pModelsManager->AddModel("ground", groundMesh);
		Scene::GameObject* ground = new GameObject();
		ground->SetModel(groundMesh);
		ground->SetPosition(glm::vec3(0.0, 0.0, 0.0));
		ground->SetScale(1.0f);
		ground->AddChild(box);
		m_gameObjectsFlat.push_back(ground);

		m_shadowMapTech.Enable();
	}

	void ShadowMapDebugScene::Update(float dt)
	{

	}

	void ShadowMapDebugScene::Draw()
	{
		shadowMapPass();
		renderPass();
	}


	void ShadowMapDebugScene::shadowMapPass()
	{
		m_shadowMapFBO.BindForWriting();
		glClear(GL_DEPTH_BUFFER_BIT);

		m_shadowMapTech.SetWVP(m_spotCamera.getProjection() * m_spotCamera.getView());
//		m_shadowMapTech.SetWVP(m_pActiveCamera->getProjection() * m_pActiveCamera->getView());

		for (auto nodeIter = m_gameObjectsFlat.begin(); nodeIter != m_gameObjectsFlat.end(); nodeIter++)
		{
			m_shadowMapTech.SetWorldMatrix((*nodeIter)->GetModelMatrix());
			(*nodeIter)->GetModel()->Draw(m_pActiveCamera->getProjection(), m_pActiveCamera->getView());
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void ShadowMapDebugScene::renderPass()
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_shadowMapTech.SetTextureUnit(0);
		m_shadowMapFBO.BindForReading(GL_TEXTURE0);

		m_shadowMapTech.SetWVP(m_pActiveCamera->getProjection() * m_pActiveCamera->getView());

		m_shadowMapTech.SetWorldMatrix(m_pQuad->GetModelMatrix());
		m_pQuad->GetModel()->Draw(m_pActiveCamera->getProjection(), m_pActiveCamera->getView());
		/*for (auto nodeIter = m_gameObjectsFlat.begin(); nodeIter != m_gameObjectsFlat.end(); nodeIter++)
		{
		m_shadowMapTech.SetWorldMatrix((*nodeIter)->getModelMatrix());
		(*nodeIter)->getModel()->Draw(m_pActiveCamera->getProjection(), m_pActiveCamera->getView());
		}*/
		
	}

}

