#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtx\quaternion.hpp>

namespace Rendering
{
	namespace Models
	{
		class Model;
	}
}
namespace Scene{

	class GameObject 
	{

	public:
		GameObject();
		GameObject(GameObject* parent);
		virtual ~GameObject();

		glm::mat4 getModelMatrix() const;
		glm::vec3 getPosition() const;
		float getScale() const;
		glm::quat getOrientation() const;

		void setOrientation(const glm::quat& orient);
		void setPosition(const glm::vec3& position) ;
		void setScale(const float& scale) ;
		void setModel(Rendering::Models::Model* model);
		void setParent(GameObject* parent);
		GameObject* getParent() const;
		Rendering::Models::Model* getModel() const;
		void addChild(GameObject* child);
		void update(float dt);
		private:

			glm::mat4 m_modelMatrix;
			glm::vec3 m_position;
			glm::quat m_orientation;
			float m_scale;
			Rendering::Models::Model* m_pModel; //Todo replace this when we add component system
			GameObject* m_pParent;
			std::vector<GameObject*> m_children;
			void updateModelMatrix();
	};
}