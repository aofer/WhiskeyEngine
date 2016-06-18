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

	Models::Mesh* boxMesh = new Models::Mesh();
	boxMesh->SetProgram(ShaderManager::GetShader("cameraShader"));
	boxMesh->Create("Assets\\box.obj");
	gameModelList["box"] = boxMesh;
	boxMesh->setPosition(glm::vec3(0.0, 3.5, 1.0));
	boxMesh->setScale(1.0f);
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

	IGameObject* model = gameModelList[gameModelName];
	model->Destroy();
	gameModelList.erase(gameModelName);

}

const IGameObject& ModelsManager::GetModel(const std::string& gameModelName) const
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
void ModelsManager::Draw(){

	for (auto model : gameModelList)
	{
		model.second->Draw();
	}
}
void ModelsManager::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{
	for (auto model : gameModelList)
	{
		model.second->Draw(projection_matrix, view_matrix);
	}
}