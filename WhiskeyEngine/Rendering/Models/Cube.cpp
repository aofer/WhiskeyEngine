//Cube.cpp
#include "Cube.h"
using namespace Rendering;
using namespace Models;

#define PI 3.14159265

Cube::Cube()
{
	m_texture = Texture("Assets\\tex1.png", GL_TEXTURE_2D);
	m_texture.Load();
	//m_texture("Resources\\tex1.png", GL_TEXTURE_2D);
}

Cube::~Cube()
{
}

void Cube::Create()
{
	GLuint vao;
	GLuint vbo;

	time(&timer);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;
	//vertices for the front face of the cube
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0),
		glm::vec4(0.0, 0.0, 1.0, 1.0), glm::vec2(0.0,0.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0),
		glm::vec4(1.0, 0.0, 1.0, 1.0), glm::vec2(1.0, 0.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1.0, 1.0)));

	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0),
		glm::vec4(0.0, 1.0, 1.0, 1.0), glm::vec2(0.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0),
		glm::vec4(0.0, 0.0, 1.0, 1.0), glm::vec2(0.0, 0.0)));

	//vertices for the right face of the cube
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0),
		glm::vec4(1.0, 1.0, 0.0, 1.0), glm::vec2(1.0, 0.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0),
		glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec2(0.0, 0.0)));

	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0),
		glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec2(0.0, 0.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0),
		glm::vec4(1.0, 0.0, 1.0, 1.0), glm::vec2(0.0, 1.0)));

	//vertices for the back face of the cube
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0),
		glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(0.0, 0.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0),
		glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec2(1.0, 0.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0),
		glm::vec4(1.0, 1.0, 0.0, 1.0), glm::vec2(1.0, 1.0)));

	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0),
		glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(0.0, 0.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0),
		glm::vec4(1.0, 1.0, 0.0, 1.0), glm::vec2(1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0),
		glm::vec4(0.0, 1.0, 0.0, 1.0), glm::vec2(0.0, 1.0)));

	//vertices for the left face of the cube
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0),
		glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(0.0, 0.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0),
		glm::vec4(0.0, 0.0, 1.0, 1.0), glm::vec2(0.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0),
		glm::vec4(0.0, 1.0, 1.0, 1.0), glm::vec2(1.0, 1.0)));

	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0),
		glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(0.0, 0.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0),
		glm::vec4(0.0, 1.0, 1.0, 1.0), glm::vec2(1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0),
		glm::vec4(0.0, 1.0, 0.0, 1.0), glm::vec2(1.0, 0.0)));

	//vertices for the upper face of the cube
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec2(1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0),
		glm::vec4(0.0, 1.0, 1.0, 1.0), glm::vec2(0.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0),
		glm::vec4(1.0, 1.0, 0.0, 1.0), glm::vec2(1.0, 0.0)));

	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0),
		glm::vec4(0.0, 1.0, 1.0, 1.0), glm::vec2(0.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0),
		glm::vec4(1.0, 1.0, 0.0, 1.0), glm::vec2(1.0, 0.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0),
		glm::vec4(0.0, 1.0, 0.0, 1.0), glm::vec2(0.0, 0.0)));

	//vertices for the bottom face of the cube
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0),
		glm::vec4(0.0, 0.0, 0.0, 1.0), glm::vec2(0.0, 0.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0),
		glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec2(1.0, 0.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0),
		glm::vec4(0.0, 0.0, 1.0, 1.0), glm::vec2(0.0, 1.0)));

	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0),
		glm::vec4(1.0, 0.0, 0.0, 1.0), glm::vec2(1.0, 0.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0),
		glm::vec4(0.0, 0.0, 1.0, 1.0), glm::vec2(0.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0),
		glm::vec4(1.0, 0.0, 1.0, 1.0), glm::vec2(1.0, 1.0)));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 36, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::uv)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::normal)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);

	rotation_speed = glm::vec3(90.0, 90.0, 90.0);
	rotation = glm::vec3(0.0, 0.0, 0.0);

}

void Cube::Update()
{

}

void Cube::Draw(const glm::mat4& projection_matrix,
	const glm::mat4& view_matrix)
{
	rotation = 0.01f * rotation_speed + rotation;
	//std::cout << "view matrix: " << view_matrix[0][0] << std::endl;
	glm::vec3 rotation_sin = glm::vec3(rotation.x * PI / 180, rotation.y * PI / 180, rotation.z * PI / 180);

	glUseProgram(program);
	glUniform3f(glGetUniformLocation(program, "rotation"),
		rotation_sin.x,
		rotation_sin.y,
		rotation_sin.z);
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1,
		false, &view_matrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projection_matrix[0][0]);
//	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, &getModelMatrix()[0][0]);
	glBindVertexArray(vao);
	m_texture.Bind(GL_TEXTURE0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}