#include "Camera.h"

using namespace FME::Graphics;



glm::vec3 translateVector(glm::vec3 pos, glm::vec3 offset)
{
	glm::vec3 res(0.0f, 0.0f, 0.0f);
	glm::mat4 translate = glm::translate(glm::mat4(), offset);
	res = glm::vec3(translate * glm::vec4(pos, 1.0f));
	return res;
}

Camera::Camera(const glm::vec3& camPosition, const glm::vec3& camPOI) : m_camPos(camPosition), m_camResetPos(camPosition), m_camPOI(camPOI), m_camResetPOI(camPOI), m_upVec(glm::vec3(0.0f, 1.0f,0.0f))
{
	m_zoom = glm::distance(m_camPOI, m_camPos);
	m_view = glm::lookAt(m_camPos, m_camPOI, m_upVec);
}


void Camera::ResetCamera()
{
	m_camPos = m_camResetPos;
	m_camPOI = m_camResetPOI;
}


void Camera::Update()
{
	m_view = glm::lookAt(m_camPos, m_camPOI, m_upVec);
}


glm::vec3 sphereicalToCartesian(glm::vec3 coords)
{
	glm::vec3 res(0.0f, 0.0f, 0.0f);
	res = glm::vec3(coords.x * sin(coords.y) * cos(coords.z), coords.x * cos(coords.y), coords.x * sin(coords.y) * sin(coords.z));
	return res;
}


glm::vec3 cartesianToSphereical(glm::vec3 coords)
{
	glm::vec3 res(0.0f, 0.0f, 0.0f);
	float rSphere = sqrt(pow(coords.x, 2) + pow(coords.y, 2) + pow(coords.z, 2));
	float currPhi = atan2(coords.z, coords.x);
	float currTheta = acos(coords.y / rSphere);
	return glm::vec3(rSphere, currTheta, currPhi);
}


void Camera::PanTumble(float xOffset, float yOffset)
{
	glm::vec3 offsetPos = translateVector(m_camPos, -m_camPOI);
	glm::vec3 radialPos = cartesianToSphereical(offsetPos);
	radialPos.z += (xOffset / glm::pi<float>());
	radialPos.y += (yOffset / glm::pi<float>());
	if (radialPos.y <= 0.0f) radialPos.y = 0.001f;
	if (radialPos.y > glm::pi<float>() * 0.5f ) radialPos.y = glm::pi<float>() * 0.5f;
	m_camPos = translateVector(sphereicalToCartesian(radialPos), m_camPOI);
}

void Camera::Zoom(float zOffset)
{
	glm::vec3 radialPos = cartesianToSphereical(m_camPos);
	radialPos.x += zOffset;
	if (radialPos.x < 0.1f) radialPos.x = 0.1f;
	m_camPos = sphereicalToCartesian(radialPos);
}

void Camera::Translate(float xOffset, float zOffset)
{
	m_camPos.x += xOffset;
	m_camPos.z += zOffset;
	m_camPOI.x += xOffset;
	m_camPOI.z += zOffset;
}

void Camera::Rotate(float xOffset, float zOffset)
{
	glm::vec3 offsetPOI = translateVector(m_camPOI, -m_camPos);

	glm::vec3 radialPos = cartesianToSphereical(offsetPOI);
	radialPos.z += (xOffset / glm::pi<float>());
	radialPos.y += (zOffset / glm::pi<float>());
	//if (radialPos.y <= 0.0f) radialPos.y = 0.001f;
	//if (radialPos.y > glm::pi<float>() * 0.5f) radialPos.y = glm::pi<float>() * 0.5f;
	m_camPOI = translateVector(sphereicalToCartesian(radialPos), m_camPos);
}

void Camera::Elevate(float yOffset)
{
	m_camPos.y += yOffset;
}