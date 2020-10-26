#include "PXpch.h"
#include "OrthoCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Phoenix
{

	OrthoCamera::OrthoCamera(float x, float y, float z, float w)
		:m_Position(0.0f), m_ViewMatrix(1.0f), m_ProjectionMatrix(glm::ortho(x, y, z, w, -1.0f, 1.0f)), m_ViewProjectionMatrix(m_ProjectionMatrix * m_ViewMatrix)
	{}

	void OrthoCamera::CalculateViewMatrix()
	{
		m_ViewMatrix = glm::inverse(glm::translate(glm::mat4(1.0f), m_Position) *
 			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1)));

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}