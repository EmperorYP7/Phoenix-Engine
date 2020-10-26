#pragma once
#include "Camera/OrthoCamera.hpp"
#include "Shader.hpp"
#include "RenderCommand.hpp"
#include <glm/glm.hpp>

namespace Phoenix
{

	class Renderer
	{
	public:
		static void BeginScene(OrthoCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		static glm::mat4 m_ViewProjectionMatrix;
	};
}