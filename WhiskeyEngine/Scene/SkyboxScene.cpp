#include "SkyboxScene.h"
#include "../Core/Init/Common.h"
#include "../Rendering/FPSCamera.h"
#include "../Rendering/Models/Mesh.h"
#include "../Rendering/Lighting.h"
#include "GameObject.h"
#include "../Managers/ModelsManager.h"

using namespace Rendering;
using namespace Scene::Components;
namespace Scene
{
	SkyboxScene::SkyboxScene() : GameScene()
	{

	}
	SkyboxScene::~SkyboxScene()
	{

	}


	void SkyboxScene::Init()
	{
		m_pActiveCamera->setPosition(glm::vec3(0.0, 2.0f, -6.0));
		m_pActiveCamera->setLookAt(glm::vec3(0.0, 2.0, 0.0));

		int test = GLCheckError(); //TODO figure out why we need to clear this
		if (!m_lighting.Init())
		{
			printf("Error initializing lighting technique\n");
		}

		m_lighting.Enable();

		m_lighting.SetTextureUnit(0);

		PointLight pl[1];
		pl[0].m_diffuseIntensity = 0.25f;
		pl[0].m_ambientIntensity = 0.1f;
		pl[0].m_color = glm::vec3(1.0f, 1.0f, 1.0f);
		pl[0].m_position = glm::vec3(2.0f, 3.0f, 0.0f);
		pl[0].Attenuation.Linear = 0.1f;

		m_lighting.SetPointLights(1, pl);

		SpotLight spotLights[1];
		spotLights[0].m_color = glm::vec3(1.0, 1.0, 1.0);
		spotLights[0].m_diffuseIntensity = 0.3f;
		spotLights[0].m_direction = glm::vec3(0.0, -1.0, 0.0);
		spotLights[0].Attenuation.Linear = 0.1f;
		spotLights[0].m_ambientIntensity = 0.1f;
		spotLights[0].m_cutoff = 10.5f;
		spotLights[0].m_position = glm::vec3(-2.0, 10.0, -2.0);
		//spotLights[0].

		m_lighting.SetSpotLights(1, spotLights);

		Models::Mesh* boxMesh = new Models::Mesh();
		boxMesh->Create("Assets\\box.obj");
		m_pModelsManager->AddModel("box", boxMesh);
		Scene::GameObject* box = new GameObject();
		box->SetModel(boxMesh);
		box->SetPosition(glm::vec3(5.0, 1.0, 0.0));
		box->SetScale(2.0f);
		//box->SetOrientation(glm::quat(45);
		m_gameObjectsFlat.push_back(box);

		Scene::GameObject* box2 = new GameObject();
		box2->SetModel(boxMesh);
		box2->SetPosition(glm::vec3(3.0, 1.0, 0.0));
		box2->SetScale(0.8f);
		m_gameObjectsFlat.push_back(box2);


		Models::Mesh* groundMesh = new Models::Mesh();
		groundMesh->Create("Assets\\ground.obj");
		m_pModelsManager->AddModel("ground", groundMesh);
		Scene::GameObject* ground = new GameObject();
		ground->SetModel(groundMesh);
		ground->SetPosition(glm::vec3(0.0, 0.0, 0.0));
		ground->SetScale(1.0f);
		ground->AddChild(box);
		m_gameObjectsFlat.push_back(ground);

		m_pSkybox = new SkyBox(m_pActiveCamera);
		if (!m_pSkybox->Init("Assets\\skybox\\",
			"sp3right.jpg",
			"sp3left.jpg",
			"sp3top.jpg",
			"sp3bot.jpg",
			"sp3front.jpg",
			"sp3back.jpg")) {
			printf("cannot init skybox\n");
		}
		m_tempSkyBoxObject = new GameObject();
		m_tempSkyBoxObject->SetScale(200);
		//m_tempSkyBoxObject->


	}

	void SkyboxScene::Update(float dt)
	{

	}

	void SkyboxScene::Draw()
	{
		m_lighting.Enable();
		//const glm::mat4& WorldTransformation = p.GetWorldTrans();
		//m_lighting.SetWVP(/*p.GetWVPTrans()*/m_pActiveCamera->getViewProjection());//TODO get model matrix

		//m_lighting.SetDirectionalLight(m_directionalLight);
		//m_lighting.SetWorldMatrix(WorldTransformation);
		m_lighting.SetEyeWorldPos(m_pActiveCamera->getPosition());
		m_lighting.SetMatSpecularIntensity(0.0f);
		m_lighting.SetMatSpecularPower(0);

		//Render scene - TODO: change to scene graph

		for (auto nodeIter = m_gameObjectsFlat.begin(); nodeIter != m_gameObjectsFlat.end(); nodeIter++)
		{
			m_lighting.SetWVP(/*p.GetWVPTrans()*/m_pActiveCamera->getViewProjection() * (*nodeIter)->GetModelMatrix());//TODO get model matrix
			m_lighting.SetWorldMatrix((*nodeIter)->GetModelMatrix());
			(*nodeIter)->GetModel()->Draw();
		}
		m_tempSkyBoxObject->SetPosition(m_pActiveCamera->getPosition());
		
		m_pSkybox->Render(m_tempSkyBoxObject->GetModelMatrix());
	}
}

