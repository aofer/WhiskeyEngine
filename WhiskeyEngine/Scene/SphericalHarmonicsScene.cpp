#include "SphericalHarmonicsScene.h"
#include "../Core/Init/Common.h"
#include "../Rendering/FPSCamera.h"
#include "../Rendering/Models/Mesh.h"
#include "../Rendering/Lighting.h"
#include "GameObject.h"
#include "../Managers/ModelsManager.h"

using namespace Rendering;

const int CUBEMAP_SIZE = 1024;

namespace Scene
{
	SphericalHarmonicsScene::SphericalHarmonicsScene() : GameScene()
	{

	}
	SphericalHarmonicsScene::~SphericalHarmonicsScene()
	{
		delete m_cubeCam;
	}

	void SphericalHarmonicsScene::Init()
	{
		glm::vec3 camPos = glm::vec3(0.0, 5.0f, -6.0);
		m_pActiveCamera->setPosition(camPos);
		m_pActiveCamera->setLookAt(glm::vec3(0.0, 5.0, 0.0));

		m_cubeCam = new CubeMapCamera(camPos);

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
		//pl[1].DiffuseIntensity = 0.25f;
		//pl[1].Color = glm::vec3(0.0f, 0.5f, 1.0f);
		//pl[1].Position = glm::vec3(7.0f, 1.0f, 0.5f);
		//pl[1].Attenuation.Linear = 0.1f;
		m_lighting.SetPointLights(1, pl);

		SpotLight spotLights[1];
		spotLights[0].m_color = glm::vec3(1.0, 1.0, 1.0);
		spotLights[0].m_diffuseIntensity = 0.3f;
		spotLights[0].m_direction = glm::vec3(0.0, -1.0, 0.0);
		spotLights[0].Attenuation.Linear = 0.1f;
		spotLights[0].m_ambientIntensity = 0.5f;
		spotLights[0].m_cutoff = 10.5f;
		spotLights[0].m_position = glm::vec3(-2.0, 10.0, -2.0);
		//spotLights[0].

		m_lighting.SetSpotLights(1, spotLights);


		//m_lighting.SetPointLights()
		/*
		cam = new Camera(45.0f, 640 / 480, 0.1f, 100.0f);
		cam->setPosition(Vector3(0, 1.5f, 6.0));
		cam->setLookAt(Vector3(0, 1.5f, 0));
		*/

		Models::Mesh* boxMesh = new Models::Mesh();
		boxMesh->Create("Assets\\box.obj");
		Models::Mesh* roomMesh = new Models::Mesh();
		roomMesh->Create("Assets\\room.obj");
		m_pModelsManager->AddModel("room", roomMesh);

		Scene::GameObject* room = new GameObject();
		room->SetModel(roomMesh);
		room->SetPosition(glm::vec3(0.0, 0.0, 0.0));
		room->SetScale(2.0f);
		m_gameObjectsFlat.push_back(room);

		Scene::GameObject* box2 = new GameObject();
		box2->SetModel(boxMesh);
		box2->SetPosition(glm::vec3(0.0, 3.4, 0.0));
		box2->SetScale(0.8f);
		m_gameObjectsFlat.push_back(box2);


		//Models::Mesh* groundMesh = new Models::Mesh();
		//groundMesh->Create("Assets\\ground.obj");
		//m_pModelsManager->AddModel("ground", groundMesh);
		//Scene::GameObject* ground = new GameObject();
		//ground->SetModel(groundMesh);
		//ground->SetPosition(glm::vec3(0.0, 0.0, 0.0));
		//ground->SetScale(1.0f);
		////ground->AddChild(box);
		//m_gameObjectsFlat.push_back(ground);

		initEnvironmentMapTexture();
		initEnvironmentRendering();
	}

	void SphericalHarmonicsScene::Update(float dt)
	{

	}

	void SphericalHarmonicsScene::Draw()
	{
		renderEnvironmentMap();
		renderScene(m_pActiveCamera->getPosition(), m_pActiveCamera->getViewProjection());

	}

	void SphericalHarmonicsScene::initEnvironmentMapTexture()
	{
		glGenTextures(1, &m_EnvMapTexture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_EnvMapTexture);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		for (int i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, CUBEMAP_SIZE,
				CUBEMAP_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		}

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;

		glBindTexture(GL_TEXTURE_CUBE_MAP,0);

	}

	void SphericalHarmonicsScene::initEnvironmentRendering()
	{
		glGenFramebuffers(1, &m_fboId);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
		//glDrawBuffer(GL_COLOR_ATTACHMENT0);
		GLuint depthBufferId;
		glGenRenderbuffers(1, &depthBufferId);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, CUBEMAP_SIZE, CUBEMAP_SIZE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X, m_EnvMapTexture, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferId);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X, m_EnvMapTexture, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	void SphericalHarmonicsScene::renderEnvironmentMap()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);

		for (int faceIndex = 0; faceIndex < 6; ++faceIndex)
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + faceIndex, m_EnvMapTexture, 0);
			glClear(GL_DEPTH_BUFFER_BIT);
			m_cubeCam->SetCameraToFace(faceIndex);
			renderScene(m_cubeCam->getPosition(), m_cubeCam->getViewProjection());
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void SphericalHarmonicsScene::renderScene(glm::vec3 camPosition, glm::mat4 viewProjection)
	{

		m_lighting.SetEyeWorldPos(camPosition);
		m_lighting.SetMatSpecularIntensity(0.0f);
		m_lighting.SetMatSpecularPower(0);

		for (auto nodeIter = m_gameObjectsFlat.begin(); nodeIter != m_gameObjectsFlat.end(); nodeIter++)
		{
			m_lighting.SetWVP(viewProjection* (*nodeIter)->GetModelMatrix());
			m_lighting.SetWorldMatrix((*nodeIter)->GetModelMatrix());
			(*nodeIter)->GetModel()->Draw();
		}
	}

}

