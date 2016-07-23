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
		"Shaders\\Camera.Fragment.glsl");


	modelsManager = new ModelsManager();
	activeCamera = new Camera();
	activeCamera->setPosition(glm::vec3(0.0,1.5f,-6.0));
	activeCamera->lookAt(glm::vec3(0.0, 0.0, 0.0));
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
	delete activeCamera;
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
	modelsManager->Draw(activeCamera->getProjection(), activeCamera->getView());
}

void SceneManager::NotifyEndFrame()
{

}

void SceneManager::NotifyReshape(int width, int height,
	int previos_width, int previous_height){

}