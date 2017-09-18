#pragma once
#include "Model.h"
#include <map>
#include <vector>
#include <GL/glew.h>


namespace Rendering
{
	namespace Models
	{
		class SimpleMesh : public Models::Model
		{
			friend class ObjMeshFactory;
		public:
			SimpleMesh();
			~SimpleMesh();

			void InitOnGPU();

			void Draw();


		private:


			struct SubMesh {
				SubMesh();

				~SubMesh();

				void InitOnGPU();

				GLuint VB;
				GLuint IB;
				GLuint VAO;

				std::vector<VertexFormat> m_vertices;
				std::vector<unsigned int> m_indices;

			};

			std::vector<SubMesh>		m_Entries;
			bool						m_isLoadedOnGPU;
		};
	}
}
