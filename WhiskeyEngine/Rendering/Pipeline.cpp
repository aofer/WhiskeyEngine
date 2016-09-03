#include "Pipeline.h"
#include <glm/gtc/matrix_transform.hpp>
using namespace Rendering;

const glm::mat4& Pipeline::GetProjTrans()
{
	return glm::perspective(m_persProjInfo.FOV, m_persProjInfo.Width / m_persProjInfo.Height, m_persProjInfo.zNear, m_persProjInfo.zFar);
}


const glm::mat4& Pipeline::GetVPTrans()
{
	GetViewTrans();
	GetProjTrans();

	m_VPtransformation = m_ProjTransformation * m_Vtransformation;
	return m_VPtransformation;
}

const glm::mat4& Pipeline::GetWorldTrans()
{
	glm::mat4 ScaleTrans = glm::mat4(1.0f);
	glm::mat4 RotateTrans = glm::mat4(1.0f);
	glm::mat4 TranslationTrans = glm::mat4(1.0f);

	ScaleTrans = glm::scale(ScaleTrans, m_scale);
	//RotateTrans = glm::rotate(RotateTrans,)
	TranslationTrans = glm::translate(TranslationTrans, m_worldPos);
	/*ScaleTrans.InitScaleTransform(m_scale.x, m_scale.y, m_scale.z);
	RotateTrans.InitRotateTransform(m_rotateInfo.x, m_rotateInfo.y, m_rotateInfo.z);
	TranslationTrans.InitTranslationTransform(m_worldPos.x, m_worldPos.y, m_worldPos.z);
*/
	m_Wtransformation = TranslationTrans * RotateTrans * ScaleTrans;
	return m_Wtransformation;
}

const glm::mat4& Pipeline::GetViewTrans()
{
	return glm::lookAt(m_camera.Pos, m_camera.Target, m_camera.Up);
}

const glm::mat4& Pipeline::GetWVPTrans()
{
	GetWorldTrans();
	GetVPTrans();

	m_WVPtransformation = m_VPtransformation * m_Wtransformation;
	return m_WVPtransformation;
}

const glm::mat4& Pipeline::GetWVOrthoPTrans()
{
	GetWorldTrans();
	GetViewTrans();

	glm::mat4 P = GetProjTrans();

	m_WVPtransformation = P * m_Vtransformation * m_Wtransformation;
	return m_WVPtransformation;
}


const glm::mat4& Pipeline::GetWVTrans()
{
	GetWorldTrans();
	GetViewTrans();

	m_WVtransformation = m_Vtransformation * m_Wtransformation;
	return m_WVtransformation;
}


const glm::mat4& Pipeline::GetWPTrans()
{
	glm::mat4 PersProjTrans = GetProjTrans();

	GetWorldTrans();

	m_WPtransformation = PersProjTrans * m_Wtransformation;
	return m_WPtransformation;
}