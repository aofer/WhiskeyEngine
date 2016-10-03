#include "SceneManager.h"
#include <glm/glm.hpp>
#include "../Core/Init/Common.h"
#include "../Rendering/Pipeline.h"
using namespace Managers;

SceneManager::SceneManager()
{

	glEnable(GL_DEPTH_TEST);

	shaderManager = new ShaderManager();
	shaderManager->CreateProgram("colorShader",
		"Shaders\\Vertex_Shader.glsl",
		"Shaders\\Fragment_Shader.glsl");
	shaderManager->CreateProgram("cameraShader",
		"Shaders\\Camera_vertex.glsl",
		"Shaders\\Camera_fragment.glsl");


	modelsManager = new ModelsManager();
	m_pActiveCamera = new Camera();
	m_pActiveCamera->setPosition(glm::vec3(0.0,2.0f,-8.0));
	m_pActiveCamera->lookAt(glm::vec3(0.0, 2.0, -9.0)); //camera lookat does not work
	int test = GLCheckError2();

	if (!m_lighting.Init())
	{
		printf("Error initializing lighting technique\n");
	}

	m_lighting.Enable();

	m_lighting.SetTextureUnit(0);

	PointLight pl[2];
	pl[0].DiffuseIntensity = 0.25f;
	pl[0].AmbientIntensity = 0.1f;
	pl[0].Color = glm::vec3(1.0f, 1.0f, 1.0f);
	pl[0].Position = glm::vec3(3.0f, 1.0f, 0.5f);
	pl[0].Attenuation.Linear = 0.1f;
	pl[1].DiffuseIntensity = 0.25f;
	pl[1].Color = glm::vec3(0.0f, 0.5f, 1.0f);
	pl[1].Position = glm::vec3(7.0f, 1.0f, 0.5f);
	pl[1].Attenuation.Linear = 0.1f;
	m_lighting.SetPointLights(2, pl);

    //m_lighting.SetPointLights()
	/*
	cam = new Camera(45.0f, 640 / 480, 0.1f, 100.0f);
	cam->setPosition(Vector3(0, 1.5f, 6.0));
	cam->setLookAt(Vector3(0, 1.5f, 0));
	*/
}

SceneManager::~SceneManager()
{

	delete shaderManager;
	delete modelsManager;
	delete m_pActiveCamera;
}

void SceneManager::NotifyBeginFrame()
{
	modelsManager->Update();
}

void SceneManager::NotifyDisplayFrame()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	Pipeline p;
	p.WorldPos(0.0f, 0.0f, 0.0f);
	p.SetCamera(m_pActiveCamera->getPosition(), m_pActiveCamera->getLookAt(), m_pActiveCamera->up());
	PersProjInfo persProjInfo; //TODO move to field?
	persProjInfo.FOV = m_pActiveCamera->getFieldOfView();
	persProjInfo.zFar = m_pActiveCamera->getFarPlane();
	persProjInfo.zNear = m_pActiveCamera->getNearPlane();
	persProjInfo.aspectRatio = m_pActiveCamera->getAspectRatio();


	p.SetPerspectiveProj(persProjInfo);
	const glm::mat4& WorldTransformation = p.GetWorldTrans();
	m_lighting.SetWVP(/*p.GetWVPTrans()*/m_pActiveCamera->getProjection() * m_pActiveCamera->getView() * glm::mat4(1.0f));//TODO get model matrix

	//m_lighting.SetDirectionalLight(m_directionalLight);
	m_lighting.SetWorldMatrix(WorldTransformation);
	m_lighting.SetEyeWorldPos(m_pActiveCamera->getPosition());
	m_lighting.SetMatSpecularIntensity(0.0f);
	m_lighting.SetMatSpecularPower(0);

	//modelsManager->Draw();
	modelsManager->Draw(m_pActiveCamera->getProjection(), m_pActiveCamera->getView());
}

void SceneManager::NotifyEndFrame()
{

}

void SceneManager::NotifyReshape(int width, int height,
	int previos_width, int previous_height){

}