#include "GeometryPassTestScene.h"
#include "../Core/Init/Common.h"
#include "../Rendering/Models/Mesh.h"
#include "GameObject.h"
#include "../Managers/ModelsManager.h"
#include "../Rendering/Camera.h"
//#include <glm/gtc/matrix_transform.hpp>


using namespace Rendering;

namespace Scene
{
	GeometryPassTestScene::GeometryPassTestScene() : GameScene()
	{
		
	}
	GeometryPassTestScene::~GeometryPassTestScene()
	{
		
	}

	void GeometryPassTestScene::Init()
	{

		m_pActiveCamera->setPosition(glm::vec3(0.0, 2.0f, -8.0));
		m_pActiveCamera->setLookAt(glm::vec3(0.0, 2.0, 0.0));

		int test = GLCheckError();

		m_geometryPassTech = new SimplePBRGeometryPassTechnique();
		m_geometryPassTech->Init();
		
		// TESTING
		m_lightingTech = new LightingTechnique();
		m_lightingTech->Init();

		m_lightingTech->Enable();

		m_lightingTech->SetTextureUnit(0);

		PointLight pl[1];
		pl[0].m_diffuseIntensity = 0.25f;
		pl[0].m_ambientIntensity = 0.1f;
		pl[0].m_color = glm::vec3(1.0f, 1.0f, 1.0f);
		pl[0].m_position = glm::vec3(2.0f, 3.0f, 0.0f);
		pl[0].Attenuation.Linear = 0.1f;
		//pl[1].DiffuseIntensity = 0.25f;
		//pl[1].Color = glm::vec3(0.0f, 0.5f, 1.0f);
		//pl[1].Position = glm::vec3(7.0f, 1.0f, 0.5f);
		//pl[1].Attenuation.Linear = 0.1f;
		m_lightingTech->SetPointLights(1, pl);

		SpotLight spotLights[1];
		spotLights[0].m_color = glm::vec3(1.0, 1.0, 1.0);
		spotLights[0].m_diffuseIntensity = 0.3f;
		spotLights[0].m_direction = glm::vec3(0.0, -1.0, 0.0);
		spotLights[0].Attenuation.Linear = 0.1f;
		spotLights[0].m_ambientIntensity = 0.1f;
		spotLights[0].m_cutoff = 10.5f;
		spotLights[0].m_position = glm::vec3(-2.0, 10.0, -2.0);
		//spotLights[0].

		m_lightingTech->SetSpotLights(1, spotLights);

		//END TESTING

		m_gBuffer = new SimplePBRGBuffer();
		m_gBuffer->Init(WINDOW_WIDTH, WINDOW_HEIGHT);

		Models::Mesh* quad = new Models::Mesh();

		if (!quad->Create("Assets\\quad.obj")) {
			printf("Error loading screen space quad");
		}
		m_pModelsManager->AddModel("quad", quad);
		m_pQuad = new GameObject();
		m_pQuad->SetModel(quad);
		m_pQuad->SetPosition(glm::vec3(0.0, 0.0, 1.0));
		m_pQuad->SetScale(5.0f);

		Models::Mesh* groundMesh = new Models::Mesh();
		groundMesh->Create("Assets\\ground.obj");
		m_pModelsManager->AddModel("ground", groundMesh);
		m_pGround = new GameObject();
		m_pGround->SetModel(groundMesh);
		m_pGround->SetPosition(glm::vec3(0.0, 0.0, 0.0));
		m_pGround->SetScale(1.0f);
		//m_gameObjectsFlat.push_back(m_pGround);

		Models::Mesh* spinningMesh = new Models::Mesh();
		spinningMesh->Create("Assets\\deer-obj.obj");
		m_pModelsManager->AddModel("spinning", spinningMesh);
		m_spinningBox = new GameObject();
		m_spinningBox->SetModel(spinningMesh);
		m_spinningBox->SetPosition(glm::vec3(0.0, 2.0, 0.0));
		m_spinningBox->SetScale(0.15f);
		m_gameObjectsFlat.push_back(m_spinningBox);

		Models::Mesh* boxMesh = new Models::Mesh();
		boxMesh->Create("Assets\\box.obj");
		m_pModelsManager->AddModel("box", boxMesh);
		Scene::GameObject* box2 = new GameObject();
		box2->SetModel(boxMesh);
		box2->SetPosition(glm::vec3(3.0, 1.0, 0.0));
		box2->SetScale(0.8f);
		m_gameObjectsFlat.push_back(box2);



	}

	void GeometryPassTestScene::Update(float dt)
	{
		m_spinningBox->SetOrientation(m_spinningBox->GetOrientation()  *  glm::angleAxis(glm::degrees(0.05f* dt), glm::vec3(0.0f, 1.f, 0.f)));
	}

	void GeometryPassTestScene::Draw()
	{

		GeometryPass();
		RenderGBufferToScreen();
	}


	void GeometryPassTestScene::GeometryPass()
	{
		m_geometryPassTech->Enable();
		m_gBuffer->BeginRender();
		m_gBuffer->BindForGeometryPass();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SimplePBRMaterial testMat;
		testMat.diffuseColor = glm::vec3(0.2, 0.5, 0.8);
		testMat.metallic = 0.8;
		testMat.specular = 0.5;
		testMat.roughness = 0.1;

		m_geometryPassTech->SetMaterial(testMat);

		for (auto nodeIter = m_gameObjectsFlat.begin(); nodeIter != m_gameObjectsFlat.end(); nodeIter++)
		{
			m_geometryPassTech->SetWorldMatrix((*nodeIter)->GetModelMatrix());
			m_geometryPassTech->SetWVP(m_pActiveCamera->getProjection() * m_pActiveCamera->getView() * (*nodeIter)->GetModelMatrix());
			(*nodeIter)->GetModel()->Draw(m_pActiveCamera->getProjection(), m_pActiveCamera->getView());
		}

		//m_lightingTech->Enable();

		//

		//m_lightingTech->SetEyeWorldPos(m_pActiveCamera->getPosition());
		//m_lightingTech->SetMatSpecularIntensity(0.0f);
		//m_lightingTech->SetMatSpecularPower(0);
		//m_lightingTech->SetWVP(m_pActiveCamera->getProjection() * m_pActiveCamera->getView());
		//for (auto nodeIter = m_gameObjectsFlat.begin(); nodeIter != m_gameObjectsFlat.end(); nodeIter++)
		//{
		//	m_lightingTech->SetWVP(/*p.GetWVPTrans()*/m_pActiveCamera->getProjection() * m_pActiveCamera->getView() * (*nodeIter)->GetModelMatrix());//TODO get model matrix
		//	m_lightingTech->SetWorldMatrix((*nodeIter)->GetModelMatrix());
		//	(*nodeIter)->GetModel()->Draw(m_pActiveCamera->getProjection(), m_pActiveCamera->getView());
		//}
	}

	void GeometryPassTestScene::RenderGBufferToScreen()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_gBuffer->BindForFinalComposition();

		GLint HalfWidth = (GLint)(WINDOW_WIDTH / 2.0f);
		GLint HalfHeight = (GLint)(WINDOW_HEIGHT / 2.0f);

		m_gBuffer->SetReadBuffer(SimplePBRGBuffer::TEXTURE_POSITION);
		glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, HalfWidth, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

		m_gBuffer->SetReadBuffer(SimplePBRGBuffer::TEXTURE_DIFFUSE);
		glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, HalfHeight, HalfWidth, WINDOW_HEIGHT, GL_COLOR_BUFFER_BIT, GL_LINEAR);

		m_gBuffer->SetReadBuffer(SimplePBRGBuffer::TEXTURE_METALLIC_ROUGHNESS_SPECULAR);
		glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, HalfWidth, HalfHeight, WINDOW_WIDTH, WINDOW_HEIGHT, GL_COLOR_BUFFER_BIT, GL_LINEAR);

		m_gBuffer->SetReadBuffer(SimplePBRGBuffer::TEXTURE_NORMAL);
		glBlitFramebuffer(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, HalfWidth, 0, WINDOW_WIDTH, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	}

}

