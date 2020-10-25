#include "PXpch.h"
#include "VertexArray.hpp"

#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLVertexArray.hpp"

namespace Phoenix {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    PX_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGL:  return new OpenGLVertexArray();
		}

		PX_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
