#include "PXpch.h"
#include "Renderer.hpp"

namespace Phoenix
{

	glm::mat4 Renderer::m_VPMatrix = {};

	void Renderer::BeginScene(OrthoCamera& camera)
	{
		m_VPMatrix = camera.GetVP();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadMat4("u_VP", m_VPMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}