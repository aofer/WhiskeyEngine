#include "SceneManager.h"
#include <glm/glm.hpp>
#include "../Core/Init/Common.h"
#include "../Rendering/Pipeline.h"
#include "../Rendering/Models/Mesh.h"
#include "../Rendering/Models/Model.h"
#include "../Scene/GameObject.h"

using namespace Managers;
using namespace Scene;

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
	m_pActiveCamera->lookAt(glm::vec3(0.0, 2.0, -9.0));
	int test = GLCheckError2();

	if (!m_lighting.Init())
	{
		printf("Error initializing lighting technique\n");
	}

	m_lighting.Enable();

	m_lighting.SetTextureUnit(0);

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
	m_lighting.SetPointLights(1, pl);

	SpotLight spotLights[1];
	spotLights[0].Color = glm::vec3(1.0, 1.0, 1.0);
	spotLights[0].DiffuseIntensity = 0.3f;
	spotLights[0].Direction = glm::vec3(0.0, -1.0, 0.0);
	spotLights[0].Attenuation.Linear = 0.1f;
	spotLights[0].AmbientIntensity = 0.1f;
	spotLights[0].Cutoff = 10.5f;
	spotLights[0].Position = glm::vec3(-2.0, 10.0, -2.0);
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
	modelsManager->AddModel("box", boxMesh);
	Scene::GameObject* box = new GameObject();
	box->setModel(boxMesh);
	box->setPosition(glm::vec3(1.0, 1.0, 0.0));
	box->setScale(1.0f);
	m_gameObjectsFlat.push_back(box);

	Scene::GameObject* box2 = new GameObject();
	box2->setModel(boxMesh);
	box2->setPosition(glm::vec3(3.0, 1.0, 0.0));
	box2->setScale(0.8f);
	m_gameObjectsFlat.push_back(box2);


	Models::Mesh* groundMesh = new Models::Mesh();
	groundMesh->Create("Assets\\ground.obj");
	modelsManager->AddModel("ground", groundMesh);
	Scene::GameObject* ground = new GameObject();
	ground->setModel(groundMesh);
	ground->setPosition(glm::vec3(0.0, 0.0, 0.0));
	ground->setScale(1.0f);
	ground->addChild(box);
	m_gameObjectsFlat.push_back(ground);
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

	//const glm::mat4& WorldTransformation = p.GetWorldTrans();
	m_lighting.SetWVP(/*p.GetWVPTrans()*/m_pActiveCamera->getProjection() * m_pActiveCamera->getView());//TODO get model matrix

	//m_lighting.SetDirectionalLight(m_directionalLight);
	//m_lighting.SetWorldMatrix(WorldTransformation);
	m_lighting.SetEyeWorldPos(m_pActiveCamera->getPosition());
	m_lighting.SetMatSpecularIntensity(0.0f);
	m_lighting.SetMatSpecularPower(0);

	//Render scene - TODO: change to scene graph

	for (auto nodeIter = m_gameObjectsFlat.begin(); nodeIter != m_gameObjectsFlat.end(); nodeIter++)
	{
		m_lighting.SetWorldMatrix((*nodeIter)->getModelMatrix());
		(*nodeIter)->getModel()->Draw(m_pActiveCamera->getProjection(), m_pActiveCamera->getView());
	}
}

void SceneManager::NotifyEndFrame()
{

}

void SceneManager::NotifyReshape(int width, int height,
	int previos_width, int previous_height){

}