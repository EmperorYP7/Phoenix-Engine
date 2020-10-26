#pragma once

#include <glm/glm.hpp>

namespace Phoenix
{
	class OrthoCamera
	{
	public:
		OrthoCamera(float x, float y, float z, float w);
		~OrthoCamera() = default;

		const glm::mat4& GetProjection() { return m_ProjectionMatrix; }
		const glm::mat4& GetView() { return m_ViewMatrix; }
		const glm::mat4& GetVP() { return  m_VPMatrix; }

		const float& GetRotation() { return m_Rotation; }
		inline void SetRotation(const float& r) { m_Rotation = r; CalculateViewMatrix(); }
		void SetPosition(const glm::vec3& Position) { m_Position = Position; CalculateViewMatrix(); }

	private:

		void CalculateViewMatrix();

		glm::mat4 m_ViewMatrix, m_ProjectionMatrix, m_VPMatrix;
		glm::vec3 m_Position;
		float m_Rotation;
	};
}
