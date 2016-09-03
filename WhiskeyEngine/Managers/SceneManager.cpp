#include "SceneManager.h"
#include <glm/glm.hpp>
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
		"Shaders\\Camera_Fragment.glsl");


	modelsManager = new ModelsManager();
	m_activeCamera = new Camera();
	m_activeCamera->setPosition(glm::vec3(0.0,1.5f,-6.0));
	m_activeCamera->lookAt(glm::vec3(0.0, 0.0, 0.0));
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
	delete m_activeCamera;
}

void SceneManager::NotifyBeginFrame()
{
	modelsManager->Update();
}

void SceneManager::NotifyDisplayFrame()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	modelsManager->Draw();
	modelsManager->Draw(m_activeCamera->getProjection(), m_activeCamera->getView());
}

void SceneManager::NotifyEndFrame()
{

}

void SceneManager::NotifyReshape(int width, int height,
	int previos_width, int previous_height){

}

void SceneManager::addPointLight(PointLight light)
{
	m_pointLights.push_back(light);
}
void SceneManager::addSpotLight(SpotLight light)
{
	m_spotLights.push_back(light);
}
void SceneManager::addDirectionalLight(DirectionalLight light)
{
	m_directionalLights.push_back(light);
}