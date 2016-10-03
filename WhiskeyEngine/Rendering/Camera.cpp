#include "Camera.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

using namespace Rendering;

static const float MaxVerticalAngle = 85.0f; //must be less than 90 to avoid gimbal lock

Camera::Camera() :
m_position(0.0f, 0.0f, 1.0f),
horizontalAngle(0.0f),
verticalAngle(0.0f),
fov(45.0f),
nearPlane(0.01f),
farPlane(100.0f),
viewportAspectRatio(4.0f / 3.0f)
{
	updateMatrices();
}

const glm::vec3& Camera::getPosition() const {
	return m_position;
}

void Camera::setPosition(const glm::vec3& position) {
	this->m_position = position;
	updateViewMatrix();
}

void Camera::offsetPosition(const glm::vec3& offset) {
	m_position += offset;
	updateViewMatrix();
}

float Camera::getFieldOfView() const {
	return fov;
}

void Camera::setFieldOfView(float fieldOfView) {
	assert(fieldOfView > 0.0f && fieldOfView < 180.0f);
	fov = fieldOfView;
	updateProjectionMatrix();
}

float Camera::getNearPlane() const {
	return nearPlane;
}

float Camera::getFarPlane() const {
	return farPlane;
}

void Camera::setNearAndFarPlanes(float nearPlane, float farPlane) {
	assert(nearPlane > 0.0f);
	assert(farPlane > nearPlane);
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
	updateProjectionMatrix();
}

glm::mat4 Camera::getOrientation() const {
	glm::mat4 orientation;
	//orientation = glm::rotate(orientation, glm::radians(verticalAngle), glm::vec3(1, 0, 0));
	//orientation = glm::rotate(orientation, glm::radians(horizontalAngle), glm::vec3(0, 1, 0));
	orientation = glm::rotate(orientation, verticalAngle, glm::vec3(1, 0, 0));
	orientation = glm::rotate(orientation, horizontalAngle, glm::vec3(0, 1, 0));
	return orientation;
}

void Camera::offsetOrientation(float upAngle, float rightAngle) {
	horizontalAngle += rightAngle;
	verticalAngle += upAngle;
	normalizeAngles();
	updateViewMatrix();
}

void Camera::lookAt(glm::vec3 position) {
	assert(position != this->m_position);
	m_lookAt = position;
	glm::vec3 direction = glm::normalize(position - this->m_position);
	//verticalAngle = glm::radians(asinf(-direction.y));
	//horizontalAngle = -glm::radians(atan2f(-direction.x, -direction.z));
	verticalAngle = glm::degrees(asinf(-direction.y));
	horizontalAngle = -glm::degrees(atan2f(-direction.x, -direction.z));
	normalizeAngles();
	updateViewMatrix();
}

glm::vec3 Camera::getLookAt() const {
	return m_lookAt;
}

float Camera::getAspectRatio() const {
	return viewportAspectRatio;
}

void Camera::setAspectRatio(float viewportAspectRatio) {
	assert(viewportAspectRatio > 0.0);
	this->viewportAspectRatio = viewportAspectRatio;
	updateProjectionMatrix();
}

glm::vec3 Camera::forward() const {
	glm::vec4 forward = glm::inverse(getOrientation()) * glm::vec4(0, 0, -1, 1);
	return glm::vec3(forward);
}

glm::vec3 Camera::right() const {
	glm::vec4 right = glm::inverse(getOrientation()) * glm::vec4(1, 0, 0, 1);
	return glm::vec3(right);
}

glm::vec3 Camera::up() const {
	glm::vec4 up = glm::inverse(getOrientation()) * glm::vec4(0, 1, 0, 1);
	return glm::vec3(up);
}

glm::mat4 Camera::getViewProjectionMatrix() const {
	return viewProjectionMatrix;
}

glm::mat4 Camera::getProjection() const {
	return projectionMatrix;
}

glm::mat4 Camera::getView() const {
	return viewMatrix;
}

void Camera::normalizeAngles() {
	horizontalAngle = fmodf(horizontalAngle, 360.0f);
	//fmodf can return negative values, but this will make them all positive
	if (horizontalAngle < 0.0f)
		horizontalAngle += 360.0f;

	if (verticalAngle > MaxVerticalAngle)
		verticalAngle = MaxVerticalAngle;
	else if (verticalAngle < -MaxVerticalAngle)
		verticalAngle = -MaxVerticalAngle;
}

void Camera::updateMatrices()
{
	updateProjectionMatrix();
	updateViewMatrix();
	viewProjectionMatrix = getProjection() * getView();
}

void Camera::updateProjectionMatrix()
{
	//projectionMatrix = glm::perspective(glm::radians(fov), viewportAspectRatio, nearPlane, farPlane);
	projectionMatrix[0][0] = 1.0f / (viewportAspectRatio * tan(fov / 2.0f));
	projectionMatrix[1][1] = 1.0f / tan(fov / 2.0f);
	projectionMatrix[2][2] = (-nearPlane - farPlane) / (nearPlane - farPlane);
	projectionMatrix[2][3] = 1.0f;
	projectionMatrix[3][2] = 2.0f * nearPlane * farPlane / (nearPlane - farPlane);
}

void Camera::updateViewMatrix()
{
	viewMatrix = getOrientation() * glm::translate(glm::mat4(), -m_position);
	std::cout << glm::to_string(viewMatrix) << std::endl;
	/*viewMatrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 10.0f, 1.0f);*/
}