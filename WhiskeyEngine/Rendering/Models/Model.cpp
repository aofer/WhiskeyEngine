#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

using namespace Rendering;
using namespace Models;

Model::Model()
{
	modelMatrix = glm::mat4(1.0f);
	scale = 1.0f;
}

Model::~Model()
{

	Destroy();

}

void Model::Draw()
{
	//this is abstract, we don't continue to override this method
}

void Model::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)
{

}

void Model::Update()
{
	//this is abstract, we don't continue to override this method
}

void Model::SetProgram(GLuint program)
{
	this->program = program;
}

GLuint Model::GetVao() const
{
	return vao;
}

const std::vector<GLuint> Model::GetVbos() const
{
	return vbos;
}

void Model::Destroy()
{
	glDeleteVertexArrays(1, &vao);
	if (vbos.size() > 0) //TODO fix later
	{
		glDeleteBuffers(vbos.size(), &vbos[0]);
	}

	vbos.clear();
}

glm::mat4 Model::getModelMatrix() const
{
	return modelMatrix;
}

glm::vec3 Model::getPosition() const
{
	return position;
}

float Model::getScale() const
{
	return scale;
}

void Model::setPosition(const glm::vec3& position)
{
	this->position = position;
	//glm::mat4 mat = glm::mat4::identyi
	updateModelMatrix();
}

void Model::setScale(const float& scale)
{
	this->scale = scale;
	updateModelMatrix();
}

void Model::updateModelMatrix()
{
	modelMatrix = glm::translate(
		glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale)),
		position);
}