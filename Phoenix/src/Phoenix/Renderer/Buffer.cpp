#include "PXpch.h"

#include "Buffer.hpp"
#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLBuffer.hpp"

namespace Phoenix
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:		PX_CORE_ASSERT(false, "RendererAPI::None is currently not supported") return nullptr;
			case RendererAPI::OpenGL:   return new OpenGLVertexBuffer(vertices, size);
		}
		
		PX_CORE_ASSERT(false, "RendererAPI::{0} is currently not supported", Renderer::GetAPI()); 
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:		PX_CORE_ASSERT(false, "RendererAPI::None is currently not supported") return nullptr;
			case RendererAPI::OpenGL:   return new OpenGLIndexBuffer(indices, size);
		}

		PX_CORE_ASSERT(false, "RendererAPI::{0} is currently not supported", Renderer::GetAPI());
		return nullptr;
	}
}