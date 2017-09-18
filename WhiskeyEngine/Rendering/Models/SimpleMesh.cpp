#include "SimpleMesh.h"
#include "../../Core/Init/Common.h"
using namespace Rendering;
using namespace Models;



SimpleMesh::SubMesh::SubMesh()
{
	VB = INVALID_OGL_VALUE;
	IB = INVALID_OGL_VALUE;
	//NumIndices = 0;
};

SimpleMesh::SubMesh::~SubMesh()
{
	if (VB != INVALID_OGL_VALUE)
	{
		glDeleteBuffers(1, &VB);
	}

	if (IB != INVALID_OGL_VALUE)
	{
		glDeleteBuffers(1, &IB);
	}
}

void SimpleMesh::SubMesh::InitOnGPU()
{
	unsigned int NumIndices = m_indices.size();
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VB);
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::uv)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::normal)));

	glGenBuffers(1, &IB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NumIndices, &m_indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

SimpleMesh::SimpleMesh()
{
}


SimpleMesh::~SimpleMesh()
{

}

void SimpleMesh::InitOnGPU()
{
	for (auto& submesh : m_Entries)
	{
		submesh.InitOnGPU();
	}
	m_isLoadedOnGPU = true;
}

void SimpleMesh::Draw()
{
	for (unsigned int i = 0; i < m_Entries.size(); i++) {
		glBindVertexArray(m_Entries.at(i).VAO);
		glDrawElements(GL_TRIANGLES, m_Entries[i].m_indices.size(), GL_UNSIGNED_INT, 0);
	}
}






