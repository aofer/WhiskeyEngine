#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include "../Rendering/Models/Model.h"
namespace Scene
{
	GameObject::GameObject()
	{
		GameObject(nullptr);
	}

	GameObject::GameObject(GameObject* parent)
	{
		m_pParent = parent;
		m_modelMatrix = glm::mat4(1.0f);
		m_scale = 1.0f;
	}

	GameObject::~GameObject()
	{

	}



	void GameObject::update(float dt)
	{

	}

	void GameObject::setParent(GameObject* parent)
	{
		m_pParent = parent;
		updateModelMatrix();
	}
	GameObject* GameObject::getParent() const
	{
		return m_pParent;
	}

	Rendering::Models::Model* GameObject::getModel() const
	{
		return m_pModel;
	}

	void GameObject::addChild(GameObject* child)
	{
		child->setParent(this);
		m_children.push_back(child);
	}
	
	void GameObject::setModel(Rendering::Models::Model* model) 
	{
		m_pModel = model;
	}




	glm::mat4 GameObject::getModelMatrix() const
	{
		return m_modelMatrix;
	}

	glm::vec3 GameObject::getPosition() const
	{
		return m_position;
	}

	float GameObject::getScale() const
	{
		return m_scale;
	}

	void GameObject::setPosition(const glm::vec3& position) 
	{
		m_position = position;
		//glm::mat4 mat = glm::mat4::identyi
		updateModelMatrix();
	}

	void GameObject::setScale(const float& scale)
	{
		m_scale = scale;
		updateModelMatrix();
	}
	glm::quat GameObject::getOrientation() const
	{
		return m_orientation;
	}

	void GameObject::setOrientation(const glm::quat& orient)
	{
		m_orientation = orient;
		updateModelMatrix();
	}

	void GameObject::updateModelMatrix()
	{
		
		glm::mat4 rotationMat = glm::mat4_cast(m_orientation);
		glm::vec3 rotateVec = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::degrees(5.0f), rotateVec);
		//m_orientation.
		//glm::mat4 RotationMatrix = glm::qu.0at::toMat4(quaternion);
		m_modelMatrix = glm::translate(
			glm::scale(rotationMat, glm::vec3(m_scale, m_scale, m_scale)),
			m_position);
		if (m_pParent)
		{
			m_modelMatrix = m_pParent->getModelMatrix() * m_modelMatrix;
		}
	}

}

