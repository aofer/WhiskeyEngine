#pragma once
#include "Model.h"
#include<time.h>
#include <stdarg.h>
#include "../Texture.h"
#include <map>
#include <vector>
#include <GL/glew.h>
#include <Importer.hpp> 
#include <Mesh.h>
#include <scene.h>       // Output data structure
#include <postprocess.h> // Post processing flags


namespace Rendering
{
	namespace Models
	{
		class Mesh : public Models::Model
		{
		public:
			Mesh();
			~Mesh();

			bool Create(const std::string& Filename);

			virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix)	override final;
			virtual void Update() override final;

		private:
			bool InitFromScene(const aiScene* pScene, const std::string& Filename);
			void InitMesh(unsigned int Index, const aiMesh* paiMesh);
			bool InitMaterials(const aiScene* pScene, const std::string& Filename);
			void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF


			struct SubMesh {
				SubMesh();

				~SubMesh();

				void Init(const std::vector<VertexFormat>& Vertices,
					const std::vector<unsigned int>& Indices);

				GLuint VB;
				GLuint IB;
				GLuint VAO;
				unsigned int NumIndices;
				unsigned int MaterialIndex;
			};

			std::vector<SubMesh> m_Entries;
			std::vector<Texture*> m_Textures;
		};
	}
}
