#include "ModelsManager.h"
#include "../Rendering/Models/Mesh.h"

using namespace Managers;
using namespace Rendering;

ModelsManager::ModelsManager()
{
	
	/*Models::Triangle* triangle = new Models::Triangle();
	triangle->SetProgram(ShaderManager::GetShader("colorShader"));
	triangle->Create();
	gameModelList["triangle"] = triangle;

	Models::Quad* quad = new Models::Quad();
	quad->SetProgram(ShaderManager::GetShader("colorShader"));
	quad->Create();
	gameModelList["quad"] = quad;
	*/
	//Models::Cube* cube = new Models::Cube();
	//cube->SetProgram(ShaderManager::GetShader("cameraShader"));
	//cube->Create();
	//gameModelList["cube"] = cube;
	//cube->setPosition(glm::vec3(0.0f, 3.0f, 1.0f));
	//cube->setScale(0.25f);

	//Models::Mesh* mesh = new Models::Mesh();
	//mesh->SetProgram(ShaderManager::GetShader("cameraShader"));
	//mesh->Create("Assets\\cow.obj");
	//gameModelList["cow"] = mesh;
	//mesh->setPosition(glm::vec3(1.0, 3.0, 1.0));
	//mesh->setScale(2.0f);


}

ModelsManager::~ModelsManager()
{


	for (auto model : gameModelList)
	{
		delete model.second;
	}
	gameModelList.clear();
}

void ModelsManager::DeleteModel(const std::string& gameModelName)
{

	IRenderable* model = gameModelList[gameModelName];
	model->Destroy();
	gameModelList.erase(gameModelName);

}

void ModelsManager::AddModel(const std::string& gameModelName, IRenderable* gameObject)
{
	if (gameModelList.find(gameModelName) != gameModelList.end())
	{
		DeleteModel(gameModelName);
	}
	gameModelList[gameModelName] = gameObject;
}

const IRenderable& ModelsManager::GetModel(const std::string& gameModelName) const
{
	return (*gameModelList.at(gameModelName));
}

void ModelsManager::Update()
{
	for (auto model : gameModelList)
	{
		model.second->Update();
	}
}
