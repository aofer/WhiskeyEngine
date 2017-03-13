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



	void GameObject::Update(float dt)
	{

	}

	void GameObject::SetParent(GameObject* parent)
	{
		m_pParent = parent;
		UpdateModelMatrix();
	}
	GameObject* GameObject::GetParent() const
	{
		return m_pParent;
	}

	Rendering::Models::Model* GameObject::GetModel() const
	{
		return m_pModel;
	}

	void GameObject::AddChild(GameObject* child)
	{
		child->SetParent(this);
		m_children.push_back(child);
	}
	
	void GameObject::SetModel(Rendering::Models::Model* model) 
	{
		m_pModel = model;
	}




	const glm::mat4& GameObject::GetModelMatrix() const
	{
		return m_modelMatrix;
	}

	const glm::vec3& GameObject::GetPosition() const
	{
		return m_position;
	}

	const float& GameObject::GetScale() const
	{
		return m_scale;
	}

	void GameObject::SetPosition(const glm::vec3& position) 
	{
		m_position = position;
		UpdateModelMatrix();
	}

	void GameObject::SetScale(const float& scale)
	{
		m_scale = scale;
		UpdateModelMatrix();
	}
	const glm::quat& GameObject::GetOrientation() const
	{
		return m_orientation;
	}

	const std::string& GameObject::GetGOName() const
	{
		return m_goName;
	}

	void GameObject::SetOrientation(const glm::quat& orient)
	{
		m_orientation = orient;
		UpdateModelMatrix();
	}

	void GameObject::UpdateModelMatrix()
	{
		
		glm::mat4 rotationMat = glm::mat4_cast(m_orientation);
		glm::vec3 rotateVec = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::degrees(5.0f), rotateVec);
		m_modelMatrix = glm::translate(
			glm::scale(rotationMat, glm::vec3(m_scale, m_scale, m_scale)),
			m_position);
		if (m_pParent)
		{
			m_modelMatrix = m_pParent->GetModelMatrix() * m_modelMatrix;
		}
	}

}

