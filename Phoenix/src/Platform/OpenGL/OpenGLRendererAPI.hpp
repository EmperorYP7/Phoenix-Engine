#pragma once
#include <glm/glm.hpp>
#include "Phoenix\Renderer\VertexArray.hpp"
#include "Phoenix\Renderer\RendererAPI.hpp"

namespace Phoenix
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void ClearColor(const glm::vec4& color);
		void Clear();
		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);
	};
}