#include "PXpch.h"
#include "Renderer.hpp"

namespace Phoenix
{

	glm::mat4 Renderer::m_ViewProjectionMatrix = {};

	void Renderer::BeginScene(OrthoCamera& camera)
	{
		m_ViewProjectionMatrix = camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadMat4("u_ViewProjection", m_ViewProjectionMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}