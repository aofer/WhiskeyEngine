#pragma once
#include <vector>
#include "../IGameObject.h"

namespace Rendering{

	namespace Models{

		class Model :virtual public IGameObject
		{

		public:
			Model();
			virtual ~Model();

			virtual void Draw()             override;
			virtual void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) override;
			virtual void Update()           override;
			virtual void SetProgram(GLuint shaderName) override;
			virtual void Destroy()          override;

			virtual GLuint GetVao()                     const override;
			virtual const std::vector<GLuint> GetVbos() const override;

			glm::mat4 getModelMatrix() const;
			glm::vec3 getPosition() const;
			float getScale() const;

			void setPosition(const glm::vec3& position);
			void setScale(const float& scale);

		protected:
			GLuint vao;
			GLuint program;
			std::vector<GLuint> vbos;


			private:

				glm::mat4 modelMatrix;
				glm::vec3 position;
				//glm::quat orientation;
				float scale;

				void updateModelMatrix();
		};
	}
}