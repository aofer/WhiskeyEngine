#include "SceneManager.h"
#include <glm/glm.hpp>
#include "../Rendering/Pipeline.h"
#include "../Rendering/Models/Mesh.h"
#include "../Rendering/Models/Model.h"
#include "../Scene/GameObject.h"
#include "../Scene/GameScene.h"
#include "../Scene//LightingScene.h"
#include "../Scene//ShadowMapDebugScene.h"
#include "../Scene//ShadowMapScene.h"
#include "../Scene/SkyboxScene.h"

using namespace Managers;
using namespace Scene;

SceneManager::SceneManager()
{

	glEnable(GL_DEPTH_TEST);

	shaderManager = new ShaderManager();
	//shaderManager->CreateProgram("colorShader",
	//	"Shaders\\Vertex_Shader.glsl",
	//	"Shaders\\Fragment_Shader.glsl");
	//shaderManager->CreateProgram("cameraShader",
	//	"Shaders\\Camera_vertex.glsl",
	//	"Shaders\\Camera_fragment.glsl");


	modelsManager = new ModelsManager();

	//m_activeScene = new ShadowMapScene();
	m_activeScene = new SkyboxScene();
	//m_activeScene = new LightingScene();
	m_activeScene->SetModelsManager(modelsManager);
	m_activeScene->Init();


}

SceneManager::~SceneManager()
{

	delete shaderManager;
	delete modelsManager;
	//delete m_pActiveCamera;
}

void SceneManager::NotifyBeginFrame(double dt)
{
	modelsManager->Update();
	m_activeScene->Update(dt);
}

void SceneManager::NotifyDisplayFrame()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	m_activeScene->Draw();

}

void SceneManager::NotifyEndFrame()
{

}

void SceneManager::NotifyReshape(int width, int height,
	int previos_width, int previous_height)
{

}