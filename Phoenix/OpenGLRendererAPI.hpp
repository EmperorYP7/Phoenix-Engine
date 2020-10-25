#pragma once
#include "Phoenix\Renderer\RendererAPI.hpp"

namespace Phoenix
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void ClearColor(const glm::vec4& color) override;
		void Clear() override;

		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}

