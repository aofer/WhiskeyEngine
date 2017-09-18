#include "ObjMeshFactory.h"
#include "SimpleMesh.h"

namespace Rendering
{
	namespace Models
	{
		SimpleMesh* ObjMeshFactory::CreateMesh(const std::string& path)
		{
			// Release the previously loaded mesh (if it exists)
//			Clear();
			SimpleMesh* resMesh = nullptr;
			Assimp::Importer Importer;

			const aiScene* pScene = Importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

			if (pScene) {
				resMesh = InitFromScene(pScene, path);
			}
			else {
				printf("Error parsing '%s': '%s'\n", path.c_str(), Importer.GetErrorString());
			}
			resMesh->InitOnGPU();

			return resMesh;
		}

		SimpleMesh* ObjMeshFactory::InitFromScene(const aiScene* pScene, const std::string& Filename)
		{
			SimpleMesh* mesh = new SimpleMesh();
			mesh->m_Entries.resize(pScene->mNumMeshes);


			// Initialize the meshes in the scene one by one
			for (unsigned int i = 0; i < mesh->m_Entries.size(); i++) {
				const aiMesh* paiMesh = pScene->mMeshes[i];
				InitMesh(i, paiMesh, mesh);
			}

			return mesh;
		}

		void ObjMeshFactory::InitMesh(unsigned int Index, const aiMesh* paiMesh, SimpleMesh* mesh)
		{
			std::vector<VertexFormat> Vertices;
			std::vector<unsigned int> Indices;

			const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

			for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
				const aiVector3D* pPos = &(paiMesh->mVertices[i]);
				const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
				const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

				VertexFormat v(glm::vec3(pPos->x, pPos->y, pPos->z),
					glm::vec2(pTexCoord->x, pTexCoord->y),
					glm::vec3(pNormal->x, pNormal->y, pNormal->z));

				Vertices.push_back(v);
			}

			for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
				const aiFace& Face = paiMesh->mFaces[i];
				assert(Face.mNumIndices == 3);
				Indices.push_back(Face.mIndices[0]);
				Indices.push_back(Face.mIndices[1]);
				Indices.push_back(Face.mIndices[2]);
			}
			mesh->m_Entries[Index].m_vertices = Vertices;
			mesh->m_Entries[Index].m_indices = Indices;
			//mesh->m_Entries[Index].Init(Vertices, Indices);
		}
	}
}

